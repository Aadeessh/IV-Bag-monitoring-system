#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID  "TMPL3ZNGdcws2"
#define BLYNK_TEMPLATE_NAME  "IOT based IV Bag Monitor"
#define BLYNK_AUTH_TOKEN  "***************"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <HX711_ADC.h>
#include <EEPROM.h> 

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 20, 4);

// HX711 Pin Configuration
const int HX711_dout = 23;  
const int HX711_sck = 19;   

// HX711 Object
HX711_ADC LoadCell(HX711_dout, HX711_sck);
const int calVal_eepromAdress = 0;  
float calibrationValue = 203.85;  

// Buzzer
#define BUZZER 25

// Blynk Credentials
char auth[] = "KXVpvSiC0x2weOW2P-AxVICchXibtIU7";
char ssid[] = "Aadeessh";
char pass[] = "******";

unsigned long t = 0;

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println("\nStarting...");

    // EEPROM Initialization for ESP32
    EEPROM.begin(512);

    // Initialize LCD
    lcd.init();
    lcd.backlight();

    // Initialize Buzzer
    pinMode(BUZZER, OUTPUT);

    // Initialize Load Cell
    LoadCell.begin();
    unsigned long stabilizingtime = 2000; 
    boolean _tare = true;
    LoadCell.start(stabilizingtime, _tare);

    if (LoadCell.getTareTimeoutFlag()) {
        Serial.println("Timeout! Check HX711 wiring.");
    } else {
        LoadCell.setCalFactor(calibrationValue);
        Serial.println("HX711 setup complete.");
    }

    while (!LoadCell.update());  
    Serial.print("Calibration value: ");
    Serial.println(LoadCell.getCalFactor());

    // Start Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
}

void loop() {
    Blynk.run();
    measureWeight();
}

void measureWeight() {
    static boolean newDataReady = false;
    const int serialPrintInterval = 500;  

    if (LoadCell.update()) {
        newDataReady = true;
    }

    if (newDataReady && millis() > t + serialPrintInterval) {
        float weight = LoadCell.getData();
        if (weight < 0) weight = 0.00;

        int liter = weight; 
        int val = map(liter, 0, 505, 0, 100);

        // LCD Display
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("IOT Based IV Bag");
        lcd.setCursor(2, 1);
        lcd.print("Monitoring System");
        lcd.setCursor(1, 2);
        lcd.print("IV Bottle = ");
        lcd.print(liter);
        lcd.print(" mL");
        lcd.setCursor(1, 3);
        lcd.print("IV Bag Percent=");
        lcd.print(val);
        lcd.print("%");

        // Serial Output
        Serial.print("Weight: ");
        Serial.print(weight, 2);
        Serial.println(" Kg");
        Serial.print("IV Bottle: ");
        Serial.print(liter);
        Serial.println("mL");
        Serial.print("IV Bag Percent: ");
        Serial.print(val);
        Serial.println("%\n");

        newDataReady = false;
        t = millis();
        
        // Buzzer Alert and Blynk Notification
        if (val <= 50 && val >= 40) {
            Blynk.logEvent("iv_alert", "IV Bottle is 50%");
            digitalWrite(BUZZER, HIGH);
            delay(50);
            digitalWrite(BUZZER, LOW);
            delay(50);
        } else if (val <= 20) {
            Blynk.logEvent("iv_alert", "IV Bottle is too LOW");
            digitalWrite(BUZZER, HIGH);
        } else {
            digitalWrite(BUZZER, LOW);
        }

        // Send Data to Blynk
        Blynk.virtualWrite(V0, liter);
        Blynk.virtualWrite(V1, val);
    }

    // Manual Tare via Serial Monitor
    if (Serial.available() > 0) {
        char inByte = Serial.read();
        if (inByte == 't') {
            LoadCell.tareNoDelay();
            Serial.println("Tare initiated...");
        }
    }

    if (LoadCell.getTareStatus()) {
        Serial.println("Tare complete!");
    }
}

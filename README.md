# IoT Based IV Bag Monitor System

## 📋 Abstract

An intelligent IoT-enabled intravenous (IV) bag monitoring system built on ESP32 that provides real-time weight measurement and depletion tracking. The system utilizes a precision load cell (HX711) to measure the remaining fluid volume in IV bags, transmits this data to the Blynk cloud platform, and alerts medical staff through audible alarms and mobile notifications when the IV bag reaches critical thresholds (50% and 20% remaining).

The device features a 20x4 LCD display for local visualization, automatic calibration capabilities, and seamless WiFi connectivity for remote monitoring. This solution improves patient care efficiency by eliminating manual IV bag checks and ensuring timely interventions before fluid depletion.

---

## 🎯 Key Objectives

- **Real-time Monitoring**: Continuous weight-based measurement of IV fluid volume
- **Remote Tracking**: Cloud-based data synchronization via Blynk IoT platform
- **Alert System**: Audible buzzer and push notifications at critical levels
- **User Interface**: Dual display (LCD + Mobile App) for accessibility
- **Automation**: Reduce manual monitoring burden on healthcare staff

---

## 💡 How It Works

1. **Measurement**: HX711 load cell measures IV bag weight
2. **Conversion**: Weight converted to milliliters and percentage depletion
3. **Display**: Real-time data shown on LCD and Blynk dashboard
4. **Alert**: Buzzer and notifications triggered at 50% and 20% thresholds
5. **Calibration**: Easy tare and calibration via serial commands

---

## 🔧 Core Components

| Component | Purpose |
|-----------|---------|
| **ESP32** | Microcontroller & WiFi module |
| **HX711 Load Cell** | Precision weight measurement |
| **20x4 I2C LCD** | Local display interface |
| **Active Buzzer** | Audible alert mechanism |
| **Blynk Platform** | Cloud IoT dashboard |

---

## 📊 Technical Specifications

- **Weight Resolution**: ±0.01 kg
- **Measurement Range**: 0-505 mL (IV bag capacity)
- **Update Interval**: 500 ms
- **Alert Thresholds**: 50% (warning) & 20% (critical)
- **Display**: 20x4 character LCD with real-time updates
- **Connectivity**: WiFi (2.4GHz) via Blynk

---

## 🚀 Applications

- Hospital patient monitoring
- Home healthcare services
- Critical care units
- Infusion therapy centers
- Remote patient supervision

---

## 📱 Features

✅ Real-time IV bag level tracking  
✅ Dual threshold alerts (50% & 20%)  
✅ Blynk mobile app integration  
✅ LCD + Cloud dashboard visualization  
✅ Automatic buzzer alerts  
✅ WiFi-enabled remote monitoring  
✅ Easy calibration mechanism  
✅ EEPROM-based data storage  

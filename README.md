# smart-home-monitoring
ESP8266-based smart home monitoring system with gas detection, temperature/humidity sensors, motion detection, and real-time visualization via Blynk.

## 🚀 Features

- **Gas Detection** (MQ2) with buzzer alert
- **Temperature & Humidity Monitoring** (DHT11)
- **Motion Detection** (PIR Sensor)
- **Water Level/Proximity Detection** (Ultrasonic Sensor)
- **Relay Control** for home appliances via Blynk
- **LCD Display** for on-device feedback
- **Blynk App Integration** for remote access and data visualization

## 🛠 Hardware Used

- NodeMCU ESP8266
- DHT11 Temperature & Humidity Sensor
- MQ2 Gas Sensor
- PIR Motion Sensor
- Ultrasonic Sensor (HC-SR04)
- 16x2 I2C LCD
- Relay Module (x2)
- Active Buzzer

## 📱 Blynk Virtual Pins

| Virtual Pin | Function              |
|-------------|-----------------------|
| V0          | PIR Control Toggle    |
| V1          | Gas Sensor Reading    |
| V2          | Temperature Reading   |
| V3          | Humidity Reading      |
| V4          | Distance Reading      |
| V5          | Relay 1 Control       |
| V6          | Relay 2 Control       |

## ⚙️ Setup Instructions

1. Install the required libraries in Arduino IDE:
   - `ESP8266WiFi`
   - `BlynkSimpleEsp8266`
   - `DHT`
   - `LiquidCrystal_I2C`

2. Replace the following credentials in the code:
   ```cpp
   char auth[] = "Your Blynk Auth Token";
   char ssid[] = "Your WiFi SSID";
   char pass[] = "Your WiFi Password";

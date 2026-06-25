# IoT Smart Load Monitoring System

## Project Overview
This project simulates a cloud-connected Smart Load Monitoring System using an **ESP32**, **HX711 load cell amplifier**, and **ThingSpeak**. The system continuously measures the weight of materials placed on a platform and sends real-time **Discord notifications** whenever the measured weight exceeds or falls below predefined thresholds.

## Features
- Continuous weight measurement using HX711 and Load Cell
- Real-time cloud monitoring with ThingSpeak
- Automatic overload detection
- Automatic low-material detection
- Discord webhook notifications
- Green LED indicates normal operation
- Red LED indicates alert condition
- Simulated using Wokwi

## Hardware Requirements
- ESP32 Development Board
- HX711 Load Cell Amplifier
- Load Cell
- Green LED
- Red LED
- Jumper Wires

## Software Requirements
- Arduino IDE
- HX711 Library
- WiFi Library
- ThingSpeak Library

## Cloud Services
- ThingSpeak
- Discord Webhook

## Pin Connections

| Component | ESP32 Pin |
|-----------|-----------|
| HX711 DOUT | GPIO 4 |
| HX711 SCK | GPIO 5 |
| Green LED | GPIO 18 |
| Red LED | GPIO 19 |

## System Workflow
1. Initialize ESP32, HX711, Wi-Fi, and ThingSpeak.
2. Read the load cell value.
3. Convert the reading into weight.
4. Upload weight to ThingSpeak.
5. Compare the weight against preset thresholds.
6. Send Discord notification if an overload or low-load condition is detected.
7. Repeat continuously.

## Project Structure

```text
Smart-Load-Monitoring/
├── Smart_Load_Monitoring.ino
├── README.md
├── diagram.json
├── screenshots/
├── report.docx
└── demo-video-link.txt

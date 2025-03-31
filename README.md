# IoT-Driven In-House Watering System 🌱💧
Technologies: Arduino | NodeMCU ESP8266 | I2C Protocol | Master-Slave Architecture | Firebase | IoT

This project enhances traditional home garden watering systems by integrating IoT functionality. It combines both hardware and software components to create a smart, automated watering solution that is efficient, scalable, and remotely manageable.

🔧 System Overview
The system is built using:

Microcontrollers: Arduino Uno (Sensor Node) & NodeMCU ESP8266 (Wi-Fi Master Node)

Communication Protocol: I2C (for master-slave communication between Arduino and NodeMCU)

IoT Platform: Firebase Realtime Database (for remote monitoring and control)

🌿 Sensors & Actuators
Soil Moisture Sensors: 3 units (to monitor soil conditions in different zones)

Ultrasonic Sensor (HC-SR04): 1 unit (to monitor water tank level)

DC Water Pumps: 3 units (each controlled independently based on sensor data)

📡 How It Works
Arduino collects data from soil and ultrasonic sensors.

Data is transmitted via I2C to NodeMCU.

NodeMCU uploads the data to Firebase and receives control signals.

Based on real-time data, water pumps are activated to irrigate specific zones.

🖼️ System Architecture
https://github.com/kabir1995/IoT-driven-in-House-Watering-System/raw/master/Block%20diagram.jpg

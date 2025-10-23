# IoT-Based-Emergency-Evacuation-System-using-ESp32
This research presents a cost-effective IoT-based real-time evacuation system using DHT11, BMP180, and OLED displays controlled by ESP32. It guides users to the safest exits via local processing and a web interface with personalized directions and a real-time chatbot for facility assistance.

 A cost-efficient and effective realtime evacuation direction system based on Internet of Things (IoT) technology with an easy-to-use web interface is offered. It can be installed in public areas like stadiums, parks, and venues for events, and it helps individuals in case of emergency by leading them to the best exit paths.

The system combines three main hardware elements: the DHT11 temperature and humidity sensor, the BMP180 pressure sensor, and the SSD1306 OLED display, controlled by an ESP32 microcontroller programmed through the Arduino IDE. All ESP32s at each gate gather and process locally real-time environmental information, removing the need for cloud infrastructure in the case of low latency and fault tolerance.

A comparison algorithm compares sensor data against safety limits to determine the safest gate, presenting this information on an OLED display and at the same time making it available via a special website. Users can enter their seat numbers on the site in order to get personal evacuation guidance, improving the accuracy of guidance. An online chatbot service on the site also offers real-time assistance to help find facilities like washrooms and snack counters.

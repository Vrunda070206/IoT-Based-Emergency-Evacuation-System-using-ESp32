#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// I2C pins (one OLED assumed)
#define OLED_SDA 21
#define OLED_SCL 22

// DHT pins for 3 gates
#define DHTPIN1 5
#define DHTPIN2 18
#define DHTPIN3 19
#define DHTTYPE DHT11

// Objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BMP085 bmp1;
Adafruit_BMP085 bmp2;
Adafruit_BMP085 bmp3;

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);

struct GateData {
float temp;
float hum;
float pressure;
float score;
};

void setup() {
Serial.begin(115200);
Wire.begin(OLED_SDA, OLED_SCL);

if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
Serial.println("SSD1306 init failed");
while (true);
}
display.setRotation(2); 
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.display();

dht1.begin();
dht2.begin();
dht3.begin();

if (!bmp1.begin()) Serial.println("BMP180 #1 not found");
if (!bmp2.begin()) Serial.println("BMP180 #2 not found");
if (!bmp3.begin()) Serial.println("BMP180 #3 not found");
}

void loop() {
GateData gates[3];

gates[0] = readGateData(dht1, bmp1);
gates[1] = readGateData(dht2, bmp2);
gates[2] = readGateData(dht3, bmp3);

// Calculate score based on deviation from ideal values
for (int i = 0; i < 3; i++) {
gates[i].score = abs(gates[i].temp - 25) +
abs(gates[i].hum - 50) +
abs(gates[i].pressure - 1013);
}

int safestGate = findSafestGate(gates);

displayInfo(gates, safestGate);

delay(5000);
}

GateData readGateData(DHT &dht, Adafruit_BMP085 &bmp) {
GateData data;
data.temp = dht.readTemperature();
data.hum = dht.readHumidity();
data.pressure = bmp.readPressure() / 100.0;
return data;
}

int findSafestGate(GateData gates[]) {
float minScore = 9999;
int index = -1;
for (int i = 0; i < 3; i++) {
if (!isnan(gates[i].temp) && !isnan(gates[i].hum) && !isnan(gates[i].pressure)) {
if (gates[i].score < minScore) {
minScore = gates[i].score;
index = i;
}
}
}
return index + 1; // Gate 1, 2, or 3
}

void displayInfo(GateData gates[], int safestGate) {
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 0);

// Get the safest gate's data
GateData safe = gates[safestGate - 1]; // safestGate is 1-based index

display.print("Temp: ");
display.print(safe.temp, 1);
display.println(" C");

display.print("Humidity: ");
display.print(safe.hum, 1);
display.println(" %");

display.print("Pressure: ");
display.print(safe.pressure, 0);
display.println(" hPa");

display.println(); // empty line for spacing

display.print("Safe Gate: Gate ");
display.println(safestGate);

display.display();
}
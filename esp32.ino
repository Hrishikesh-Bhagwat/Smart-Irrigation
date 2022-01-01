#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h> // For temperature and humidity, if using BME280

// AWS IoT Core credentials
const char* ssid = "your-SSID";//Enter SSID
const char* password = "your-PASSWORD";//Enter Password
const char* mqttServer = "your-iot-endpoint.iot.us-west-2.amazonaws.com";//Enter endpoint
const int mqttPort = 8883;
const char* clientId = "esp32-moisture-temperature";

// Moisture sensor pin
const int moistureSensorPin = A0;

// BME280 setup (for temperature and humidity)
Adafruit_BME280 bme;

// WiFi client
WiFiClientSecure espClient;

// MQTT client
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // AWS IoT Core setup
  espClient.setCACert(root_ca);
  espClient.setCertificate(client_cert);
  espClient.setPrivateKey(private_key);

  // Initialize sensors
  bme.begin();

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
}

void loop() {
  // Read soil moisture
  int moistureValue = analogRead(moistureSensorPin);

  // Read temperature and humidity
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();

  // Publish data to AWS IoT Core
  String payload = "{\"moisture\":" + String(moistureValue) +
                   ",\"temperature\":" + String(temperature) +
                   ",\"humidity\":" + String(humidity) + "}";

  char topic[50];
  sprintf(topic, "sensors/esp32");

  if (client.connect(clientId)) {
    client.publish(topic, payload.c_str());
    client.disconnect();
  }

  delay(60000); // Send data every 1 minute
}
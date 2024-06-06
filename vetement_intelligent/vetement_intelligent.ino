#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MAX3010x.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Remplacez par les informations de votre réseau WiFi
const char* ssid = "VOTRE_SSID";
const char* password = "VOTRE_MOT_DE_PASSE";

// Déclaration des adresses I2C des capteurs
#define BME280_ADDRESS 0x76
#define MAX30102_ADDRESS 0x57

// Créez les objets pour les capteurs
Adafruit_BME280 bme;
Adafruit_MAX3010x max30102;
OneWire oneWire(5); // Broche pour le capteur de température DS18B20
DallasTemperature sensors(&oneWire);

// Créez un objet pour le serveur web
AsyncWebServer server(80);

// Variables pour stocker les valeurs des capteurs
float temperature = 0;
float humidity = 0;
float pressure = 0;
float heartRate = 0;
float spo2 = 0;
float skinConductance = 0;

void setup() {
  // Initialisez le port série
  Serial.begin(115200);

  // Initialisez le WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialisez les capteurs
  Wire.begin();
  bme.begin(BME280_ADDRESS);
  max30102.begin(MAX30102_ADDRESS);
  sensors.begin();

  // Configurez les routes pour les requêtes HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html>";
    html += "<head>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; margin: 0; padding: 20px; background-color: #f4f4f4; }";
    html += "h1 { color: #333333; }";
    html += ".sensor-container { background-color: #ffffff; padding: 20px; margin-bottom: 20px; }";
    html += ".sensor-title { color: #555555; font-size: 18px; margin-bottom: 10px; }";
    html += ".sensor-value { color: #333333; font-size: 24px; margin-bottom: 20px; }";
    html += ".sensor-icon { width: 40px; height: 40px; margin-right: 10px; vertical-align: middle; }";
    html += "</style>";
    html += "</head>";
    html += "<body>";
    html += "<h1>Données des capteurs</h1>";

    // Capteur de température
    html += "<div class='sensor-container'>";
    html += "<img class='sensor-icon' src='https://example.com/temperature-icon.png' alt='Temperature Icon'>";
    html += "<div class='sensor-title'>Température</div>";
    html += "<div class='sensor-value'>" + String(temperature) + " °C</div>";
    html += "</div>";

    // Capteur d'humidité
    html += "<div class='sensor-container'>";
    html += "<img class='sensor-icon' src='https://example.com/humidity-icon.png' alt='Humidity Icon'>";
    html += "<div class='sensor-title'>Humidité</div>";
    html += "<div class='sensor-value'>" + String(humidity) + " %</div>";
    html += "</div>";

    // Capteur de pression
    html += "<div class='sensor-container'>";
    html += "<img class='sensor-icon' src='https://example.com/pressure-icon.png' alt='Pressure Icon'>";
    html += "<div class='sensor-title'>Pression</div>";
    html += "<div class='sensor-value'>" + String(pressure) + " hPa</div>";
    html += "</div>";

    // Capteur de fréquence cardiaque
    html += "<div class='sensor-container'>";
    html += "<img class='sensor-icon' src='https://example.com/heart-rate-icon.png' alt='Heart Rate Icon'>";
    html += "<div class='sensor-title'>Fréquence cardiaque</div>";
    html += "<div class='sensor-value'>" + String(heartRate) + " bpm</div>";
    html += "</div>";

    // Capteur de SpO2html += "<div class='sensor-container'>";
    html += "<img class='sensor-icon' src='https://example.com/spo2-icon.png' alt='SpO2 Icon'>";
    html += "<div class='sensor-title'>SpO2</div>";
    html += "<div class='sensor-value'>" + String(spo2) + " %</div>";
    html += "</div>";

    // Capteur de conductance cutanée
    html += "<div class='sensor-container'>";
    html += "<img class='sensor-icon' src='https://example.com/skin-conductance-icon.png' alt='Skin Conductance Icon'>";
    html += "<div class='sensor-title'>Conductance cutanée</div>";
    html += "<div class='sensor-value'>" + String(skinConductance) + "</div>";
    html += "</div>";

    html += "</body>";
    html += "</html>";

    request->send(200, "text/html", html);
  });

  // Démarrez le serveur web
  server.begin();
}

void loop() {
  // Lisez les valeurs des capteurs
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0;
  heartRate = max30102.getHeartRate();
  spo2 = max30102.getSpO2();
  sensors.requestTemperatures();
  skinConductance = analogRead(A0);

  // Attendez pendant 1 seconde avant de lire les capteurs à nouveau
  delay(1000);
}

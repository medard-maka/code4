#include <SPIFFS.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* ssid = "McMeder";
const char* password = "mcmeder91";

const int DHTPIN = 4;     // Broche à laquelle le capteur DHT est connecté
const int DHTTYPE = DHT11;   // Type de capteur DHT utilisé (DHT11, DHT22, DHT21)

const int POTENTIOMETER_PIN = 34;  // Broche à laquelle le potentiomètre est connecté
const int BUTTON_PIN = 2;  // Broche à laquelle le bouton poussoir est connecté

DHT dht(DHTPIN, DHTTYPE);  // Initialisation du capteur DHT


WebServer server(80);

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  File fi= SPIFFS.open("/valide.html", "r");
  File fil = SPIFFS.open("/meder.html", "r");
  if (!file) {
    Serial.println("Erreur lors de l'ouverture du fichier index.html");
    return;
  }

  String content = file.readString();
  server.send(200, "text/html", content);
  file.close();
}

void handlePotentiometer() {
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);
  server.send(200, "text/plain", String(potentiometerValue));
}

void handleTemperature() {
  float temperature = dht.readTemperature();
  server.send(200, "text/plain", String(temperature));
}

void handleHumidity() {
  float humidity = dht.readHumidity();
  server.send(200, "text/plain", String(humidity));
}


void setup() {
  Serial.begin(115200);

  // Initialisation des composants
  dht.begin();

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi en cours...");
  }
  Serial.println("Connexion au WiFi établie");

  // Initialisation du système de fichiers SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Erreur lors de l'initialisation du système de fichiers SPIFFS");
    return;
  }

  // Configuration des routes pour le serveur Web
  server.on("/", HTTP_GET, handleRoot);
  server.on("/potentiometerValue", HTTP_GET, handlePotentiometer);
  server.on("/temperature", HTTP_GET, handleTemperature);
  server.on("/humidity", HTTP_GET, handleHumidity);
  

  server.begin();

  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();

  
 
}

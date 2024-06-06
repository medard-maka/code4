#include <WiFi.h>
#include <HTTPClient.h>

// Configuration du WiFi
const char* ssid = "McMeder";
const char* password = "mcmeder91";

// Configuration du potentiomètre
const int potPin = 34; // Pin analogique pour le potentiomètre

void setup() {
  // Initialiser le moniteur série
  Serial.begin(115200);

  // Se connecter au WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Lire la valeur du potentiomètre
  int potValue = analogRead(potPin);

  // Envoyer la valeur du potentiomètre à l'interface en ligne
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://medard-maka.github.io/ketsia/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String payload = "potValue=" + String(potValue);
    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(1000); // Attendre 1 seconde avant de mesurer à nouveau
}

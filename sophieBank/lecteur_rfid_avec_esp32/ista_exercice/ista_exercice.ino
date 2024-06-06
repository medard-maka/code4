#include <WiFi.h>
#include <FirebaseArduino.h>

// Configuration WiFi
const char* ssid = "McMeder";
const char* password = "mcmeder91";

// Configuration de Firebase
#define FIREBASE_HOST "YOUR_FIREBASE_HOST"
#define FIREBASE_AUTH "YOUR_FIREBASE_AUTH"

// Broches du potentiomètre
const int potPin = 34;

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connexion à Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Lire la valeur du potentiomètre
  int potValue = analogRead(potPin);

  // Envoyer la valeur du potentiomètre à Firebase
  Firebase.setInt("potentiometer/value", potValue);

  delay(1000); // Envoyer les données toutes les 1 seconde
}

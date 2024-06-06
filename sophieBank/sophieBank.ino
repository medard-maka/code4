#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <MFRC522.h>
#include <HTTPClient.h>

// Définir les broches pour le lecteur RFID
#define SS_PIN 15
#define RST_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Créer une instance du lecteur RFID

// Remplacez avec vos informations de réseau
const char* ssid = "McMeder";
const char* password = "mcmeder91";

WebServer server(80);  // Créer une instance du serveur web

void handleRoot() {
  String html = readFile("/index.html");
  String uid = readRFID();
  html.replace("{RFID_ID}", uid);
  server.send(200, "text/html", html);

  if (uid != "") {
    sendDataToWebsite(uid);
  }
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();  // Initialiser le SPIFFS

  // Se connecter au réseau Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au Wi-Fi...");
  }
  Serial.println("Connecté au réseau Wi-Fi");

  // Initialiser le lecteur RFID
  mfrc522.PCD_Init();
  Serial.println("Lecteur RFID initialisé");

  // Gérer la requête GET pour la page d'accueil
  server.on("/", handleRoot);

  // Démarrer le serveur web
  server.begin();
  Serial.println("Serveur web démarré");
}

void loop() {
  server.handleClient();
}

String readFile(const char* path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Impossible de lire le fichier");
    return String();
  }

  String content;
  while (file.available()) {
    content += file.readStringUntil('\n');
  }
  file.close();
  return content;
}

String readRFID() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return String();
  }

  String uid;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  mfrc522.PICC_HaltA();
  return uid;
}

void sendDataToWebsite(String uid) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://medard-maka.github.io/ketsia/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String payload = "RFID_ID=" + uid;
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Erreur lors de l'envoi des données: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Erreur de connexion WiFi");
  }
}

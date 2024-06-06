#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

int led = 2;
int buz = 7;

// Tableau des cartes autorisées
byte authorizedCards[][4] = {
    {0xE9, 0xC0, 0x81, 0x14},  // Carte 1 E9 C0 81 14

    {0x72, 0x17, 0xBE, 0x22}   // Carte 2
};

// Nombre de cartes autorisées
const int numAuthorizedCards = sizeof(authorizedCards) / sizeof(authorizedCards[0]);

void setup()
{
  myservo.attach(6);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Prêt à lire les cartes...");
  Serial.println();
}

void loop()
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Show UID on serial monitor
  Serial.print("L'identité de la carte est : ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();

  // Vérifier si la carte est autorisée
  bool isAuthorized = false;
  for (int i = 0; i < numAuthorizedCards; i++)
  {
    bool match = true;
    for (int j = 0; j < 4; j++)
    {
      if (mfrc522.uid.uidByte[j] != authorizedCards[i][j])
      {
        match = false;
        break;
      }
    }
    if (match)
    {
      isAuthorized = true;
      break;
    }
  }

  // Traiter l'accès en fonction de l'autorisation
  if (isAuthorized)
  {
    Serial.println("Accès autorisé pour toi, employé de l'entreprise");
    Serial.println();
    delay(100);

    digitalWrite(led, HIGH);
    digitalWrite(buz, LOW);
    delay(1000);
    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    digitalWrite(led, LOW);
    delay(3000);
    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
  }
  else
  {
    Serial.println("Accès refusé, tu n'es pas reconnu dans cette entreprise");
    Serial.println();
    delay(100);

    digitalWrite(buz, HIGH);
    delay(3000);
    digitalWrite(buz, LOW);
    delay(3000);
  }
}

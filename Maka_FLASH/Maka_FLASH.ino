#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>    
SoftwareSerial GSM(8, 9); 
char phone_no[]="+243995799692"; 
char inchar; 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse I2C de l'écran LCD, 16 colonnes et 2 lignes
int led1=3;
int led2=4;
const int waterFlowPin = 2;  // Broche du capteur de débit d'eau
const float flowFactor = 7.5;  // Facteur de conversion pour le débit (en L/min)
const unsigned long interval = 1000;  // Intervalle de mise à jour de l'écranh en millisecondes

volatile unsigned int pulseCount = 0;  // Compteur d'impulsions du capteur à effet Hall
volatile float flowRate = 0.0;  // Variable pour stocker le débit instantané (en L/min)
float totalVolume = 1.0;  // Variable pour stocker le volume total écoulé (en litres)
int volumeAddress = 0;  // Adresse de la variable de volume dans l'EEPROM

unsigned long previousMillis = 0;

void setup() {
  lcd.init();                     // Initialise l'écran LCD
  lcd.backlight();                // Active le rétroéclairage de l'écran LCD
  lcd.begin(16, 2);               // Démarre l'écran LCD avec 16 colonnes et 2 lignes
  lcd.print("Volume: ");
  lcd.setCursor(0, 1);
  lcd.print("Debit:   ");


Serial.println("Initializing....");
initModule("AT","OK",1000);                //Once the handshake test is successful, it will back to OK
initModule("ATE1","OK",1000);              //this command is used for enabling echo
initModule("AT+CPIN?","READY",1000);       //this command is used to check whether SIM card is inserted in GSM Module or not
initModule("AT+CMGF=1","OK",1000);         //Configuring TEXT mode
initModule("AT+CNMI=2,2,0,0,0","OK",1000); //Decides how newly arrived SMS messages should be handled  
Serial.println("Initialized Successfully"); 


  attachInterrupt(digitalPinToInterrupt(waterFlowPin), pulseCounter, FALLING);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {

if(GSM.available() >0){inchar=GSM.read(); Serial.print(inchar); 
 if(inchar=='R'){inchar=GSM.read(); 
 if(inchar=='I'){inchar=GSM.read();
 if(inchar=='N'){inchar=GSM.read();
 if(inchar=='G'){initModule("ATH","OK",1000); // this command is used for Call busy
    }
   }
  }
 }

else if(inchar=='P'){delay(10); inchar=GSM.read(); 
     if(inchar=='R'){delay(10); inchar=GSM.read();
     if(inchar=='O'){delay(10); inchar=GSM.read();

     if(inchar=='1'){
              totalVolume=totalVolume+10;
              sendSMS(phone_no,"j'ai recu 10 litres ");
              }
              else if(inchar=='2'){
              totalVolume=totalVolume+20;
              sendSMS(phone_no,"j'ai recu 20 litres ");
              }
              else if(inchar=='3'){
              totalVolume=totalVolume+30;
              sendSMS(phone_no,"j'ai recu 30 litres ");
      }
     }
    }
  }
}
delay(5);
unsigned long currentMillis = millis();
 if (currentMillis - previousMillis >= interval) {
    updateFlowRate();
    updateVolume();
    updateLCD(totalVolume, flowRate);
    previousMillis = currentMillis;
  }
}

void sendSMS(char *number, char *msg){
GSM.print("AT+CMGS=\"");GSM.print(number);GSM.println("\"\r\n"); //AT+CMGS="Mobile Number" <ENTER> - Assigning recipient's mobile number
delay(500);
GSM.println(msg); // Message contents
delay(500);
GSM.write(byte(26));
delay(500);  
}

void initModule(String cmd, char *res, int t){
while(1){
    Serial.println(cmd);
    GSM.println(cmd);
    delay(100);
    while(GSM.available()>0){
       if(GSM.find(res)){
        Serial.println(res);
        delay(t);
        return;
       }else{Serial.println("Error");
       }
       }
    delay(t);
  }
}

void pulseCounter() {
  pulseCount++;  // Incrémente le compteur d'impulsions
}

void updateFlowRate() {
  detachInterrupt(digitalPinToInterrupt(waterFlowPin));  // Détache l'interruption pendant le calcul du débit
  float pulses = pulseCount;
  flowRate = (pulses / interval) * flowFactor;  // Calcule le débit instantané en L/min
  pulseCount = 0;  // Réinitialise le compteur d'impulsions
  attachInterrupt(digitalPinToInterrupt(waterFlowPin), pulseCounter, FALLING);  // Réattache l'interruption
}

void updateVolume() {
  totalVolume -= flowRate * (interval / 60000.0); 
  digitalWrite(led2, LOW);  // Éteint la LED rouge
  digitalWrite(led1, LOW);  // Éteint la LED jaune

  if (totalVolume <= 0.5) {
    digitalWrite(led1, HIGH);  // Allume la LED jaune si le volume est inférieur ou égal à 0.5 litre
    if (totalVolume <= 0) {
    digitalWrite(led2, HIGH);  // Allume la LED rouge si le volume est inférieur ou égal à 0 litre
  }
  } 
}

void updateLCD(float totalVolume, float flow) {
  lcd.setCursor(8, 0);
  lcd.print("       ");  // Efface le champ du volume précédent
  lcd.setCursor(8, 0);
  lcd.print(totalVolume, 2);  // Imprime le volume avec 2 décimales
  lcd.print(" L");

  lcd.setCursor(6, 1);
  lcd.print("     ");  // Efface le champ du débit précédent
  lcd.setCursor(6, 1);
  lcd.print(flow, 2);  // Imprime le débit avec 2 décimales
  lcd.print(" L/min");
}

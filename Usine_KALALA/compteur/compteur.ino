#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


#define SENSOR_PIN 12
#define RELAY_PIN 13


int delayTime = 500;
int impulseCount = 0;

bool lastSensorState = LOW;


void setup() {
  
  lcd.clear();
  lcd.begin(16, 2);
  
  lcd.print("Relay Control");
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Maa-Lis");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Fundi bora");
  lcd.setCursor(2, 1);
  lcd.print("0810076009");
  delay(2000);
  
  updateLCD();
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  bool sensorState = digitalRead(SENSOR_PIN);
  if (sensorState != lastSensorState && sensorState == HIGH) {
    impulseCount++;
    updateLCD();
  }
    
  lastSensorState = sensorState;
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bouchons ");
 
  lcd.setCursor(0, 1);
  lcd.print(impulseCount);
}

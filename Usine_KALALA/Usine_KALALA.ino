#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define BUTTON_PIN_INCREMENT 9
#define BUTTON_PIN_DECREMENT 8
#define SENSOR_PIN 12
#define RELAY_PIN 13


int delayTime = 500;
int impulseCount = 0;

bool lastSensorState = LOW;
bool lastButtonStateIncrement = HIGH;
bool lastButtonStateDecrement = HIGH;

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
  
  pinMode(BUTTON_PIN_INCREMENT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DECREMENT, INPUT_PULLUP);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  bool sensorState = digitalRead(SENSOR_PIN);
  if (sensorState != lastSensorState && sensorState == HIGH) {
    impulseCount++;
    updateLCD();
    digitalWrite (RELAY_PIN ,HIGH);
    delay(delayTime);
    digitalWrite (RELAY_PIN ,LOW);
  }
  
  bool buttonStateIncrement = digitalRead(BUTTON_PIN_INCREMENT);
  bool buttonStateDecrement = digitalRead(BUTTON_PIN_DECREMENT);
  
  if (buttonStateIncrement != lastButtonStateIncrement && buttonStateIncrement == LOW) {
    delayTime += 500;
    updateLCD();
    
  }
  
  if (buttonStateDecrement != lastButtonStateDecrement && buttonStateDecrement == LOW) {
    delayTime -= 20;
    if (delayTime < 0) {
      delayTime = 0;
    }
    updateLCD();
    
  }
  
  lastSensorState = sensorState;
  lastButtonStateIncrement = buttonStateIncrement;
  lastButtonStateDecrement = buttonStateDecrement;
  
  delay(1);
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Delay: ");
  lcd.print(delayTime);
  lcd.print(" ms");
  
  lcd.setCursor(0, 1);
  lcd.print("Bout: ");
  lcd.print(impulseCount);
}

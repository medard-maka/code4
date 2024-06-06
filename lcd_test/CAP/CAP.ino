#include <SoftwareSerial.h>


int caT=A0;
float T;


void setup() {
  pinMode(A0,OUTPUT);
Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){

    T=analogRead(caT);
    Serial.print("temperature");
    Serial.print(T);
    Serial.println("°C");
    
    delay(1000);
  }

}

#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
  int res=A0;
  int vx=0;
  int vxx=0;
  String ut="°C";
  void setup() {
    Serial.begin(9600);
   lcd.begin(16,2);
   pinMode(res,INPUT);
 
  
  }
  
  void loop() {
   vx=analogRead(res);
vxx=map(vx,0,1023,0,100);
   //vxx=(vx/4);
   lcd.setCursor(4,0);
   lcd.print ("medard");
   lcd.setCursor(1,1);
   lcd.println(vxx);
   lcd.println(ut);
  }

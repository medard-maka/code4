#include <SoftwareSerial.h>    //Create software serial object to communicate with SIM800L
SoftwareSerial GSM(8, 9); //SIM800L Tx & Rx is connected to Arduino #8 & #9
char phone_no[]="+243997780844"; //change with country code and +243997780844 with phone number to sms

#define US  A0
#define IS  A1
#define U0  A2
#define UM  A3
#define UF  A4


int R1=2; 
int R2=3;
int R3=4;
int R4=5;
int R5=6;
int R6=7;
int R7=10;
int R8=11;
int R9=12;
int R10=13;
int R11;
int R12;
int R13;
int R14;
int R15;

char inchar; // Will hold the incoming character from the GSM shield

void setup(){// put your setup code here, to run once

Serial.begin(9600);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)  
GSM.begin(9600);   //Begin serial communication with Arduino and SIM800L

pinMode(US, INPUT); 
pinMode(IS, INPUT);
pinMode(UM, INPUT);
pinMode(U0, INPUT); 
pinMode(UF, INPUT);

pinMode(R1,OUTPUT);
pinMode(R2,OUTPUT);
pinMode(R3,OUTPUT);
pinMode(R4,OUTPUT);
pinMode(R5,OUTPUT);
pinMode(R6,OUTPUT);
pinMode(R7,OUTPUT);
pinMode(R8,OUTPUT); 
pinMode(R9,OUTPUT);
pinMode(R10,OUTPUT);
pinMode(R11,OUTPUT);
pinMode(R12,OUTPUT);
pinMode(R13,OUTPUT);
pinMode(R14,OUTPUT);
pinMode(R15,OUTPUT);

  
Serial.println("Initializing....");
initModule("AT","OK",1000);                //Once the handshake test is successful, it will back to OK
initModule("ATE1","OK",1000);              //this command is used for enabling echo
initModule("AT+CPIN?","READY",1000);       //this command is used to check whether SIM card is inserted in GSM Module or not
initModule("AT+CMGF=1","OK",1000);         //Configuring TEXT mode
initModule("AT+CNMI=2,2,0,0,0","OK",1000); //Decides how newly arrived SMS messages should be handled  
Serial.println("Initialized Successfully");
sendSMS(phone_no,"Activation"); 

}

void loop(){

if(GSM.available() >0){inchar=GSM.read(); Serial.print(inchar); 
     if(inchar=='D'){delay(10); inchar=GSM.read(); 
     if(inchar=='E'){delay(10); inchar=GSM.read();
     if(inchar=='P'){delay(10); inchar=GSM.read();

     if(inchar=='A'){digitalWrite(R1, 1); sendSMS(phone_no,"DEPART 1,ACTIVE");}
     if(inchar=='a'){digitalWrite(R1, 0); sendSMS(phone_no,"DEPART 1,DESACTIVE");}
     if(inchar=='B'){digitalWrite(R2, 1); sendSMS(phone_no,"DEPART 2,ACTIVE");}
     if(inchar=='b'){digitalWrite(R2, 0); sendSMS(phone_no,"DEPART 2,DESACTIVE");}
     if(inchar=='C'){digitalWrite(R3, 1); sendSMS(phone_no,"DEPART 3,ACTIVE");}
     if(inchar=='c'){digitalWrite(R3, 0); sendSMS(phone_no,"DEPART 3,DESACTIVE");}

     if(inchar=='D'){digitalWrite(R4, 1); sendSMS(phone_no,"DEPART 4,ACTIVE");}
     if(inchar=='d'){digitalWrite(R4, 0); sendSMS(phone_no,"DEPART 4,DESACTIVE");}
     if(inchar=='E'){digitalWrite(R5, 1); sendSMS(phone_no,"DEPART 5,ACTIVE");}
     if(inchar=='e'){digitalWrite(R5, 0); sendSMS(phone_no,"DEPART 5,DESACTIVE");}
     if(inchar=='F'){digitalWrite(R6, 1); sendSMS(phone_no,"DEPART 6,ACTIVE");}
     if(inchar=='f'){digitalWrite(R6, 0); sendSMS(phone_no,"DEPART 6,DESACTIVE");}

     if(inchar=='H'){digitalWrite(R7, 1); sendSMS(phone_no,"DEPART 7,ACTIVE");}
     if(inchar=='h'){digitalWrite(R7, 0); sendSMS(phone_no,"DEPART 7,DESACTIVE");}
     if(inchar=='I'){digitalWrite(R8, 1); sendSMS(phone_no,"DEPART 8,ACTIVE");}
     if(inchar=='i'){digitalWrite(R8, 0); sendSMS(phone_no,"DEPART 8,DESACTIVE");}
     if(inchar=='J'){digitalWrite(R9, 1); sendSMS(phone_no,"DEPART 9,ACTIVE");}
     if(inchar=='j'){digitalWrite(R9, 0); sendSMS(phone_no,"DEPART 9,DESACTIVE");}

     if(inchar=='K'){digitalWrite(R7, 1); sendSMS(phone_no,"DEPART 7,ACTIVE");}
     if(inchar=='k'){digitalWrite(R7, 0); sendSMS(phone_no,"DEPART 7,DESACTIVE");}
     if(inchar=='L'){digitalWrite(R8, 1); sendSMS(phone_no,"DEPART 8,ACTIVE");}
     if(inchar=='l'){digitalWrite(R8, 0); sendSMS(phone_no,"DEPART 8,DESACTIVE");}
     if(inchar=='M'){digitalWrite(R9, 1); sendSMS(phone_no,"DEPART 9,ACTIVE");}
     if(inchar=='m'){digitalWrite(R9, 0); sendSMS(phone_no,"DEPART 9,DESACTIVE");}

     if(inchar=='K'){digitalWrite(R10, 1); sendSMS(phone_no,"DEPART 10,ACTIVE");}
     if(inchar=='k'){digitalWrite(R10, 0); sendSMS(phone_no,"DEPART 10,DESACTIVE");}
     
     
else if(inchar=='X'){ sendSMS(phone_no,"Tous sont activés");
digitalWrite(R1,HIGH);
digitalWrite(R2,HIGH);
digitalWrite(R3,HIGH);

digitalWrite(R4,HIGH);
digitalWrite(R5,HIGH);
digitalWrite(R6,HIGH);
digitalWrite(R7,HIGH);
digitalWrite(R8,HIGH);
digitalWrite(R9,HIGH);
digitalWrite(R10,HIGH);
digitalWrite(R11,HIGH);
digitalWrite(R12,HIGH);

digitalWrite(R13,HIGH);
digitalWrite(R14,HIGH);
digitalWrite(R15,HIGH);
      }
     }
    }
  }
}


if(digitalRead (US) == 1){sendSMS(phone_no,"U > !! SURTENSION");
delay(2);
sendSMS(phone_no,"Declanchement I=0");
digitalWrite(R1,LOW);
digitalWrite(R2,LOW);
digitalWrite(R3,LOW);

digitalWrite(R4,LOW);
digitalWrite(R5,LOW);
digitalWrite(R6,LOW);

digitalWrite(R10,LOW);
digitalWrite(R11,LOW);
digitalWrite(R12,LOW);

digitalWrite(R13,LOW);
digitalWrite(R14,LOW);
digitalWrite(R15,LOW);
}
if(digitalRead (IS) == 1){sendSMS(phone_no,"I > !! SURINTENSITE");
delay(2);
sendSMS(phone_no,"Declanchement Depart 1&3");
digitalWrite(R1,LOW);
digitalWrite(R2,LOW);
digitalWrite(R3,LOW);

digitalWrite(R7,LOW);
digitalWrite(R8,LOW);
digitalWrite(R9,LOW);

}
if(digitalRead (U0) == 1){sendSMS(phone_no,"U0 MANQUE TENSION");}
if(digitalRead (UF) == 1){sendSMS(phone_no,"U < 75% DE LA TENSION NOMINALE ");
delay(2);
sendSMS(phone_no,"Declanchement Depart 3&4");
digitalWrite(R1,LOW);
digitalWrite(R2,LOW);
digitalWrite(R3,LOW);

digitalWrite(R4,LOW);
digitalWrite(R5,LOW);
digitalWrite(R6,LOW);

digitalWrite(R10,LOW);
digitalWrite(R11,LOW);
digitalWrite(R12,LOW);

digitalWrite(R13,LOW);
digitalWrite(R14,LOW);
digitalWrite(R15,LOW);

}
if(digitalRead (UM) == 1){sendSMS(phone_no,"U < 95% DE LA TENSION NOMINALE ");
sendSMS(phone_no,"Declanchement Depart 1&2");
digitalWrite(R1,LOW);
digitalWrite(R2,LOW);
digitalWrite(R3,LOW);

digitalWrite(R4,LOW);
digitalWrite(R5,LOW);
digitalWrite(R6,LOW);

}

delay(5);
}



void sendSMS(char *number, char *msg){
GSM.print("AT+CMGS=\"");GSM.print(number);GSM.println("\"\r\n"); //AT+CMGS=”Mobile Number” <ENTER> - Assigning recipient’s mobile number
delay(500);
GSM.println(msg); // Message contents
delay(500);
GSM.write(byte(26)); //Ctrl+Z  send message command (26 in decimal).
delay(500);  
}

void callUp(char *number){
GSM.print("ATD + "); GSM.print(number); GSM.println(";"); 
delay(200);       // wait for 20 seconds...
GSM.println("ATH"); //hang up
delay(200);  
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
       }else{Serial.println("Error");}}
    delay(t);
  }
}

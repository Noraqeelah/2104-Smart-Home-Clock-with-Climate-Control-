//Own transmitter code - Noraqilah
//need to include ir remote lib?
#include <IRremote.h>

// I/O
int SEND_PIN = 3;    //pin 3.2 - The pin where you connect RX output pin of IR sensor
IRsend irsend(SEND_PIN);             // IRsend irsend(SEND_PIN);
decode_results results;
int button1 =  73;  // pin 1.1 - S1
int button2 =  74; // pin 1.4 - S2


//Codes to send.Up to 8 bits so 0-255.
byte button1_CODE = 0x04;
byte button2_CODE = 0x08;


void setup() {
  Serial.begin(9600);            //Baud rate
  irsend.enableIROut(10);    //KHz
//  irsend.blink13(true);
  pinMode(button1,INPUT);      //input from Switch 1
  pinMode(button2,INPUT);     //input from Switch 2
  pinMode(3,OUTPUT);          //output from PIN 3.2 for DATA

}

void loop() {
// if one button is pressed, we send one byte corresponding to that button
  if(digitalRead(button1)== HIGH){
    Serial.write(button1_CODE);
    Serial.println("HIGH");
    delay(1000);                //Delay, so that it wont be send twice
  }
   if(digitalRead(button2)== LOW){
    Serial.write(button2_CODE);
    Serial.println("LOW");
    delay(1000);
  }
  
}

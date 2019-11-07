//https://circuitdigest.com/microcontroller-projects/arduino-motion-detector-using-msp430-launchpad-and-pir-sensor
//red led will turn on if an object detected
//detect 2-3 steps away
void setup()
{
  pinMode(2, INPUT);  //pin6.0
  pinMode(78, OUTPUT);  // led PIN 1.0
}
void loop()
{
  if(digitalRead(2) == HIGH)
  {
    Serial.print("Object detected\n\n");
    digitalWrite(78, HIGH);  
    delay(100);}
  else{
    Serial.print("No object in sight\n\n");
    digitalWrite(78, LOW);
    delay(100);
  }
}

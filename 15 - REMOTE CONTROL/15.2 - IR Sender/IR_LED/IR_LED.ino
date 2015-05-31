/***********************************************************
IRSend sketch
this code needs an IR LED connected to pin 3
button pin connected to pin 4
************************************************************/
#include <IRremote.h>        // IR remote control library
IRsend irsend;
int buttonPin = 4;              //button pin connected to pin 4
long irKeyCodes = 0xFFA25D;     //the code value of power off
void setup()
{
  digitalWrite(buttonPin, HIGH); // turn on pull-ups
}
void loop() {
  if(!digitalRead(buttonPin)){
    delay(2);
    while(!digitalRead(buttonPin));   //waiting for the button to realeased
    irsend.sendSony(irKeyCodes, 32);
  }
}

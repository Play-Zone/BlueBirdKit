#include <IRremote.h>
int RECV_PIN = 11;
int state = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();     // Start the receiver
  pinMode(13,OUTPUT);
}
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();        // Receive the next value
    if(results.value == 0xFFA25D){
      state = !state;
      digitalWrite(13,state);
    }
  }
}

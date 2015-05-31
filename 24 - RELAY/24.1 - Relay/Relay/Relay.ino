int relayPin = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(relayPin, OUTPUT);     
}

void loop() {
  digitalWrite(relayPin, HIGH);   
  delay(1000);             
  digitalWrite(relayPin, LOW);    
  delay(1000);             
}

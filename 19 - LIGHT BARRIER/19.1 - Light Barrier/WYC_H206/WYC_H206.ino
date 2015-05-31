volatile int count = 0;
void setup() {
  attachInterrupt(0,pulseCount,FALLING);
  Serial.begin(9600);
}

void loop() {
  Serial.println(count);
}
void pulseCount(){
  count ++;
}

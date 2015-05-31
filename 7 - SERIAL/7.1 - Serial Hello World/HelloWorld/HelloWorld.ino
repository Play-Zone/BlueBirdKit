String str = "Hello World!!!";
String str1 = "Welcome to ARDUINO!!!";
void setup()
{
  Serial.begin(9600);   
}
void loop(){
  Serial.println(str); 
  Serial.println(str1); 
  delay(1000);   
}

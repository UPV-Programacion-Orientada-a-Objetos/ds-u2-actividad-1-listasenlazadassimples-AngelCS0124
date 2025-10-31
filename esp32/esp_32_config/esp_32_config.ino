void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  float temp = random(200, 351) / 10.0;
  Serial.print("TEMP,T-001,"); 
  Serial.println(temp);
  delay(3000);
  
  int pres = random(80, 121);  
  Serial.print("PRES,P-001,"); 
  Serial.println(pres);
  delay(3000);
}
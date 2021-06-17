#define pulsePin A7

float pulseVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(pulsePin, INPUT);
  Serial.println("ADC");
  pulseVal = -1.0;
  delay(10000);
  for(int i=0; i < 1000; i++){
    pulseVal = analogRead(pulsePin);
    Serial.println(pulseVal);
    delay(10);
  }
  Serial.println("DONE!");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

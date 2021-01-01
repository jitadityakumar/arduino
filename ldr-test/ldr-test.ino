// LDR Test
// Board Arduino Uno

int LDR_PIN = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("LDR Read");
  Serial.println(analogRead(LDR_PIN));
  delay(2000);
}

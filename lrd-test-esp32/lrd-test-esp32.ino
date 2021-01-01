// LDR Test
// Board ESP32

int LDR_PIN = 33;

void setup() {
  // put your setup code here, to run once:
  adcAttachPin(LDR_PIN);
  Serial.begin(9600);
  Serial.println("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("LDR Read");
  int ldr_value = analogRead(LDR_PIN);
  Serial.println(ldr_value);
  delay(2000);
}

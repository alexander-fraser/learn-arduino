/*
  Blink Slow
  Alexander Fraser
  18 May 2020
  
  Blink the LED-13 at a slow rate.
*/

int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
  delay(2000);
}

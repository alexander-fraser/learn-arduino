/*
  Blink Progression
  Alexander Fraser
  18 May 2020
  
  Blinks the LED-13 at a progressively faster and then slower rate.
*/

int ledPin = 13;
int delayTime = 1000;

void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int x = 0; x <= 3; x++){
    // the LED turns on for progressively increments.
    digitalWrite(ledPin, HIGH);   // turn the LED on.
    delay(delayTime);             
    digitalWrite(ledPin, LOW);    // turn the LED off.
    delay(500);                   
  
    delayTime -= 250;
  }
    for (int x = 0; x <= 3; x++){
    // the LED turns on for progressively increments.
    digitalWrite(ledPin, HIGH);   // turn the LED on.
    delay(delayTime);             
    digitalWrite(ledPin, LOW);    // turn the LED off.
    delay(500);                   
  
    delayTime += 250;
  }
}

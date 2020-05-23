/*
  RGB Blink
  Alexander Fraser
  22 May 2020
  
  Blinks an RGB LED through all three primary colors.

  Setup:
    - Place the RGB LED on a breadboard.
    - Attach the common cathode pin to GND.
    - Connect each of the anode pins to a curent-limiting resistor
      and then to the digital output pins used by the code.
*/

int ledPins[] = {9,10,11};
int x;

void setup() {
  // Initialize the 3 output pins using a loop.
  for(x=0; x<3; x++) {
    pinMode(ledPins[x], OUTPUT);
  }
}

void loop() { 
  // Loop through each of the three pins and turn on the
  // color for 1 second each.
  for(x=0; x<3; x++) {
    digitalWrite(ledPins[x], HIGH); 
    delay(1000);
    digitalWrite(ledPins[x], LOW); 
  }
}

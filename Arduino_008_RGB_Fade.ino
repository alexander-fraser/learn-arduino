/*
  RGB Fade
  Alexander Fraser
  22 May 2020
  
  Fades through all the colors on an RGB LED.

  Setup:
    - Place the RGB LED on a breadboard.
    - Attach the common cathode pin to GND.
    - Connect each of the anode pins to a curent-limiting resistor
      and then to the digital output pins used by the code.
*/

int ledPins[] = {9,10,11};
int waningPin, waxingPin, offPin, x;
int delayTime = 10;

void setup() {
  // Initialize the 3 output pins using a loop.
  for(x=0; x<3; x++) {
    pinMode(ledPins[x], OUTPUT);
  }
}

void loop() { 
  // Loop through each of the three colors (on each of the pins).
  for(x=0; x<3; x++) {

    // Compute the references for each of the pins in the sequence.    
    waningPin = x;
    waxingPin = ((x+1) % 3);
    offPin = ((x+2) % 3);

    for (int ledValue = 0; ledValue <= 255; ledValue++){
      // Fade through each of the primary colors.
      // Done by setting the voltage of one color to 0 and then
      // grading the remaining voltage (255 in total) from one
      // pin to the next.
      analogWrite(ledPins[offPin], 0);
      analogWrite(ledPins[waningPin], 255 - ledValue);
      analogWrite(ledPins[waxingPin], ledValue); 
      delay(delayTime);
    }  

  }
}
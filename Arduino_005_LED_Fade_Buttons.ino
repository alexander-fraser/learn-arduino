/*
  LED Fade Buttons
  Alexander Fraser
  21 May 2020
  
  Fades an LED on digital pin 11 according to input from 2 buttons.

  Setup:
    - Place two buttons on a breadboard.
    - Connect one side of each of the buttons to GND.
    - Connect the other side of one of the buttons to digital pin 2.
    - Connect the other side of the other button to digital pin 3.
    - Place an LED with a current-limiting resistor on the board attached
      to digital pin 11 and GND.
*/

int ledPin = 11, onButtonPin = 2, offButtonPin = 3;
int ledState = 255, onButtonState, offButtonState;

void setup() {
  // Initialize the pins for the button inputs and LED output.
  // INPUT_PULLUP is used to pull the voltage of the pins to high
  // when the button is not depressed (i.e. connected to GND).
  // Otherwise it will float.
  pinMode(ledPin, OUTPUT);
  pinMode(onButtonPin, INPUT_PULLUP);
  pinMode(offButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Collect whether the buttons are pressed and print the state.
  onButtonState = digitalRead(onButtonPin);
  offButtonState = digitalRead(offButtonPin);

  Serial.println(String(onButtonState) + "," + String(offButtonState) + "," + String(ledState));

  // Increase the brightness while one button is pressed and
  // decrease the brightness while the other button is pressed.
  if(onButtonState == LOW){
    ledState++;
  }
  if(offButtonState == LOW){
    ledState--;
  }
  ledState = min(max(ledState, 0), 255);
  analogWrite(ledPin, ledState);
  delay(10);
}

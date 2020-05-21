/*
  Blink Buttons
  Alexander Fraser
  20 May 2020
  
  Blinks the LED-13 according to input from buttons.

  Setup:
    - Place two buttons on a breadboard.
    - Connect one side of each of the buttons to GND.
    - Connect the other side of one of the buttons to digital pin 2.
    - Connect the other side of the other button to digital pin 3.
*/

int ledPin = 13, onButtonPin = 2, offButtonPin = 3;
int ledState = HIGH, onButtonState, offButtonState;

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

  Serial.println(String(onButtonState) + "," + String(offButtonState));

  if(onButtonState == LOW){
    ledState = HIGH;
  }
  if(offButtonState == LOW){
    ledState = LOW;
  }

  digitalWrite(ledPin, ledState);
}

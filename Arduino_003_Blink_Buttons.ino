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

int buttonPin1 = 2;
int buttonPin2 = 3;
int ledPin = 13;
int button1State, button2State;

void setup() {
  // Initialize the pins for the button inputs and LED output.
  // INPUT_PULLUP is used to pull the voltage of the pins to high
  // when the button is not depressed (i.e. connected to GND).
  // Otherwise it will float.
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() { 
  // Collect whether the buttons are pressed and print the state.
  button1State = digitalRead(buttonPin1);
  button2State = digitalRead(buttonPin2);

  Serial.print(button1State);
  Serial.print(",");
  Serial.print(button2State);
  Serial.println("");

  // Turn the LED on when button 1 is pressed and off when 
  // button 2 is pressed. 
  if(button1State==LOW) {
    digitalWrite(ledPin, HIGH); 
  }
  if(button2State==LOW) {
    digitalWrite(ledPin, LOW); 
  }
}

/*
  LED Fade Potentiometer
  Alexander Fraser
  21 May 2020
  
  Fades an LED on digital pin 11 according to input from a potentiometer.

  Setup:
    - Place two buttons on a breadboard.
    - Connect one side of each of the buttons to GND.
    - Connect the other side of one of the buttons to digital pin 2.
    - Connect the other side of the other button to digital pin 3.
    - Place an LED with a current-limiting resistor on the board attached
      to digital pin 11 and GND.
*/

int ledPin = 11, potPin = A0;
int potLevel, ledBrightness;
float ledVoltage;

void setup() {
  // Initialize the input and output pins.
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  
  ledBrightness = 0;

  Serial.begin(9600);
}

void loop() {
  // Read the voltage across the potentiometer and remap the value
  // from 10-bit to 8-bit.
  potLevel = analogRead(potPin);
  ledBrightness = map(potLevel, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);

  // Compute and print the voltage supplied to the LED.
  ledVoltage = ledBrightness * (5.0 / 255.0);
  Serial.println(ledVoltage);
}

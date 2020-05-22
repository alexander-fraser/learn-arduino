/*
  LED Fade
  Alexander Fraser
  21 May 2020
  
  Fades an LED on digital pin 3 using PWM.
*/

int ledPin = 3;
int ledBrightness, ledFadeAmount;

void setup() {
  // Initializes the pins and sets the rate of fade.
  pinMode(ledPin, OUTPUT);
  ledBrightness = 0;
  ledFadeAmount = 5;
}

void loop() {
  // analogWrite takes a value from 0 to 255 for the duty
  // cycle of the PMW (between 0V and 5V).
  analogWrite(ledPin, ledBrightness);
  delay(25);

  ledBrightness = ledBrightness + ledFadeAmount;

  // Reverse the fade when the voltage reaches 0V or 5V.
  if (ledBrightness == 0 || ledBrightness == 255) {
    ledFadeAmount = -ledFadeAmount;
  }
}

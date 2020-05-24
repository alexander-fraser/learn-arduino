/*
  LED Fade Serial
  Alexander Fraser
  24 May 2020
  
  Allows the user to set the brightness of an LED using the serial monitor.

  Setup:
    - Place the LED on the breadboard and attach it to GND and the output pin,
      with a current-limiting resistor in the circuit.

*/

int ledPin = 9;

void setup(){
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  // Delay to allow time for serial monitor to open.
  delay(500);
  Serial.println("Enter LED brightness value from 0 to 255");
}

void loop(){
  if(Serial.available()){

    // Collect the user's input value.    
    int ledBrightness = Serial.parseInt();

    // Check to ensure that the serial packet has data.
    // If it does, then use it to set the LED brightness.
    if (Serial.available() > 0){
      analogWrite(ledPin, ledBrightness);
      Serial.println(ledBrightness);
    }
    
  }    
}
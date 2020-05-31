/*
  Seven Segment Display Count
  Alexander Fraser
  30 May 2020
  
  Uses a SN74HC595 shift register to control a seven-segment display.
  It counts up from 0 to 9 and repeats.

  The display has seven LEDs that light up to display the numeric digits 0-9.
  It also includes an eighth LED for a decimal.

  Setup:
    - Place the shift register on the breadboard.
    - Place the seven-segment display on the breadboard with a 
      current-limiting resistor connecting the cathode to GND.
    - Shift register pinout (numbers are counter-clockwise from 
      the half-moon cut-out):
        - 1-7:  Qb-Qh -> These are the output pins. Connect to LED anodes.
        - 8:    GND   -> Connect to GND.
        - 9:    Qh'   -> n/a
        - 10:   SRCLR -> Connect to 5V (connect to GND to clear the register).
        - 11:   SRCLK -> Connect to clockPin.
        - 12:   RCLK  -> Connect to latchPin.
        - 13:   OE    -> Connect to overridePin.
        - 14:   SER   -> Connect to dataPin.
        - 15:   Qa    -> This is the 8th output pin. Connect to LED anode.
        - 16:   VCC   -> Connect to 5V (SRCLK power can light LEDs).
    - Seven-segment display pinout (numbers are counter-clockwise from
      the bottom-left):
        - 1:    bottom-left
        - 2:    bottom
        - 3:    GND (common cathode)
        - 4:    bottom-right
        - 5:    decimal
        - 6:    top-right
        - 7:    top
        - 8:    GND (common cathode)
        - 9:    top-left
        - 10:   middle

*/

// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
// Corresponding to display:   12456790
// Corrsponding to register:   ABCDEFGH
byte seven_seg_digits[10] = { B11101110,  // = 0
                              B00101000,  // = 1
                              B11001101,  // = 2
                              B01101101,  // = 3
                              B00101011,  // = 4
                              B01100111,  // = 5
                              B11100111,  // = 6
                              B00101100,  // = 7
                              B11101111,  // = 8
                              B00101111   // = 9
                             };

int overridePin = 3, dataPin = 4, latchPin = 5, clockPin = 6;
int ledBrightness = 255;
boolean decimalIndicator = false;
 
void setup(){                     // Shift register pinout labels in datasheet:
  pinMode(overridePin, OUTPUT);   // OE
  pinMode(dataPin, OUTPUT);       // SER
  pinMode(latchPin, OUTPUT);      // RCLK
  pinMode(clockPin, OUTPUT);      // SRCLCK

  // Set the brightness of the display.
  analogWrite(overridePin, 255 - ledBrightness);

  Serial.begin(9600);
  delay(500);
  Serial.println("Enter a number from 0 to 9. Enter a ./, for decimal on/off.");
}

void loop() {
  // Asks for the user to give it a digit, which it then displays.
  if(Serial.available() > 0){

    // Collect the user input.
    byte inputByte = Serial.read();
    Serial.print(inputByte);

    // Turn on/off the decimal if user enters ./,
    if(inputByte == 46){
      decimalIndicator = true;
    }
    if (inputByte == 44){
      decimalIndicator = false;
    }

    // Convert the byte to an integer and check if it is within limits.
    byte digitByte = inputByte - '0';    
    if(digitByte >= 0 && digitByte <= 9){
      Serial.print(",");
      Serial.print(digitByte);
      byte outputByte = getByteCode(digitByte, decimalIndicator);
      sevenSegWrite(outputByte);
    }

    Serial.println(",");

  }  
}

void sevenSegWrite(byte displayDigits) {

  // Display a number on the digital segment display.
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, displayDigits);   // See "Arduino_010 sketch for a breakout of the shiftOut function".
  digitalWrite(latchPin, HIGH);

  // Print the bytecode for the display pinout.
  Serial.print(",");
  Serial.print(displayDigits, BIN);

}

byte getByteCode(byte digit, boolean decimalIndicator){

  // Look up the bytecode corresponding to the digit from the table.
  byte displayDigits = seven_seg_digits[digit];

  // Add the decimal, if selected.
  if(decimalIndicator == true){
    displayDigits = bitWrite(displayDigits, 4, 1);    
  }
  else{
    displayDigits = bitWrite(displayDigits, 4, 0);
  }

  return displayDigits;
}
/*
  Seven Segment Display
  Alexander Fraser
  24 May 2020
  
  Uses a SN74HC595 shift register to control a seven-segment display.
  Displays the digit entered by the user.

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
  Serial.println("Enter a number from 0 to 9.");
}

void loop() {
  // Asks for the user to give it a digit, which it then displays.
  if(Serial.available()){
    int userDigit = Serial.parseInt();

    // Check to ensure that the serial packet has data.
    if (Serial.available() > 0){
      byte byteCode = getByteCode(userDigit, decimalIndicator);
      sevenSegWrite(userDigit, byteCode);
    }

  }  
}

void sevenSegWrite(int userDigit, byte displayDigits) {
  // Display a number on the digital segment display.

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, displayDigits);   // See "Arduino_010 sketch for a breakout of the shiftOut function".
  digitalWrite(latchPin, HIGH);

  // Print the bytecode for the display pinout.
  Serial.print(userDigit);
  Serial.print(",");
  Serial.println(displayDigits, BIN);

}

byte getByteCode(int digit, boolean decimalIndicator){
  // Look up the bytecode corresponding to the digit from the table.

  byte displayDigits;

  // Add the decimal, if selected.
  if(decimalIndicator){
    displayDigits = bitSet(seven_seg_digits[digit], 4);    
  }
  else{
    displayDigits = seven_seg_digits[digit];
  }
  return displayDigits;

}
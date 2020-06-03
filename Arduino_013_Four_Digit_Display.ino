/*
  Four Digit Display
  Alexander Fraser
  2 June 2020
  
  Uses a SN74HC595 shift register to control a foud-digit seven-segment 
  display. Displays the four integers specified in the loop function.

  The display has four sets of seven LEDs that light up to display the 
  numeric digits 0-9. They each have an eighth LED for a decimal.

  Setup:
    - Place the shift register on the breadboard.
    - Place the four-digit seven-segment display on the breadboard.
    - Connect each of the 4 GND pins on the display to the arduino
      pins using a 220 ohm current-limiting resistor.
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
        - 3:    decimal
        - 4:    bottom-right
        - 5:    middle
        - 6:    GND 4     -> Connect to displayPin4
        - 7:    top-right
        - 8:    GND 3     -> Connect to displayPin3
        - 9:    GND 2     -> Connect to displayPin2
        - 10:   top-left
        - 11:   top
        - 12:   GND 1     -> Connect to displayPin1

*/

// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
// Corresponding to display:   123457AB
// Corrsponding to register:   ABCDEFGH           HEX
byte seven_seg_digits[10] = { B11010111,  // = 0  D7
                              B00010100,  // = 1  14
                              B11001101,  // = 2  CD
                              B01011101,  // = 3  5D
                              B00011110,  // = 4  1E
                              B01011011,  // = 5  5B
                              B11011011,  // = 6  DB
                              B00010101,  // = 7  15
                              B11011111,  // = 8  DF
                              B00011111   // = 9  1F
                             };

unsigned char digits_hex[]= {   0xd7,   // = 0
                                0x14,   // = 1
                                0xcd,   // = 2
                                0x5d,   // = 3
                                0x1e,   // = 4
                                0x5b,   // = 5
                                0xdb,   // = 6
                                0x15,   // = 7
                                0xdf,   // = 8
                                0x1f    // = 9
                              };

int overridePin = 3, dataPin = 4, latchPin = 5, clockPin = 6;
int displayPin[] = {9, 10, 11, 12};
 
void setup(){                       // Shift register pinout labels in datasheet:
  pinMode(overridePin, OUTPUT);     // OE
  pinMode(dataPin, OUTPUT);         // SER
  pinMode(latchPin, OUTPUT);        // RCLK
  pinMode(clockPin, OUTPUT);        // SRCLCK
  
  for(int x = 0; x < 4; x++){
    pinMode(displayPin[x], OUTPUT); // GND pins 1-4
  }
}

void loop() {

  // Lights every segment in the display.
//  writeSameDigit(8);   

  // Displays four digits, based on the input passed (in HEX).
  int digits[] = {1, 2, 3, 4};
  writeFourDigits(digits);

}

void writeSameDigit(int reference){
  // Takes a single byte passed to it (in HEX) and displays it for all digits.
  unsigned char digit = digits_hex[reference];
  sevenSegWrite(digit);
  for(int x = 0; x < 4; x++){
    digitalWrite(displayPin[x], LOW); 
  }
}

void writeFourDigits(int digits[]){
  // Takes an array of four bytes passed to it (in HEX) and displays them.
  for(int x = 0; x < 4; x++){
    unsigned char digit = digits_hex[digits[x]];
    sevenSegWrite(digit);
    digitalWrite(displayPin[x], LOW);
    delay(5);
    digitalWrite(displayPin[x], HIGH);
  }
}

void sevenSegWrite(byte displayDigits) {
  // Display a number on the digital segment display.
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, displayDigits);   // See "Arduino_010 sketch for a breakout of the shiftOut function".
  digitalWrite(latchPin, HIGH);
}
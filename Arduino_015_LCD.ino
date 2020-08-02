/*
  LCD
  Alexander Fraser
  2 August 2020
  
  Demonstrates the use of a 16x2 LCD display. This sketch prints "Hello World!"
  to the LCD.

  Requirements:
    - LiquidCrystal.h library

  Setup:
    - Place the LCD display breakout board on the breadboard.
    - LCD driver pinout (order is from left to right on the board):
        - 1     VSS     -> Connect to GND.
        - 2     VDD     -> Connect to 5V.
        - 3     VO      -> Connect to GND using a 220 ohm current-limiting resistor.
        - 4     RS      -> Connect to digital pin 7. Register selection (data input = HIGH, instruction input = LOW).
        - 5     RW      -> Connect to GND. Read/write setting (read = HIGH, write = LOW).
        - 6     E       -> Connect to digital pin 8. Enables data transfer when HIGH.
        - 7-10  D0-D3   -> n/a (used for 8-bit data transfers). 
        - 11-14 D4-D7   -> Connect to digital pins 9-12, respectively.
        - 15     A      -> Connect to 5V (powers the backlight).
        - 16     K      -> Connect to GND using a 220 ohm current-limiting resistor (powers the backlight).
*/

#include <LiquidCrystal.h> 

// initialize the library with the numbers of the interface pins.
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  

void setup() {
  lcd.begin(16, 2);             // Set up the LCD's number of columns and rows. 
  lcd.print("Hello World!");    // Print a message to the LCD.
}

void loop() {
}



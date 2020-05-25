/*
  LED Shift Register
  Alexander Fraser
  24 May 2020
  
  Uses a SN74HC595 shift register to control 8 LEDs and count through
  the 8-bit integers (from 0 to 255) in binary.

  The code below will provide the chip with serial communication for lighting
  the LEDs, which will be converted to parallel instructions by the chip.

  Setup:
    - Place the shift register on the breadboard.
    - Place 8 LEDs on the breadboard with current-limiting resistors connecting
      them to GND.
    - Pinout (numbers are counter-clockwise from the half-moon cut-out):
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
*/

int overridePin = 3, dataPin = 4, latchPin = 5, clockPin = 6;
int ledBrightness = 255;

void setup(){                     // Shift register pinout labels in datasheet:
  pinMode(overridePin, OUTPUT);   // OE
  pinMode(dataPin, OUTPUT);       // SER
  pinMode(latchPin, OUTPUT);      // RCLK
  pinMode(clockPin, OUTPUT);      // SRCLCK
  Serial.begin(9600);
}

void loop(){
  // Set the brightness of the LEDs.
  analogWrite(overridePin, 255 - ledBrightness);

  // Loop through all 256 integers that can be represented in 8-bit binary.  
  for (int x = 0; x < 255; x++){
    Serial.println(String(x));
    manualUpdateShiftRegister(x);
    delay(100);
  }
}

void manualUpdateShiftRegister(int leds){ 
  int bitValue;
  digitalWrite(latchPin, LOW);
  
  // Increment through the 8 bits in the input (least-significant bit first).
  for (int x = 0; x < 8; x++){   
    digitalWrite(clockPin, LOW);     
    
    // Read the current bit from the input value.
    bitValue = bitRead(leds, x);    
    
    // If the bit is on, send the value HIGH. Otherwise, send LOW.
    if(bitValue == 1){
      digitalWrite(dataPin, HIGH);   
    }
    else{
      digitalWrite(dataPin, LOW);
    }

    // The clock is advanced forward.
    digitalWrite(clockPin, HIGH);   
  }
  
  // The values are written to the register, which changes the output signals.
  digitalWrite(latchPin, HIGH);   
}
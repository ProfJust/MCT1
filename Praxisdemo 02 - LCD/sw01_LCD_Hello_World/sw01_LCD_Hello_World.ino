// sw01_LCD_Hello_World.ino
  
  /*  LiquidCrystal Library - Hello World
      Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
   library works with all LCD displays that are compatible with the
   Hitachi HD44780 driver. There are many of them out there, and you
   can usually tell them by the 16-pin interface.
   
   This sketch prints "Hello World!" to the LCD
   and shows the time.
  
    http://www.arduino.cc/en/Tutorial/LiquidCrystal
   */
   
   // include the library code:
  #include <LiquidCrystal.h>
  
  // initialize the library with the numbers of the interface pins
  //     LCD Pins   RS EN D4 D5 D6 D7
  // D-SUB-Stecker Nr  5  6  1  2  3  4 
  // Arduino Pin Nr   D4 D5 D0 D1 D2 D3  (Stecker J2)
  LiquidCrystal lcd( 4, 5, 0, 1, 2, 3);  //Version für LCD an J2 
  //    Achtung!! Bei EB092 an Programm Schalter denken
  //  LiquidCrystal lcd(28,29,24,25,26,27);  //Version für LCD an J20 PinNr.+24
  //  LiquidCrystal lcd(15,14,19,18,17,16);  //Version für LCD an J5 
  //  LiquidCrystal lcd(12,13, 8, 9,10,11);  //Version für LCD an J3 
    
void setup() {    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);    
    // Print a message to the LCD.
    lcd.print("Hello, World! ");
  }
    
  void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis() / 1000);
  }




#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#include <Stepper.h>
// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 10, 12, 11, 13);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup(){
  lcd.backlight();
  lcd.init(); 

  myStepper.setSpeed(10);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
  
}

void loop(){
  char customKey = customKeypad.getKey();
  if (customKey){
    if(customKey==65)
        {
          lcd.clear();
          lcd.setCursor(0, 0); 
          lcd.print(customKey);
          Serial.println("clockwise");
          myStepper.step(stepsPerRevolution);
        }
    if(customKey==66)
        {
          lcd.clear();
          lcd.setCursor(0, 0); 
          lcd.print(customKey);
          Serial.println("counterclockwise");
          myStepper.step(-stepsPerRevolution);
          }
      
  
  }

  
}

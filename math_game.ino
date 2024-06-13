// This code show a simple math game using a 4x4 keyboard and 
// LCD display with I2C.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Define the size of the keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad ROW0, ROW1, ROW2, ROW3 to these Arduino pins
byte rowPins[ROWS] = {9, 8, 7, 6}; 

// Connect keypad COL0, COL1, COL2, COL3 to these Arduino pins
byte colPins[COLS] = {5, 4, 3, 2}; 

// Create the Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);


String userAnswer = ""; // Variable to store the user's input


void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  randomSeed(analogRead(0));

  lcd.setCursor(2, 0);
  lcd.print("Let's play");
  lcd.setCursor(2, 1);
  lcd.print("a math game.");
  delay(3000);
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("Enter the");
  lcd.setCursor(0, 1);
  lcd.print("correct answer");
  delay(3000);
  lcd.clear();
}

void loop() {
  // Display the question
  int numberX = random(10, 99);
  int numberY = random(10, 99);
  
  lcd.setCursor(2,0);
  lcd.print("Solve");
  lcd.setCursor(8,0);
  lcd.print(numberX);
  lcd.setCursor(10,0);
  lcd.print("+");
  lcd.setCursor(11,0);
  lcd.print(numberY);

  int correctAnswer = numberX + numberY;
  
  bool answerVerified = false;
  
  while (!answerVerified) {
    char key = keypad.getKey();
  
    if (key) { // Check if a key is pressed
      if (key == '#') {
        // Print the collected input when '#' is pressed
        int userAnswerInt = userAnswer.toInt(); // Convert the input to an integer

        lcd.clear();

        // Check if the answer is correct
        if (userAnswerInt == correctAnswer) {
          lcd.setCursor(0, 0);
          lcd.print("Correct! The");
          lcd.setCursor(0, 1);
          lcd.print("answer is");
          lcd.setCursor(10, 1);
          lcd.print(correctAnswer);
        
      } else {
          lcd.setCursor(0, 0);
          lcd.print("Wrong! The");
          lcd.setCursor(0, 1);
          lcd.print("answer is");
          lcd.setCursor(10, 1);
          lcd.print(correctAnswer);
      }

      delay(5000); // Wait for 5 seconds before restarting the loop
      lcd.clear();
      userAnswer = ""; // Clear the input string for the next question
      answerVerified = true;
    } else {
      userAnswer += key; // Append the pressed key to the input string
      lcd.setCursor(3, 1);
      lcd.print(userAnswer); // Display the current input
      }
    }
  }  
}

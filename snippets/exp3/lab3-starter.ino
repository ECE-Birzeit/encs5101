// lab3-starter.ino: Lab work 3. Fill in the three TODOs.
// Keypad wired as in Example 3 (pins 22..28).

#include <Keypad.h>
#include <string.h>

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const char PASSWORD[] = "1234";
char typed[5];                       // up to 4 digits, plus the '\0' that ends a string
byte n = 0;                          // how many digits have been typed

void setup() {
  Serial.begin(9600);
  Serial.println("Enter the password, then #");
}

void loop() {
  char key = keypad.getKey();
  if (key == NO_KEY) return;         // nothing pressed

  if (key >= '0' && key <= '9' && n < 4) {
    // TODO 1: store key in typed[n], then add 1 to n
    Serial.print('*');               // show a star, not the digit
  }

  if (key == '#') {
    typed[n] = '\0';                 // end the string
    Serial.println();
    // TODO 2: if typed is the same as PASSWORD print "Hello", otherwise "Wrong password"
    // TODO 3: set n back to 0, so the next attempt starts empty
  }
}

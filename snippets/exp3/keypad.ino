// keypad.ino: print every key pressed on a 4x3 keypad to the Serial Monitor
// Needs the "Keypad" library by Mark Stanley and Alexander Brevig.

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};

byte rowPins[ROWS] = {22, 23, 24, 25};   // R1..R4
byte colPins[COLS] = {26, 27, 28};       // C1..C3

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial.println("Press a key:");
}

void loop() {
  char key = keypad.getKey();     // NO_KEY if nothing was pressed
  if (key != NO_KEY) {
    Serial.println(key);
  }
}

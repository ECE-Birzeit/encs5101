// lcd-hello.ino: text on a 16x2 I2C LCD, and a seconds counter on its second row.
// Wired as for scanner.ino. Library: "LiquidCrystal I2C" by Frank de Brabander.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // address from the scanner, 16 columns, 2 rows

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);                // column 0, row 0
  lcd.print("Hello, BZU!");
}

void loop() {
  lcd.setCursor(0, 1);                // column 0, row 1
  lcd.print("Uptime: ");
  lcd.print(millis() / 1000);
  lcd.print(" s");
  delay(200);
}

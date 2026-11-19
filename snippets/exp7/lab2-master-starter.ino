// lab2-master-starter.ino: Lab work 2, the master board. Fill in TODO 2, 3 and 4.
// LCD as in Example 2. SDA (20), SCL (21) and GND also wired to the slave board.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte SLAVE_ADDRESS = 8;
LiquidCrystal_I2C lcd(0x27, 16, 2);   // your LCD's address from the scanner

void setup() {
  Wire.begin();                    // the master: no address
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  Wire.requestFrom(SLAVE_ADDRESS, (byte)2);   // ask the slave for 2 bytes
  if (Wire.available() == 2) {
    byte high = Wire.read();       // first byte: the high byte
    byte low = Wire.read();        // second byte: the low byte

    int reading = 0;               // TODO 2: put high and low back together
    float volts = 0;               // TODO 3: convert reading (0..1023) to volts (0..5)

    Serial.print(reading);
    Serial.print("  ");
    Serial.println(volts);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading: ");
    lcd.print(reading);
    lcd.setCursor(0, 1);
    // TODO 4: print "Volts: " and then volts on this row
  }
  delay(500);
}

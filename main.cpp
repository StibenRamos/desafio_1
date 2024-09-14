#include <LiquidCrystal.h>

int seconds = 0;
int analogPin = 0;
int val = 0;

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Odio esto");
}

void loop()
{
  val = analogRead(analogPin);
  Serial.println(val);
  lcd_1.setCursor(0, 1);
  lcd_1.print(seconds);
  delay(1000);
  seconds += 1;
}
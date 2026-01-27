#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(A0,INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, user! ^-^");
}

void loop() {
  lcd.clear();
  float T=analogRead(A0);
  float t=100*((1.1/1023)*T);
  lcd.setCursor(0,0);
  lcd.print(t);
  Serial.println(t);
  delay(1000);
}

#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  byte temperature = 0;
  byte humidity = 0;
  int err = dht11.read(&temperature, &humidity, NULL);
  if (err != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(2000);
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print((int)temperature); lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: "); lcd.print((int)humidity); lcd.print(" %");
  Serial.print("Temp = "); Serial.print((int)temperature);
  Serial.print(" C, Humidity = "); Serial.print((int)humidity);
  Serial.println(" %");
  delay(2000);
}


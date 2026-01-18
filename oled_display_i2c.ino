#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3C 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  delay(250);
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.display();

  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 25);
  display.println("Starting...");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  static float voltage = 10.0;
  voltage += random(-5, 6) * 0.01;
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Ahnaf Hossain");

  display.setTextSize(1);
  display.setCursor(0, 15);
  display.println("EEE, AUST");

  display.drawLine(0, 28, 127, 28, SH110X_WHITE);

  display.setTextSize(2);
  display.setCursor(0, 40);
  display.print("V = ");
  display.print(voltage, 2);
  display.println("V");

  static int x = 0;
  display.fillCircle(110 + sin(x * 0.1) * 10, 20, 3, SH110X_WHITE);
  x++;
  display.display();
  delay(1000);
}

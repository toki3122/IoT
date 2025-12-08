/*********************************************************************
  Custom SH1106 OLED Display Example
  ----------------------------------
  Shows your name, university, and a simulated sensor voltage value
  on an SH1106 128x64 OLED display using I2C.

  Based on Adafruit's SH110X example by Ladyada and Rupert Hirst.
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// ---- OLED Setup ----
#define i2c_Address 0x3C        // Usually 0x3C (or try 0x3D if blank)
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

  // Optional: show startup screen
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(20, 25);
  display.println("Starting...");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  static float voltage = 10.0;    // simulated sensor reading
  voltage += random(-5, 6) * 0.01; // vary voltage a little for animation

  // --- Clear previous frame ---
  display.clearDisplay();

  // --- Title / Name ---
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Ahnaf Hossain");

  // --- University name ---
  display.setTextSize(1);
  display.setCursor(0, 15);
  display.println("EEE, AUST");

  // --- Draw line separator ---
  display.drawLine(0, 28, 127, 28, SH110X_WHITE);

  // --- Show voltage (example sensor data) ---
  display.setTextSize(2);
  display.setCursor(0, 40);
  display.print("V = ");
  display.print(voltage, 2);
  display.println("V");

  // --- Optional circle animation ---
  static int x = 0;
  display.fillCircle(110 + sin(x * 0.1) * 10, 20, 3, SH110X_WHITE);
  x++;

  // --- Display everything ---
  display.display();

  delay(1000);
}

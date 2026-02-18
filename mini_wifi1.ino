#include <WiFi.h>

char ssid[] = "8888";
char password[] = "tokee3122";

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  WiFi.disconnect(true);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);          // critical for ESP32-C3
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {}

#include <WiFi.h>
char* ssid="Tokee";
char* password="tokee0267";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.print("Connecting to WiFi");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());
}
void loop() {}

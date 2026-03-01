#include <esp_now.h>
#include <WiFi.h>
int int_value;
float float_value;
bool bool_value = true;
// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0xA0, 0xF2, 0x62, 0xA4, 0x00, 0x88};
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
struct_message myData;
esp_now_peer_info_t peerInfo;
void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;       // fixed channel
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  randomSeed(esp_random());
}
void loop() {
  int_value = random(1, 20);
  float_value = 1.3 * int_value;
  bool_value = !bool_value;
  strcpy(myData.a, "Welcome to the Workshop!");
  myData.b = int_value;
  myData.c = float_value;
  myData.d = bool_value;
  esp_err_t result = esp_now_send(
    broadcastAddress,
    (uint8_t *) &myData,
    sizeof(myData)
  );
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  } else {
    Serial.println("Sending error");
  }
  delay(2000);
}
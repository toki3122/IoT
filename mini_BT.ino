#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define LED_PIN 8

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHAR_UUID           "abcdefab-1234-5678-1234-abcdefabcdef"

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) {
    String value = pChar->getValue();
    if (value.length() > 0) {
      if (value[0] == '1') digitalWrite(LED_PIN, HIGH);
      if (value[0] == '0') digitalWrite(LED_PIN, LOW);
    }
  }
};

void setup() {
  pinMode(LED_PIN, OUTPUT);

  BLEDevice::init("ESP32_LED");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pChar = pService->createCharacteristic(
    CHAR_UUID,
    BLECharacteristic::PROPERTY_WRITE
  );

  pChar->setCallbacks(new MyCallbacks());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
}

void loop() {}

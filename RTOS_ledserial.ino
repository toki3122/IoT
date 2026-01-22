#include <Arduino_FreeRTOS.h>
void task_controlled(void *param);
void task_print(void *param);
TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  xTaskCreate(task_controlled,"Task1",100,NULL,1,&TaskHandle1);
  xTaskCreate(task_print,"Task2",100,NULL,1,&TaskHandle2);
}
void loop() {}
void task_controlled(void *param){
  (void) param;
  while(true){
    digitalWrite(13,digitalRead(8));
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void task_print(void *param){
  (void) param;
  while(true){
    Serial.println("led");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

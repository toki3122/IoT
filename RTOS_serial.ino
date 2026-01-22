#include <Arduino_FreeRTOS.h>
void task_print1(void *param);
void task_print2(void *param);
TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xTaskCreate(task_print1,"Task1",100,NULL,1,&TaskHandle1);
  xTaskCreate(task_print2,"Task2",100,NULL,2,&TaskHandle2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void task_print1(void *param){
  (void) param;
  while(true){
    Serial.println("Task1");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void task_print2(void *param){
  (void) param;
  while(true){
    Serial.println("Task2");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
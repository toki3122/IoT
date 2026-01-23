#include <Arduino_FreeRTOS.h>
void task_controlled(void *param);
void task_print(void *param);
void task_print1(void *param);
TaskHandle_t TaskHandle1;
TaskHandle_t TaskHandle2;
TaskHandle_t TaskHandle3;
uint32_t count;
void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT);
  xTaskCreate(task_controlled,"Task1",100,NULL,1,&TaskHandle1);
  xTaskCreate(task_print,"Task2",100,NULL,1,&TaskHandle2);
  xTaskCreate(task_print1,"Task3",100,NULL,1,&TaskHandle3);
}
void loop() {}
void task_controlled(void *param){
  (void) param;
  TickType_t getTick;
  getTick=xTaskGetTickCount();
  while(true){
    digitalWrite(13,digitalRead(8));
    vTaskDelayUntil(&getTick,1000/portTICK_PERIOD_MS);//better delay method
  }
}
void task_print(void *param){
  (void) param;
  while(true){
    count++;
    Serial.println("led");
    if(count==15)
      vTaskResume(TaskHandle3);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
void task_print1(void *param){
  (void) param;
  while(true){
    count++;
    Serial.println("works");
    if(count==10){
      //vTaskDelete(TaskHandle3);//deletes taskhandle 3
      vTaskSuspend(TaskHandle3);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

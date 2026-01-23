#include <Arduino_FreeRTOS.h>
void task_print(void *param);
void task_print1(void *param);
TaskHandle_t TaskHandle2;
TaskHandle_t TaskHandle3;
// if there are multiple tasks, the tasks might miss..
volatile int a;
volatile bool mymutex=false;
void setup() {
  Serial.begin(9600);
  xTaskCreate(task_print,"Task2",100,NULL,1,&TaskHandle2);
  xTaskCreate(task_print1,"Task3",100,NULL,1,&TaskHandle3);
}
void loop() {}
void task_print(void *param){
  (void) param;
  while(true){
    while(mymutex==true);
    for(a=0;a<5;a++){
    Serial.println(a);
    vTaskDelay(50/portTICK_PERIOD_MS);
    }
    mymutex=true;
  }
}
void task_print1(void *param){
  (void) param;
  while(true){
    while(mymutex==false);
    for(a=0;a<5;a++){
    Serial.println(a);
    vTaskDelay(50/portTICK_PERIOD_MS);
    }
    mymutex=false;
  }
}

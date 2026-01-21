#include <ESP32Servo.h>
Servo myservo;
void setup() {
  myservo.attach(18);
  myservo.write(0);
}

void loop() {

for (int t=0;t<=180;t+=15) {
  myservo.write(t);
  delay(15);
}delay(100);
for (int t=180;t>=0;t-=15) {
  myservo.write(t);
  delay(15);
}
}
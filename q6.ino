#define led1 4
#define led2 5
void setup() {
int A,a[3];
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
Serial.begin(9600);
delay(100);
Serial.print("enter A: ");
while(!Serial.available()){}
delay(100);
A=Serial.parseInt();
Serial.println(A);
for(int i=0;i<3;i++){
  a[i]=A%10;
  A/=10;
}
if(a[2]>a[0]){
  for(int i=0;i<a[1];i++){
    digitalWrite(led1,HIGH);
    delay(1000);
    digitalWrite(led1,LOW);
    delay(1000);
  }
}
else if(a[2]<a[0]){
  for(int i=0;i<a[1];i++){
    digitalWrite(led2,HIGH);
    delay(1000);
    digitalWrite(led2,LOW);
    delay(1000);
  }
}
else{
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  }
}
void loop() {}

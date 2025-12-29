void setup() {
int A,B;
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
Serial.begin(9600);
delay(100);
Serial.print("enter A: ");
while(!Serial.available()){}
delay(100);
A=Serial.parseInt();
Serial.println(A);
Serial.print("enter B: ");
while(!Serial.available()){}
delay(100);
B=Serial.parseInt();
Serial.println(B);
if(A%B==0){
digitalWrite(4,HIGH);
digitalWrite(5,LOW);
}
else{
digitalWrite(4,LOW);
digitalWrite(5,HIGH);
}
}
void loop() {}

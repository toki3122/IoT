void setup() {
  pinMode(2,OUTPUT);
  pinMode(4,INPUT);
  //Serial.begin(9600);
}
int touchval;
void loop(){
  touchval=touchRead(4);
  //Serial.println(touchval);
  if(touchval<=512){
    digitalWrite(2,HIGH);
  }
  else{
    digitalWrite(2,LOW);
  }
}

void setup()
{
  int a,c,b;
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("enter first value: ");
    while(Serial.available()==0){}
  a=Serial.parseInt();
  Serial.println(a,DEC);
  Serial.println("enter second value: ");
    while(Serial.available()==0){}
  b=Serial.parseInt();
  Serial.println(b,DEC);
  c=a+b;
  Serial.println("result:");
  Serial.println(c,DEC);
  Serial.println(c,BIN);
  Serial.println(c,HEX);
  for(int i=1;i<=c;i++){
    digitalWrite(13,!digitalRead(13));
    delay(1000);
  }
}

void loop()
{
  
}

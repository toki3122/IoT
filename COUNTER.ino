byte luptable[]={0x3f,0x06,0x5b,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x0f};
int value=0;
void setup() {
  pinMode(5,INPUT_PULLUP);
  DDRB=0b111111;
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0,OUTPUT);
  digitalWrite(A0,0);
  PORTB=luptable[0];
  digitalWrite(6,bitRead(luptable[0],6));
  digitalWrite(7,bitRead(luptable[0],7));
  delay(100);
}
void loop() {
  if(digitalRead(5)==LOW && value!=0x0f){
    delay(200);
    value++;
    PORTB=luptable[value];
    digitalWrite(6,bitRead(luptable[value],6));
    digitalWrite(7,bitRead(luptable[value],7));
  }
  else if(digitalRead(5)==LOW && value==0x0f){
    delay(200);
    value=0;
    PORTB=luptable[0];
    digitalWrite(6,bitRead(luptable[0],6));
    digitalWrite(7,bitRead(luptable[0],7));
  }
}
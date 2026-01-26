byte luptable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void setup() {
  int sum=0x1234+0x5678;
  byte d[4];
  byte ccd[4];
  DDRB=0b111111;
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0,OUTPUT);
  digitalWrite(A0,0);
  for(int i=0;i<4;i++){
    d[i]=sum%16;
    sum/=16;
  }
  for(int i=0;i<4;i++){
    ccd[i]= luptable[d[3-i]];
    PORTB=ccd[i];
    digitalWrite(6,bitRead(ccd[i],6));
    digitalWrite(7,bitRead(ccd[i],7));
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

byte luptable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int sum=0x17+0x19;
  byte d[2];
  byte ccd[2];
void setup() {
  DDRB=0b111111;
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(A0,OUTPUT);
  digitalWrite(A0,1);
  for(int i=0;i<2;i++){
    d[i]=sum%16;
    sum/=16;
  }
}

void loop() {
    ccd[0]= luptable[d[0]];
    PORTB=~ccd[0];
    digitalWrite(6,!bitRead(ccd[0],6));
    digitalWrite(7,!bitRead(ccd[0],7));
    delay(10);
    ccd[1]= luptable[d[1]];
    PORTB=~ccd[1];
    digitalWrite(6,!bitRead(ccd[1],6));
    digitalWrite(7,!bitRead(ccd[1],7));
    delay(10);
  }

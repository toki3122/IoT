void setup() {
    DDRB=0b111111;
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(A0,OUTPUT);
    PORTB=0b101111;
    digitalWrite(6,1);
    digitalWrite(7,0);
    digitalWrite(A0,0);
    // byte y=0x66;
    // PORTB=y;
    // digitalWrite(6,bitRead(y,6));
    // byte y7=bitRead(y,7);
    // digitalWrite(7,y7);
}

void loop() {
  // put your main code here, to run repeatedly:

}

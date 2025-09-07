//this version of LDR control is done using a relay
uint8_t threshold=0;
unsigned int sum=0;
for(int i=0;i<1000;i++){
	sum+=analogRead(A0);
	delay(10);
}
threshold=sum/1000;
void setup() {
  pinMode(3, OUTPUT);
}
void loop() {
	if (analogRead(A0) < threshold) {
  digitalWrite(3,1); 
	} 
  else{
    digitalWrite(3,0);
  }
  delay(1000);
}

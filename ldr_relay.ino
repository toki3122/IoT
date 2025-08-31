//this version of LDR control is done using a relay
int thresholdHigh = 530;
int thresholdLow = 490;
//calibration can be done to set the the high and low value
void setup() {
  pinMode(3, OUTPUT);
}
void loop() {
	if (analogRead(A0) < thresholdLow) {
  digitalWrite(3,1); 
	} 
	else if (analogRead(A0) > thresholdHigh) {
  digitalWrite(3,0); 
	}

  else{
    digitalWrite(3,0);
  }
  delay(1000);
}

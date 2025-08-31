//led control v1
void setup()
{
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop()
{
  unsigned int brightness = map(analogRead(A0),0,1023,0,255);
  analogWrite(3, brightness);
  delay(1000);
  analogWrite(3,0);
  analogWrite(5,brightness);
  delay(1000);
  analogWrite(5,0);
  analogWrite(6,brightness);
  delay(1000);
  analogWrite(6,0);
  analogWrite(9,brightness);
  delay(1000);
  analogWrite(9,0);
  analogWrite(10,brightness);
  delay(1000);
  analogWrite(10,0);
}

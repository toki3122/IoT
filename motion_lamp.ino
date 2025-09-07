//motion activation
int threshold=0;
for(int i=0;i<1000;i++){
	sum+=analogRead(A0);
	delay(10);
}
threshold=sum/1000;
void setup()
{
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(57600);
  Serial.println("Sensor readings:");
}

void loop()
{
  if (analogRead(A0)>=threshold)
  {
    Serial.println("Motion detected! Turning on the light.");
    Serial.println(pirsensor);
    digitalWrite(13, HIGH);
    delay(5000);
    digitalWrite(13, LOW);
  }
  else
  {
    digitalWrite(13,LOW);
  }

  delay(10);
}

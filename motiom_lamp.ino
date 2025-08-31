//motion activation
int pirsensor=0;

void setup()
{
  pinMode(3,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(57600);
  Serial.println("Sensor readings:");
}

void loop()
{
  int pirsensor=analogRead(3);

  if (pirsensor>=512)
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

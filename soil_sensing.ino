int water;
void setup() {
  pinMode(3,INPUT);
  pinMode(5,OUTPUT);
}

void loop() { 
  water = analogRead(A0);
  if(water>=512) 
  {
  analogWrite(5,0);
  }
  else if(water<=512 && water>=256)
  {
  analogWrite(5,150);
  }
  else
  {
  analogWrite(5,255);
  }
  delay(400); 
}

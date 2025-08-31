#define lmf 4
#define lmb 5
#define lms 3
#define rmf 6
#define rmb 7
#define rms 11
#define ls 10
#define rs 9
void motor(int a, int b)
{
  if(a>0)
  {
	digitalWrite(lmf,1);
  digitalWrite(lmb,0);
  }
  else
  {a=-a;
	digitalWrite(lmf,0);
  digitalWrite(lmb,1);
  }
  if(b>0)
  {
	digitalWrite(rmf,1);
  digitalWrite(rmb,0);
  }
  else
  {b=-b;
	digitalWrite(rmf,0);
  digitalWrite(rmb,1);
  }
  analogWrite(lms,a);
  analogWrite(rms,b);
}
void setup() {
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(lmb, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(rmf, OUTPUT);
}

void loop() {
  if(analogRead(ls)<=512 && analogRead(rs)<=512)  
  {
    motor(255,255);
  }
  
  if((analogRead(ls))>=512 && analogRead(rs)<=512)     
  {
    motor(0,155);
  }
  
  if(analogRead(ls)<=512 && (analogRead(rs))>=512)     
  {
    motor(155,0);
  }
  
  if((analogRead(ls))>=512 && (analogRead(rs))>=512)    
  {       
    motor(0,0);
  }
}

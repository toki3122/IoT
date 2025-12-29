#define led 4
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  int a,b,r;
  String op;
  Serial.print("enter input 1: ");
  while(!Serial.available()){}
  a=Serial.parseInt();
  Serial.println(a);
  Serial.print("enter input 2: ");
  while(!Serial.available()){}
  b=Serial.parseInt();
  Serial.println(b);
  Serial.print("enter operation: ");
  while(!Serial.available()){}
  op=Serial.readString();
  Serial.println(op);
  Serial.print("result: ");
  if(op=="Add" || op=="+"){
    r=a+b;
    Serial.println(r);
  }
  else if(op=="Subtract" || op=="-"){
    r=a-b;
    Serial.println(r);
  }
  else if(op=="Multiply" || op=="*"){
    r=a*b;
    Serial.println(r);
  }
  else if(op=="Division" || op=="/"){
    r=a/b;
    Serial.println(r);
  }
  else if(op=="Modulus" || op=="%"){
    r=a%b;
    Serial.println(r);
  }
  else{
    Serial.println("INVALID");
    digitalWrite(led,HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

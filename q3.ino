#define led0 4
#define led1 5
void setup() {
pinMode(led0, OUTPUT);
pinMode(led1, OUTPUT);
Serial.begin(9600);
String s;
delay(100);
Serial.print("enter input: ");
while(!Serial.available()){}
delay(100);
s=Serial.readString();
if(s.length()!=4){
  Serial.println("INVALID");
}
else if(s=="0000"){
  Serial.println("INVALID");
}
else{
  if(s[0]=='1'){
    digitalWrite(led1, HIGH);
    digitalWrite(led0, HIGH);
  }
  else if(s[0]=='0' && s[1]=='1'){
    digitalWrite(led1, HIGH);
    digitalWrite(led0, LOW);
  }
  else if(s[0]=='0' && s[1]=='0' && s[2]=='1'){
    digitalWrite(led1, LOW);
    digitalWrite(led0, HIGH);
  }
  else if(s[0]=='0' && s[1]=='0' && s[2]=='0' && s[3]=='1'){
    digitalWrite(led1, LOW);
    digitalWrite(led0, LOW);
  }
}
}
void loop() {}

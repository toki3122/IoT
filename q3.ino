void setup() {
Serial.begin(9600);
int a;
Serial.print("enter input: ");
while(!Serial.available()){}
a=Serial.parseInt();

}
void loop() {}

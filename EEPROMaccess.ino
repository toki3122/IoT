#include <EEPROM.h>
void setup()
{
  Serial.begin(9600);
  EEPROM.write(0x0010,0x34);
  EEPROM.write(0x0011,0x12);
  byte y1=EEPROM.read(0x0010);
  byte y2=EEPROM.read(0x0011);
  Serial.println(y1,HEX);
  Serial.println(y2,HEX);
  //SINGLE LINE:
  EEPROM.put(0x0010,0x1234);
  unsigned int y3;
  EEPROM.get(0x0010,y3);
  Serial.println(y3,HEX);
}

void loop()
{
  
}

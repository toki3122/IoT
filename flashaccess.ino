const PROGMEM byte y=0x35;//one byte
const PROGMEM unsigned int b=0x1235;//two byte
void setup()
{
  Serial.begin(9600);
  byte z=pgm_read_byte_near(&y);
  unsigned int x=pgm_read_word_near(&b);
  Serial.println(z,HEX);
  Serial.println(b,HEX);
}

void loop()
{
  
}

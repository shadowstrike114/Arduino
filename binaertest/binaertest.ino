
void setup()
{
  DDRB =  0b00100000; //port 5 ausgang
}

void loop()
{
  PORTB |= (1 << 5);
  delay(1000);
  PORTB &= ~(1 << 5);
  delay(1000);
}

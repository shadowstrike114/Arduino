
#define GasIn  3
#define GasOut  10
#define CtrlIn  2

int Gas = 1000; //gas 0%
int Ctrl = 1000; //ctrl 0%


void setup()
{
  Serial.begin(9600);
  attachInterrupt(0,controlIn,CHANGE);
  attachInterrupt(1,gasIn,CHANGE);
  
  TCCR1A = 0b00000000; //alles 0 -> normal operation
  TCCR1B = 0b00000010; //normal operation, letzte 3 clock select:
                       // 010 -> clk/8 -> 0,5us
  TCNT1 = 0; // timer counter auf 0 setzen
  
}

void loop()
{
  Serial.print(Ctrl);
  Serial.print("     ");
  Serial.println(Gas);
}

void controlIn()
{
  static unsigned long zeit;
  
  zeit = TCNT1; 
  TCNT1 = 0; //Timer auf 0, sofort weiterzählen
  
  if (( zeit > 1900 ) && ( zeit < 4000 ))
  {
    Ctrl = zeit / 2;    
  }
  
}

void gasIn()
{
  static unsigned long zeit;
  
  zeit = TCNT1; 
  TCNT1 = 0; //Timer auf 0, sofort weiterzählen
  
  if (( zeit > 1900 ) && ( zeit < 3600 ))
  {
    Gas = zeit / 2;    
  }
  
}

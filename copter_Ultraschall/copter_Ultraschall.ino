#include <LiquidCrystal.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#define TRIGPIN A5
#define ECHOPIN A4

double dist;
double integral = 0;
long anzahl;
boolean vorher;
double differenz;
double abstand;

double kP = 0.2;
double kI = 0.5;
double kD = 0;

double P;
double I;
double D;

long signalzeit = 0;
int sigin; //1000: aus  2000 an
long siginpriv; //1000: aus  2000 an
int sigout;
int sigein;
long sigeinpriv;
int haltehoehe = 0;
boolean ausgeben;

void sendTrigger();
long fetchPulse(int timeout); //entspricht der PulseIn funktion des Arduino
double getDist();
void interrupt();
void gasinterrupt();
void hoehehalten();
void ausgabe();
void uebergeben();

void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  attachInterrupt(0,interrupt,CHANGE);
  attachInterrupt(1,gasinterrupt,CHANGE);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(5,  OUTPUT);
  Serial.begin(9600);
}

void loop() {
  uebergeben();
  hoehehalten();
  ausgabe();
}

void uebergeben()
{
  noInterrupts();
  sigin = siginpriv;
  sigein = sigeinpriv;
  interrupts();
}

void hoehehalten()
{
  if (sigin > 1500)
  {
    interrupts();
    if (!vorher)
    {
      vorher = true;
      haltehoehe = getDist();
    }
    dist = (getDist() + getDist()+getDist()+getDist()+getDist());
    //Serial.println(dist);
    if (dist > 50)
      differenz = haltehoehe - (dist / 5); //nach unten positiv nach oben negativ

    integral += differenz;
    anzahl++;


    //Proportional
    P = map(differenz,-400, 400,-1000,1000);  

    //Integral


    //Anwenden
    sigout = sigein+ kP * P;// + kI * integral;

    if (sigout > 1800)
      sigout = 1800;
    if (sigout < 1000)
      sigout = 1000;
  }
  else{
    sigout = sigein;
    vorher = false;
    integral = 0;
    anzahl = 0;  
  }


}

void sendTrigger()
{
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
}

long fetchPulse()
{
  uint32_t zeit = micros();
  while (!digitalRead(ECHOPIN)) 
  {
    if (micros() - zeit > 23324) //8m (4 hin 4 zurück) /343 m/s = 0.0233236s also ~23324 us
    {
      return -1;
    } 
  }

  zeit = micros();
  while (digitalRead(ECHOPIN))
  {
    if (micros() - zeit > 23324)
    {
      return -1;
    } 
  }

  return micros() - zeit;
}

double getDist()
{
  sendTrigger();
  abstand = (fetchPulse()*343.0)/20000.0; //8m (4 hin 4 zurück) /343 m/s = 0.0233236s also ~23324 us
  //delay(3);
  return abstand;
}

void gasinterrupt()
{
  static boolean lastState;  
  static unsigned long lastTime;
  if (lastState && !digitalRead(3))
  {
    if (1000 < micros() - lastTime && micros()- lastTime < 2000)
    {
      sigeinpriv = micros() - lastTime;
    }
  }
  lastState = digitalRead(3);  
  lastTime = micros();
}

void interrupt()
{
  static boolean lastState;  
  static unsigned long lastTime;
  if (lastState && !digitalRead(2))
  {
    if (1000 < micros() - lastTime && micros()- lastTime < 2000)
    {
      siginpriv = micros() - lastTime;
    }
  }
  lastState = digitalRead(2);  
  lastTime = micros();
}


void ausgabe()
{
  while (!digitalRead(3)){
  }
  //Serial.println(sigout);
  digitalWrite(5, HIGH);
  delayMicroseconds(sigout);
  digitalWrite(5, LOW);
  delay(2);
}









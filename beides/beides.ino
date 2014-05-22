#include <Adafruit_NeoPixel.h>

#define PIN  15
Adafruit_NeoPixel balken = Adafruit_NeoPixel(8,PIN,NEO_KHZ800);

double sinus = 0.0;
double I = 0.0;
int led = 0;
double cosinusR = 0.0;
double cosinusG = 0.0;
double cosinusB = 0.0;
double J = 0.0;
double K = 0.0;
double Y = 0.0;
int R;
int G;
int B;

int zeit =  10;

int RR = 256;
int RG = 256;
int RB = 256;

int nummer = 0;

int schalter;
int reihe;

void setup()
{
  pinMode(PIN, OUTPUT);
  balken.begin();
  balken.show();
  attachInterrupt(0,umschalten,RISING);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(schalter);
  Update();


  if(analogRead(A1) > 512)
  {      
    if((schalter > 340)&&(schalter < 680))
    {
      for (int L = 0; L < 8 ; L++)
      {
        balken.setPixelColor(L,RG,RR,RB);
      }
      delay(10);
      balken.show();
    }
    else if (schalter < 340)
    {
      zeit = map(analogRead(A0),0,340,3,30);
      sinus = (sin(I) + 1)/2.0; //zwischen 0 und 1
      led = round(sinus*7);
      balken.setPixelColor(led,RG,RR,RB);
      balken.show();
      delay(zeit);
      balken.setPixelColor(led,0,0,0);
      balken.show();
      I = I + 0.1;
    }
    else if (schalter > 680)
    {
      cosinusR = (lincos(I)+1)/2;
      cosinusG = (lincos(J)+1)/2;
      cosinusB = (lincos(K)+1)/2;
      R = round(cosinusR * 255);
      G = round(cosinusG * 255);
      B = round(cosinusB * 255);
      for (int i = 0; i < 8;i++)
      {
        balken.setPixelColor(i,G,R,B);
      }
      balken.show();
      delay(5);
      I = I + 0.002;
      J = J + 0.0021;
      K = K + 0.0022;
    }
  }
  else 
  {
    for (int I = 0; I < 8; I++)
    {
      balken.setPixelColor(I,0,0,0);
    }
    balken.show();
  }
}

double lincos(double wert)
{
  if (floor(floor(wert)/2) == floor(wert)/2)
  {
    Y = -1 + 2*(wert - floor(wert));
  }
  if (floor(floor(wert)/2) != floor(wert)/2)
  {
  Y = 1 - 2*(wert-floor(wert));
  }
  return -Y;
}

void umschalten()
{
  if (nummer > 2){ nummer = 0; }
  else{ nummer = nummer + 1; }
  delay(10);
}



void Update()
{
  if (nummer == 0)
  {
    schalter = analogRead(A0);  
  }
  else if (nummer == 1)
  {
    RR = map(analogRead(A0),0,1023,0,255);
  }
  else if ( nummer == 2 )
  {
    RG = map(analogRead(A0),0,1023,0,255);
  }
    else if ( nummer == 3 )
  {
    RB = map(analogRead(A0),0,1023,0,255);
  }
}
/*
  balken.setPixelColor(8,0,0,0);
  for (int i = 0; i < 8; i++)
  {
    balken.setPixelColor(i,255,255,255);
    if(i>0) 
    {
      balken.setPixelColor(i-1,0,0,0);
    }
    balken.show();
    delay(50);
  }
    for (int i = 7; i > -1; i--)
  {
    balken.setPixelColor(i,255,255,255);
    if(i < 7) 
    {
      balken.setPixelColor(i+1,0,0,0);
    }
    balken.show();
    delay(50);
  }
  */

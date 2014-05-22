#include <Adafruit_NeoPixel.h>

#define PIN  6
Adafruit_NeoPixel balken = Adafruit_NeoPixel(8,PIN,NEO_KHZ800);

double sinus = 0.0;
double I = 0.0;
int led = 0;

void setup()
{
  balken.begin();
  balken.show();
  Serial.begin(9600);
}

void loop()
{
  if (analogRead(A0) < 512){
  sinus = (sin(I) + 1)/2.0; //zwischen 0 und 1
  Serial.println(sinus);
  led = round(sinus*7);
  Serial.println(led);
  balken.setPixelColor(led,255,255,255);
  balken.show();
  delay(100);
  balken.setPixelColor(led,0,0,0);
  balken.show();
  I = I + 0.1;
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

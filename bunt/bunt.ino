#include <Adafruit_NeoPixel.h>

#define PIN  6
Adafruit_NeoPixel balken = Adafruit_NeoPixel(8,PIN,NEO_KHZ800);

double cosinusR = 0.0;
double cosinusG = 0.0;
double cosinusB = 0.0;
double I = 0.0;
double J = 0.0;
double K = 0.0;
int R;
int G;
int B;

void setup()
{
  balken.begin();
  balken.show();
}

void loop()
{
  cosinusR = (cos(I) + 1)/2;
  cosinusG = (cos(J + (3.141592654/2))+1)/2;
  cosinusB = (cos(K + (3.141592654))+1)/2;
  R = round(cosinusR * 255);
  G = round(cosinusG * 255);
  B = round(cosinusB * 255);
  
  for (int i = 0; i < 8;i++)
  {
    balken.setPixelColor(i,G,R,B);
  }
  balken.show();
  delay(100);
  I = I + 0.1;
  J = J + 0.2;
  K = K + 0.3;
}

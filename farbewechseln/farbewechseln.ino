#include <Adafruit_NeoPixel.h>

#define PIN  6
Adafruit_NeoPixel balken = Adafruit_NeoPixel(8,PIN,NEO_KHZ800);

double cosinusR = 0.0;
double cosinusG = 0.0;
double cosinusB = 0.0;
double I = 0.0;
double J = 0.0;
double K = 0.0;
double Y;
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

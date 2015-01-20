#include <i2c_t3.h>
#include <LSM303.h>

LSM303 lsm;

void setup(){
  Serial.begin(115200);
  pinMode(12,INPUT_PULLUP);
  lsm.begin();
  //Wire.begin(I2C_MASTER,0,I2C_PINS_18_19,I2C_PULLUP_INT,I2C_RATE_400);
}

void loop(){
  lsm.readMag();
  Serial.print(lsm.magX);
  Serial.print("   ");
  Serial.print(lsm.magY);
  Serial.print("   ");
  Serial.println(lsm.magZ);
  delay(1000);
}

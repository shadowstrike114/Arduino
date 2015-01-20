#include "Arduino.h"
#include "LSM303.h"

LSM303::LSM303(){
	
}

bool LSM303::begin(void){
/*	maximum Rate in the Datasheet:400khz
	Found to operate well up to 2400Khz
	Keeping  at 1200 for safety		*/
	Wire.begin(I2C_MASTER,0,I2C_PINS_18_19,I2C_PULLUP_INT,I2C_RATE_1200);
	
	//ODR 1001 => 1344Hz, LP 0 => off, Z 1 Y 1 X 1 => XYZ on
	write8(LSM303_ACCEL, LSM303_ACCEL_CTRL_REG1_A, 0b10010111);

	write8(LSM303_MAG, LSM303_MAG_CRA_REG_M, 0b10011100); //220Hz update rate
	write8(LSM303_MAG, LSM303_MAG_CRB_REG_M, 0b00100000); //+-1.3 Gauss
	write8(LSM303_MAG, LSM303_MAG_MR_REG_M, 0x00);//activate continuous mode
	
	return true;
}

void LSM303::write8(byte addr, byte reg, byte val){
	Wire.beginTransmission(addr);
	
	Wire.write(reg);
	Wire.write(val);
	
	Wire.endTransmission();
}

byte LSM303::read8(byte addr, byte reg){
	byte val;
  
	Wire.beginTransmission(addr);
	Wire.write(reg);
	Wire.endTransmission();

	Wire.requestFrom((int)addr, 1);
	val = Wire.read();
	Wire.endTransmission(); 
	
	return val;
}

void LSM303::readAcc(){
	Wire.beginTransmission(LSM303_ACCEL);
	//First bit 1 for continuous read. (See datasheet part 5.1.2)
	Wire.write(LSM303_ACCEL_OUT_X_L_A | 0x80);
	Wire.endTransmission();
	
	Wire.requestFrom(LSM303_ACCEL, 6);
	
	uint8_t xlo = Wire.read();
	uint8_t xhi = Wire.read();
	uint8_t ylo = Wire.read();
	uint8_t yhi = Wire.read();
	uint8_t zlo = Wire.read();
	uint8_t zhi = Wire.read();
	
	accX = (int16_t)((xhi << 8)|(xlo)) >> 4;
	accY = (int16_t)((yhi << 8)|(ylo)) >> 4;
	accZ = (int16_t)((zhi << 8)|(zlo)) >> 4;

//-------TODO: MAGNET------
}

void LSM303::readMag(){
	Wire.beginTransmission(LSM303_MAG);
	Wire.write(LSM303_MAG_OUT_X_H_M);
	Wire.endTransmission();
	
	Wire.requestFrom(LSM303_MAG, 6);
	
	uint8_t xhi = Wire.read();
	uint8_t xlo = Wire.read();
	uint8_t yhi = Wire.read();
	uint8_t ylo = Wire.read();
	uint8_t zhi = Wire.read();
	uint8_t zlo = Wire.read();
	
	magX = (int16_t)((xhi << 8)|(xlo));
	magY = (int16_t)((yhi << 8)|(ylo));
	magZ = (int16_t)((zhi << 8)|(zlo));
}

void LSM303::readTemp(){
	Wire.beginTransmission(LSM303_MAG);

	Wire.write(LSM303_TEMP_OUT_H_M);
	Wire.endTransmission();
	
	Wire.requestFrom(LSM303_MAG, 2);
	
	uint8_t thi = Wire.read();
	uint8_t tlo = Wire.read();
	
	temp = (double)((int16_t)(thi << 8)|(tlo)>>4)/8.0 - 40;
}

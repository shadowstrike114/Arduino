#ifndef LSM303_h
#define LSM303_h

#include "Arduino.h"
#include <i2c_t3.h>

#define LSM303_ACCEL 0x19
#define LSM303_ACCEL_OUT_X_L_A 0x28
#define LSM303_ACCEL_STATUS_REG_A 0x27
#define LSM303_ACCEL_CTRL_REG1_A 0x20
#define LSM303_MAG 0x1E
#define LSM303_MAG_CRA_REG_M 0x00
#define LSM303_MAG_CRB_REG_M 0x01
#define LSM303_MAG_MR_REG_M 0x02
#define LSM303_MAG_OUT_X_H_M 0x03
#define LSM303_TEMP_OUT_H_M 0x31


class LSM303
{
	public:
		LSM303();
		
		bool begin();
		void readAcc(); //Max.1344Hz update rate
		void readMag();//Max. 220Hz update rate
		void readTemp();//Max.220Hz update rate
				
		int16_t accX;
		int16_t accY;
		int16_t accZ;
		
		int16_t magX;//TODO: Conversion
		int16_t magY;
		int16_t magZ;
		
		double temp;//Temperature sensor isn't very good
		
		void write8(byte addr, byte reg, byte val);
		byte read8(byte addr, byte reg);
		
		
	private:
		
};

#endif

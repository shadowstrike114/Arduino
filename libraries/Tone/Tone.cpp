/* Tone.cpp
 * Simple implementation of tone() and noTone() functions for Intel Galileo
 * by Janosch Gräf <graef@st.cs.uni-saarland.de>
 * and Florian Gross <fgross@st.cs.uni-saarland.de>
 */

#include <Tone.h>
#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>

extern TwoWire Wire;

/* I2C address of CY8C9540A */
#define CY_I2C_ADDR 0x20

/* set I2C register of CY8C9540A to specified value */
static void _cy_set_register(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(CY_I2C_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

/* Disables tone */
void noTone(int pin) {
  analogWrite(pin, 0);
}

int globalToneSetupDone = 0;
int toneSetupDone[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setupTone(int pin) {
  if (!globalToneSetupDone) {   
    Wire.begin();
    globalToneSetupDone = 1;
  }
  
  if (!toneSetupDone[pin]) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, 1);
    toneSetupDone[pin] = 1;
  }  
}

/* Plays tone in background endlessly. Use noTone() to stop it.
 *  @param pin    The pin to play on. Only pins which support PWM will
 *      work.
 *  @param frequency  The frequency to play in Hz. Use 0 to disable tone.
 *      Should be between 125 Hz and 32 kHz.
 *  @param volume Volume between 0 and 10 (inclusive). Volume of 0 will
 *      disable tone.
 */               
void tone(int pin, int frequency) {
  if (frequency == 0) {
    noTone(pin);
    return;
  }

  // set the top (period)
  unsigned long top = 93750 / frequency;
  top = constrain(top, 0, 255);
  
  if (top == 0) {
    noTone(pin);
    return;
  }

  setupTone(pin);
    
  // Select programmable PWM CLK source to 93 kHz
  _cy_set_register(0x29, 0x03);
  _cy_set_register(0x2A, top);

  // set duty cycle (pulse width)
  unsigned int duty = top / 2; // Calculate the duty cycle (volume).
  _cy_set_register(0x2B, duty);
}

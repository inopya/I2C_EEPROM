/*
 * Version 1.0
 * Admite lectura/escritura de cualquier tipo de datos:
 * byte, int, float... o incluso struct
 */

#include "I2C_EEPROM_inopya.h"
#include <Wire.h>

I2C_EEPROM_inopya::I2C_EEPROM_inopya(uint8_t chipID)
{
  _chipID = chipID;
  Wire.begin();
}

void I2C_EEPROM_inopya::write(unsigned int memory_pos, byte informacion) const
{
  Wire.beginTransmission(_chipID);
  Wire.write((int)(memory_pos >> 8));       	// MSB
  Wire.write((int)(memory_pos & 0xFF));     	// LSB
  Wire.write(informacion);                  	// Write byte
  Wire.endTransmission();

  /* pausa necesaria para que se complete la escritura */
  //delay(5);   // se recomiendan 5 ms, pero en algunos modelos desde 3ms la consolidacion de datos es estable
  delayMicroseconds(3500);   // "jugar" con este valor si se desea acelerar un poco el proceso
}

byte I2C_EEPROM_inopya::read(unsigned int memory_pos) const
{
  byte read_informacion = 0x3A;

  Wire.beginTransmission(_chipID);
  Wire.write((int)(memory_pos >> 8));  			// MSB
  Wire.write((int)(memory_pos & 0xFF));      	// LSB
  Wire.endTransmission();

  Wire.requestFrom(_chipID, 1);

  if (Wire.available()) {
    read_informacion = Wire.read();
  }

  return read_informacion;
}

/*
 * Version 1.0
 * Admite lectura/escritura de cualquier tipo de datos:
 * byte, int, float... o incluso struct
 */
 
#include <Wire.h>

#ifndef I2C_EEPROM_inopya_h
#define I2C_EEPROM_inopya_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class I2C_EEPROM_inopya
{
  public:
     /* parametros: 'Direccion (uint8_t)' I2C de la eeprom externa */
    I2C_EEPROM_inopya(uint8_t chipID);

    /* parametros: 'Direccion de memoria (unsigned int)' en la que deseamos escribir, 'valor (byte)' que deseamos escribir */
    void write(unsigned int memory_pos, byte dato) const;

    /* parametros: 'Direccion de memoria (unsigned int)' de la que deseamos leer un byte */
    byte read(unsigned int memory_pos) const;


	/* parametros: 'Direccion de memoria (unsigned int)' en la que deseamos escribir, valor (de cualquier tipo) que deseamos escribir */
	template< typename T > T &save(unsigned int memory_pos, T informacion )
	{
	  uint8_t *ptr = (uint8_t*) &informacion;
	  //Serial.print(F("save, grabando en EEPROM ")); Serial.println(informacion);
	  for(int count=0; count<sizeof(T); count++){
		Wire.beginTransmission(_chipID); 
		Wire.write((int)(memory_pos >> 8));   // MSB
		Wire.write((int)(memory_pos & 0xFF)); // LSB 
		Wire.write(*ptr);
		Wire.endTransmission();
		//Serial.print(memory_pos); Serial.print(F(" --> "));Serial.println(dato);
		//delay(5);   // se recomiendan 5 ms, pero en algunos modelos desde 3ms la consolidacion de datos es estable
		delayMicroseconds(3500);   // "jugar" con este valor si se desea acelerar un poco el proceso
		ptr++;
		memory_pos++;
	  }
	  //Serial.println(F("Fin de save en EEPROM"));
	}


	/* parametros: 'Direccion de memoria (unsigned int)' de la que deseamos leer, variable (de cualquier tipo) para cargar el valor leido */
	template< typename T > T &load(unsigned int memory_pos, T &informacion )
	{
	  //Serial.print(F("load, cargando de EEPROM "));Serial.print(sizeof(T));Serial.println(F(" bytes"));
	  uint8_t *ptr = (uint8_t*) &informacion;

	  for(int count=0; count<sizeof(T); count++){
		Wire.beginTransmission(_chipID);
		Wire.write((int)(memory_pos >> 8));   // MSB
		Wire.write((int)(memory_pos & 0xFF)); // LSB 
		Wire.endTransmission();
		Wire.requestFrom(_chipID, 1);
		*ptr = Wire.read(); 
		//Serial.print(memory_pos); Serial.print(F(" --> "));Serial.println(*ptr);
		ptr++;
		memory_pos++;
	  }
	 
	  //Serial.print(F("load, saliendo de EEPROM con el valor ")); Serial.println(informacion);
	  return informacion;  //es redundante porque lo carga en la variable original cuya direccion recibe
	}



  private:
    uint8_t _chipID;
	
};

#endif 


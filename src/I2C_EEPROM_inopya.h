/*
 * Version 1.1
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
     /* parametro: 'Direccion (uint8_t)' I2C de la eeprom externa */
    I2C_EEPROM_inopya(uint8_t chipID);

	/* configurar pausa entre grabacion de datos consecutivos */
	void recPause(uint16_t pause);
	
    /* parametros: 
		-'Direccion de memoria (unsigned int)' en la que deseamos escribir, 
		-'valor (byte)' que deseamos escribir 
	*/
    void write(unsigned int memory_pos, byte dato) const;

    /* parametro: 'Direccion de memoria (unsigned int)' de la que deseamos leer un byte */
    byte read(unsigned int memory_pos) const;


	/* parametros: 
		-'Direccion de memoria (unsigned int)' en la que deseamos escribir, 
		-'valor (de cualquier tipo)' que deseamos escribir 
	*/
	template< typename T > T &save(unsigned int memory_pos, T informacion )
	{
	  //Serial.print(F("save, grabando en EEPROM "));Serial.print(sizeof(T));Serial.println(F(" bytes"));
	  uint8_t *ptrDato = (uint8_t*) &informacion;
	  Wire.beginTransmission(_chipID); 
	  Wire.write((int)(memory_pos >> 8));   // MSB
	  Wire.write((int)(memory_pos & 0xFF)); // LSB 
	  for(int count=0; count<sizeof(T); count++){
		Wire.write(*ptrDato);
		/* pausa necesaria para que se complete la escritura */
		if(_rec_pause>1000){ delayMicroseconds(_rec_pause); }
		else if(_rec_pause>0){ delay(_rec_pause); }
		else{ delay(5); }   // Se recomiendan 5 ms, 
							// pero en algunos modelos desde 3ms la consolidacion de datos es estable
					        // Algunos 'clones' chinos necesitan 6 o mas :(
		ptrDato++;
	  }
	  Wire.endTransmission();
	}



	/* parametros:
		-'Direccion de memoria (unsigned int)' de la que deseamos leer, 
		- variable (de cualquier tipo) para cargar el valor leido 
	*/
	template< typename T > T &load(unsigned int memory_pos, T &informacion )
	{
	  //Serial.print(F("load, cargando de EEPROM "));Serial.print(sizeof(T));Serial.println(F(" bytes"));
	  uint8_t *ptrDato = (uint8_t*) &informacion;
	  
	  Wire.beginTransmission(_chipID);
      Wire.write((int)(memory_pos >> 8));   // MSB
	  Wire.write((int)(memory_pos & 0xFF)); // LSB 
      Wire.endTransmission();
	  Wire.requestFrom(_chipID, sizeof(T));
	  for(int count=0; count<sizeof(T); count++){
		*ptrDato = Wire.read(); 
		ptrDato++;
	  }
	  return informacion;  //es redundante porque lo carga en la variable original cuya direccion recibe
	}


  private:
    uint8_t _chipID;
	uint16_t _rec_pause = 6;  // "jugar" con este valor si se desea acelerar un poco el proceso.
							  // Se recomiendan 5 ms, pero en algunos modelos desde 3ms la consolidacion de datos es estable
				              // Algunos 'clones' chinos necesitan 6 o más :(
	
};

#endif 


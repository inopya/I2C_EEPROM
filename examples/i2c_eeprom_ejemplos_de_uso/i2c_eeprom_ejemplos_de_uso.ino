
/*
  #       _\|/_   A ver..., ¿que tenemos por aqui?
  #       (O-O)        
  # ---oOO-(_)-OOo---------------------------------
   
   
  ##########################################################
  # ****************************************************** #
  # *            DOMOTICA PARA AFICIONADOS               * #
  # *        USO DE EEPROM EXTERNA HASTA  64kb           * #
  # *          Autor:  Eulogio López Cayuela             * #
  # *                                                    * #
  # *       Versión v1.0      Fecha: 04/02/2020          * #
  # ****************************************************** #
  ##########################################################
*/

#define __VERSION__ "Ejemplos de uso eeprom externa\n"

/*
  
 ===== NOTAS DE LA VERSION =====
 Test de eeprom externa
 Ejemplo de uso de la libreria I2C_EEPROM_inopya
*/


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        IMPORTACION DE LIBRERIAS
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#include <I2C_EEPROM_inopya.h>



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DECLARACION DE CONSTANTES  Y  VARIABLES GLOBALES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#define CHIP_ID           0x50      // la direccion de memoria del chip (24LC256) si A0, A1 y A2 estan a GND es 0x50
#define POS_MEMO             0      // posicion memoriade usada apra las pruebas de eeprom
                                    // recordar que el chip (24LC256) dispone de 32768 posiciones de memoria
byte patron_byte = 23;              // valor 'byte' que usaremos en el test de escritura y lectura de bytes 
float patron_float = 1501.13;       // valor 'float' que usaremos en el test de escritura y lectura de floats 



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION PARA DECLARACION DE OBJETOS
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

I2C_EEPROM_inopya eeprom(CHIP_ID);  // Creamos un objeto del tipo i2c_eeprom (eeprom externa)



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 
//***************************************************************************************************
//         FUNCION DE CONFIGURACION
//***************************************************************************************************
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 

void setup() 
{
  Serial.begin(9600);
  Serial.println(F(__VERSION__));
  Serial.print(F("CHIP ID = 0x"));
  Serial.println(CHIP_ID, HEX);

  /* Escritura de un byte */
  eeprom.write(POS_MEMO, patron_byte);

  /* Lectura de un byte */
  byte dato_byte = 0;
  dato_byte = eeprom.read(POS_MEMO);

  /* Escritura de un float */
  eeprom.save(POS_MEMO, patron_float);

  /* Lectura de un float */
  float dato_float = 0;
  eeprom.load(POS_MEMO, dato_float);
  
  Serial.print(F("\n\nPruebas realizadas\n"));
}



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 
//***************************************************************************************************
//  BUCLE PRINCIPAL DEL PROGRAMA   (SISTEMA VEGETATIVO)
//***************************************************************************************************
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 

void loop() 
{
  //nada en el loop, para evitar escrituras excesivas de la eeprom
}




//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************

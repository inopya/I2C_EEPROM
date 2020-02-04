
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

#define __VERSION__ "Test de uso de eeprom externa\n"

/*
  
 ===== NOTAS DE LA VERSION =====
 Test de eeprom externa
  
 
*/


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        IMPORTACION DE LIBRERIAS
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#include <I2C_EEPROM_inopya.h>



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DECLARACION DE CONSTANTES  Y  VARIABLES GLOBALES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#define CHIP_ID           0x50      // la direccion de memoria del chip (24LC256) si A0, A1 y A2 estan a GND es 0x50
#define POS_MEM_INICIAL      0      // primera posicion usada apra el test de lectura y escritura de bytes
#define EEPROM_BYTES        45      // numero de bytes que se usaran para el test de escritura de bytes
                                    // recordar que el chip (24LC256) dispone de 32768 posiciones de memoria
#define POS_MEM_FLOAT       20      // posicion de memoria para usar en el test de lectura escritura de un float

byte patron_byte = 23;              // valor 'byte' que usaremos en el test de escritura y lectura de bytes 
float patron_float = 1501.13;       // valor 'float' que usaremos en el test de escritura y lectura de float 



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
  Serial.print(F("CHIP ID = 0x"));
  Serial.println(CHIP_ID, HEX);

  test_write_read();
  test_save_load();

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



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   ###################################################################################################### 
                                         BLOQUE DE FUNCIONES
   ###################################################################################################### 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//  TEST DE ESCRITURA Y LECTURA DE DATOS byte
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void test_write_read()
{
  Serial.print(F("\nProbaremos las funciones 'read', 'write' ")); 
  Serial.print(F("entre las posiciones ")); Serial.print(POS_MEM_INICIAL);
  Serial.print(F(" y ")); Serial.println(POS_MEM_INICIAL+EEPROM_BYTES, DEC);
  
  Serial.print(F("Escribiendo bytes con 'write'...\n"));
  for (unsigned int direccion_memoria = POS_MEM_INICIAL; direccion_memoria < POS_MEM_INICIAL+EEPROM_BYTES; direccion_memoria++) {
    eeprom.write(direccion_memoria, patron_byte);
  }

  Serial.println(F("\nLeyendo bytes con 'read' desde la EEPROM..."));
  unsigned int errores = 0;
  for (unsigned int direccion_memoria = POS_MEM_INICIAL; direccion_memoria < POS_MEM_INICIAL+EEPROM_BYTES; direccion_memoria++) {
    byte dato = 0;
    dato = eeprom.read(direccion_memoria);
    //Serial.print(dato, DEC);
    if (dato != patron_byte) {
      errores++;
      Serial.print(F(" - Error en la direccion de memoria "));
      Serial.println(direccion_memoria, HEX);
    }
    else{
      //Serial.print(F("\n"));
    }
  }
  if (errores==0){
    Serial.println(F("TEST 'write-read' OK\n")); 
  }
  else{
    Serial.println(F("La EEPROM presenta errores\n"));
  }
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//  TEST DE ESCRITURA Y LECTURA DE DATOS float
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void test_save_load()
{
  Serial.print(F("\nAhora probaremos las funciones 'save' y 'load' ")); 
  Serial.print(F("En la posicion ")); Serial.println(POS_MEM_FLOAT);
  
  Serial.println(F("Escribiendo con 'save' en la EEPROM..."));
  eeprom.save(POS_MEM_FLOAT, patron_float);

  Serial.println(F("Leyendo con 'load' de la EEPROM..."));
  float dato = 0;
  eeprom.load(POS_MEM_FLOAT, dato);
  Serial.print(F("El dato leido por 'load' es: "));Serial.println(dato);
  
  if (dato==patron_float){
    Serial.print(F("\nTEST 'save-load' OK\n")); 
  }
  else{
    Serial.print(F("\nLa EEPROM presenta errores\n"));
  }
}


//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************

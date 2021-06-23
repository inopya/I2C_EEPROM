## **I2C_EEPROM_inopya V1.1** para Arduino

**Autor:** _Eulogio López_  

Libreria para acceso mediannte I2C a memorias EEPROM externas de hasta 64kb. 

v1.1. >> Cambios realizados en las funciones de lectura y escritura de _I2C_EEPROM_inopya.h_ para datos mayores a un byte, es decir float, int, car[], struct... 
Se consigue acelerar un poco el proceso de escritura, pero sobre todo corrigen fallos de escritura (la lectura era correcta) debidos a problemas con la libreria wire.h sobre clones tipo WavGat basado en el chip LogicGreen LGT8F328.

### **Funciones**

#### **`I2C_EEPROM_inopya.write( posicion, byte )`** 

Este metodo permite leer de la eeprom un byte

#### **`I2C_EEPROM_inopya.read( posicion )`**

Este metodo permite guardar en la eeprom un byte.

#### **`I2C_EEPROM_inopya.save( posicion, dato )`**

Este metodo permite guardar en eeprom datos de cualquier tipo: byte, int, float, struct...

#### **`I2C_EEPROM_inopya.load( posicion, dato )`**

Este metodo permite leer de la eeprom datos de cualquier tipo: byte, int, float, struct...






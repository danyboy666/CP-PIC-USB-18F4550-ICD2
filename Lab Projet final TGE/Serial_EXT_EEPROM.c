///////////////////////////////////////////////////////////////////////////
////   Library for a MicroChip 24C32                                   ////
////                                                                   ////
////   init_ext_eeprom();    Call before the other functions are used  ////
////                                                                   ////
////   write_ext_eeprom(a,d);  Write the byte d to the address a       ////
////                                                                   ////
////   d = read_ext_eeprom(a);  Read the byte d from the address a     ////
////                                                                   ////
////   b = ext_eeprom_ready();  Returns TRUE if the eeprom is ready    ////
////                            to receive opcodes                     ////
////                                                                   ////
////   The main program may define EEPROM_SDA                          ////
////   and EEPROM_SCL to override the defaults below.                  ////
////                                                                   ////
////                            Pin Layout                             ////
////   -----------------------------------------------------------     ////
////   |                                                         |     ////
////   | 1: NC   Not Connected | 8: VCC   +5V                    |     ////
////   |                       |                                 |     ////
////   | 2: NC   Not Connected | 7: WP    GND                    |     ////
////   |                       |                                 |     ////
////   | 3: NC   Not Connected | 6: SCL   EEPROM_SCL and Pull-Up |     ////
////   |                       |                                 |     ////
////   | 4: VSS  GND           | 5: SDA   EEPROM_SDA and Pull-Up |     ////
////   -----------------------------------------------------------     ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996, 2003 Custom Computer Services          ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////     Modification pour le module ET-MINI 24XX de EEPROM série      ////
////        par Dany Ferron 2012                                       ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
// Byte de controle
//
//  1 -| Ces quatre bit ont toujours cette valeur 
//     | pour les opérations d'écritures et de
//  0 -| lectures. 1010xxxx
//     |
//  1 -|
//     |
//  0 -|
//
//  A2 <-- Un niveau haut sur ce bit spécicifie l'address sur le bus I2C.
//
//  A1 <-- Un niveau haut sur ce bit spécicifie l'address sur le bus I2C.
//
//  A0 <-- Un niveau haut sur ce bit spécicifie l'address sur le bus I2C.
//
//  0 - 1 <-- 1 en lecture, 0 en écriture

#ifndef EEPROM_SDA
   #define EEPROM_SDA  PIN_B0
   #define EEPROM_SCL  PIN_B1
#endif

//#use i2c(master, sda=EEPROM_SDA, scl=EEPROM_SCL)

#define hi(x) (*((int8 *) &x + 1)) // Macro servant à garder HAUT octet du mot.

#define WRITE_BIT 1
// Addresse sur le Bus.
#define I2C_ADDRESS_EEPROM_1 0xA8 // ByteID = 1010 1000
#define I2C_ADDRESS_EEPROM_2 0xAA // ByteID = 1010 1010
#define I2C_ADDRESS_EEPROM_3 0xAC // ByteID = 1010 1100
#define I2C_ADDRESS_EEPROM_4 0xAE // ByteID = 1010 1110
//#define EEPROM_ADDRESS long int
//#define EEPROM_SIZE    4096

// Génère un état d'haute impédance sur les lignes I2C.
void init_ext_eeprom() 
{
   output_float(EEPROM_SCL);
   output_float(EEPROM_SDA);
}
// Fonction servant à générer le Bit ACK requis à la fin de chaque opération 
// d'écriture/lecture dans la EEPROM externe. Ce Bit est fournis avec un coup
// d'horloge suplémentaire générer par le Master(le microprocesseur) après la 
// réception de chaque Byte.
BOOLEAN ext_eeprom_ready() 
{  
   int1 ack;
   
   i2c_start();            // If the write command is acknowledged,
   ack = i2c_write(I2C_ADDRESS_EEPROM_1);  // then the device is ready.
   i2c_stop();
   
   return !ack;
}

void write_ext_eeprom(long int address, BYTE data) 
{
   while(!ext_eeprom_ready()); // S'assure que le bit ACK à été généré avant l'opération.
      
   i2c_start();
   i2c_write(I2C_ADDRESS_EEPROM_1); // Byte de controle incluant l'addresse sur le Bus.
   i2c_write(hi(address)); // Écriture du HAUT octet du mot de l'addresse mémoire. 
   i2c_write(address); // Écriture du BAS octet du mot de l'addresse mémoire.
   i2c_write(data); // Écriture de la donnée recue du programme principal.
   i2c_stop();


}


BYTE read_ext_eeprom(long int address) 
{
   BYTE data;

   while(!ext_eeprom_ready()); // S'assure que le bit ACK à été généré avant l'opération.
   
   i2c_start();
   i2c_write(I2C_ADDRESS_EEPROM_1); // Byte de controle incluant l'addresse sur le Bus.
   i2c_write(hi(address)); // Écriture du HAUT octet du mot de l'addresse mémoire.
   i2c_write(address); // Écriture du BAS octet du mot de l'addresse mémoire.
   i2c_start();
   i2c_write(I2C_ADDRESS_EEPROM_1 + WRITE_BIT); // Byte de controle signalant la lecture.
   data=i2c_read(0); // Lecture de l'octet en mémoire.
   i2c_stop();
   
   return(data); // Retour de l'octet vers le programme l'appelant.
}


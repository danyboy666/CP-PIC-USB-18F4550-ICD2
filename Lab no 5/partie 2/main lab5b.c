/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 5 (partie 2)                        //
//         Programme no 1: Expérimentation avec le protocole I²C               //
//                                                                             //
//                                                                             //
// Le module DS1307 RTC (pour Real Time Clock) est une horloge en mesure de    //
// fournir secondes, minutes, heures, jour, mois & année avec prise en compte  //
// des années bisextiles  jusqu'en 2100. Une pile de sauvegarde peut être mise //
// en place pour conserver les données en cas de coupure de l'alim extérieure. //
//                                                                             //
// Le DS1307 s'interface sur le bus I²C.                                       //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// (c)Copyright 2012 : Dany Ferron 2012                                        //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                                                                             //
//              _________________                                              //
//            -|1              40|-RB7                                         //
//            -|                 |-RB6                                         //
//            -|    PIC18F4550   |-RB5                                         //
//            -|      @20MHz     |-RB4                                         //
//            -|                 |-RB3                                         //
//            -|                 |-RB2                                         //
//            -|                 |-RB1 <-> SLC (serial clock)                  //
//            -|                 |-RB0 <-> SDA (serial data)                   //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-RC7/RX <- This is the connection to the     //
//            -|                 |-RC6/TX -> MELabs serial LCD controller      //
//            -|                 |-                                            //
//            -|                 |-                                            //
//         RD0-|                 |-                                            //
//         RD1-|20             21|-RD2                                         //
//              -----------------                                              //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
#include "main lab5b.h"
#include "DS1307_db666.c"
#include "SLCD.c"

#define BIT_VAL(x) (1 << x) // Bit test
#define HR12 0x40 // Sert de masque pour isoler le Bit6 représentant le mode 12hr.

#define AM 0x00 
#define PM 0x20 // Sert de masque pour Bit5 du registre des heures.
#define ENABLED 1
#define DISABLED 0

 //////////////////////////Programme principal//////////////////////////////////
 void main()
 {
    // Variables de temps.
    BYTE sec;
    BYTE min;
    BYTE hour;
    BYTE day;
    BYTE date;
    BYTE month;
    BYTE year;
    
    BYTE ampm_test;
    BOOLEAN ampm;
    BOOLEAN mode_12hr;
    
    ds1307_init();
    // Mode 12 heures -> mode_12hr = ENABLED 
    // Mode 24 heures -> mode_12hr = DISABLED
    mode_12hr = DISABLED; 
    // Bloc d'ajustement de temps.
    // Set date for -> Lundi 19 mars 2012   
    // Set time for -> 11:59:50 PM ou 23:59:50 
    write_ds1307(0,0x50); //Set second to 00 and enable clock(bit7=0):0-59
    write_ds1307(1,0x59); //Set minute :0-59
    switch(mode_12hr)
    {  
       case 1:write_ds1307(2,0x11 | PM | HR12); // Set hour :01-12,AM-PM
       break;
       default:write_ds1307(2,0x23); //Set hour :00-23
    }
    write_ds1307(3,0x02); // Set day : 1-07
    write_ds1307(4,0x19); // Set date : 1-31
    write_ds1307(5,0x03); // Set month : 1-12
    write_ds1307(6,0x12); // Year : 00-99
    
    while(TRUE)
    {
       // Bloc de lecture des données provenant du module DS1307.
       // Pointe vers l'adresse I2C: 0xD0 + le bit d'adresse correspondant.
       sec=read_ds1307(0); 
       min=read_ds1307(1);
       hour=read_ds1307(2);
       day=read_ds1307(3);
       date=read_ds1307(4);
       month=read_ds1307(5);
       year=read_ds1307(6);
       
       printf("\f");
       // En fesant un Bit test sur la variable des heures, le résultat de l'équation 
       // ET logique est transferer dans variable et ainsi avec une condition IF THEN
       // identifie et affecte le reste du programme.
       if(mode_12hr == ENABLED)
       {
          ampm_test = (hour & BIT_VAL(5)); 
          
          if(ampm_test == 0x20)ampm = 1;
          
          else ampm = 0;
          
       hour = (hour & 0x1f); // ET logique pour définir heures.
       LCD_Position(1,16);

          switch(ampm)
          {
             case 0:printf(":AM");
             break;
             case 1:printf(":PM");
             break;
          }  
       }       
       LCD_Position(1,1);
       printf("Heure :%2x:%2x:%2x\r\n",hour,min,sec);
       switch(day) // Identification de la journée.
       {
          case 1:printf("Date :DIM-");
          break;
          case 2:printf("Date :LUN-");
          break;
          case 3:printf("Date :MAR-");
          break;
          case 4:printf("Date :MER-");
          break;
          case 5:printf("Date :JEU-");
          break;
          case 6:printf("Date :VEN-");
          break;
          case 7:printf("Date :SAM-");
          break;
       }
       printf("%2x/%2x/%2x",date,month,year);
       delay_ms(1000);
    }
 }


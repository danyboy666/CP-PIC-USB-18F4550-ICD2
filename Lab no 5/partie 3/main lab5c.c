/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 5 (partie 3)                        //
//         Programme no 1: Expérimentation avec le protocole I²C               //
//      Modules utilisé:  ET-MINI DS1307                                       //
//                        ET-MINI PCF8583                                      //
// Utilisation: Définir quel module est utilisé en modifiant                   //
// #define I2C_Clock_Chip 1 du programme principal et du driver                //
//               1 pour PCF8583, 2 pour DS1307                                 //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// (c) Copyright 2012 Dany Ferron                                              //
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
#include "main lab5c.h"
#include "RTC_Clock.c"
#include "SLCD.c"

#define I2C_Clock_Chip 2 // 1 for PCF8583, 2 for DS1307

#zero_ram // S'assure que le registre interne servant à tenir les variables est à zero

void main() 
{
   
   init_I2C_Clock();// initialise RTC
                 // Set time and date:
                 // hh,mm,ss,DD,MM,YY,WD
   set_I2C_Clock(0x11,0x59,0x50,0x20,0x03,0x12,0x03);

   while(TRUE)
   {
      printf("\f");
      get_I2C_Clock();// Reads date and time
      #if(I2C_Clock_Chip  == 1)
         rtc_value.year += 0x10; 

      #endif
      LCD_Position(1,1);

      #if(I2C_Clock_Chip  == 1)
         printf("  -- PCF8583 --\n\r");

      #else
         printf("  -- DS1307 --\n\r");

      #endif
      
      printf(" Time: %X:%X:%X\n\r",rtc_value.hour,rtc_value.minute,rtc_value.second);// Display time on second line
      LCD_Position(3,1);// goto on 1st column third row(3th line)
      switch(rtc_value.weekday)
      {
         // process weekday and display it
         case 1:
         printf("Date: Dim-");
         break;

         case 2:
         printf("Date: Lun-");
         break;

         case 3:
         printf("Date: Mar-");
         break;

         case 4:
         printf("Date: Mer-");
         break;

         case 5:
         printf("Date: Jeu-");
         break;

         case 6:
         printf("Date: Ven-");
         break;

         case 7:
         printf("Date: Sam-");
         break;
      }

      printf("%X/%X/%X\n\r",rtc_value.day,rtc_value.month,rtc_value.year);
      delay_ms(1000);
   }
}


/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 5 (partie 3)                        //
//         Programme no 1: Expérimentation avec le protocole I²C               //
//                 Modules utilisé:  ET-MINI PCF8583                           // 
//  Ce Programme Peut lire le module et obtenir la date et l'heure dans le     //
//  format 12 heures ou 24 heures en speciant dans le programme principale     //
//                    // Mode 12 heures -> mode_12hr = ENABLED                 //
//                    // Mode 24 heures -> mode_12hr = DISABLED                //
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

#include "RTC_DB666.h"
#include "PCF8583_DB666.c"
#include "SLCD.c"

#define BIT_VAL(x) (1 << x) // Identify selected Bit for operation
#define HR12 0x80 // Sert de masque pour isoler le Bit 7 représentant le mode 12hr
                  // du registre des heures.

#define AM 0x00 
#define PM 0x40 // Sert de masque pour Bit 6 du Bit AM/PM du registre des heures.
#define ENABLED 1
#define DISABLED 0

BYTE set_hrs;
BYTE ampm_test;
BOOLEAN ampm;    
BOOLEAN mode_12hr;

void main()
{   
    init_PCF8583();// initialise RTC   
    // Mode 12 heures -> mode_12hr = ENABLED 
    // Mode 24 heures -> mode_12hr = DISABLED
    mode_12hr = ENABLED; 
    
    switch(mode_12hr)
    {  
       case 0:set_hrs=(0x23); //Set hour :00-23
       break;
       case 1:set_hrs=(0x11 | PM | HR12); // Set hour :01-12,AM-PM
       break;       
    }
                  // Set time and date:
                  // hh,mm,ss,DD,MM,YY,WD
   set_PCF8583(set_hrs,0x59,0x50,0x20,0x03,0x12,0x03);
   
   while(TRUE)
   {
      get_PCF8583();// Reads date and time      
      rtc_value.yrs += PCF8583_YEAR_REG; 
      
      printf("\f");// Clear LCD display
      
      if(mode_12hr == ENABLED)
       {
          ampm_test = (rtc_value.hrs & BIT_VAL(6)); 
          
          if(ampm_test == PM)ampm = 1;
          
          else ampm = 0;
          
       rtc_value.hrs = (rtc_value.hrs & 0x1f); // ET logique pour définir heures.
       
       LCD_Position(2,15);// goto on 15th column third row(1st line) 

          switch(ampm)
          {
             case 0:printf(" AM");break;             
             case 1:printf(" PM");break;             
          }       
       }    
            
      LCD_Position(1,1);// goto on 1st column third row(1st line)      
      printf("  -- PCF8583 --\n\r");      
      LCD_Position(2,1);// goto on 1st column third row(2th line)
      printf("Time: %X:%X:%X\n\r",rtc_value.hrs,rtc_value.mins,rtc_value.secs);// Display time on second line
      LCD_Position(3,1);// goto on 1st column third row(3th line)
      
      switch(rtc_value.dows)
      {
         // process weekday and display it
         case 1:printf("Date: Dim-");break;
         case 2:printf("Date: Lun-");break;
         case 3:printf("Date: Mar-");break;
         case 4:printf("Date: Mer-");break;
         case 5:printf("Date: Jeu-");break;
         case 6:printf("Date: Ven-");break;
         case 7:printf("Date: Sam-");break;
      }

      printf("%X/%X/%X\n\r",rtc_value.days,rtc_value.mths,rtc_value.yrs);
            
      delay_ms(1000); // Taux de rafraichissement du l'affichage.
   }
}



/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 5 (partie 1)                        //
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

#include "main lab5a.h"
#include "ds1307paul.c "

void main()
{
  BYTE sec; 
  BYTE min; 
  BYTE hrs; 
  BYTE day; 
  BYTE month; 
  BYTE yr; 
  BYTE dow;

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   printf("%c%c",0xfe,0x01);
   printf("%s","Quelle heure il est?");
   delay_ms(3000);

   ds1307_init(); 
  
  // Set date for -> 1 avril 2012 Lundi
  // Set time for -> 15:20:55 
  ds1307_set_date_time(1,4,12,2,15,20,55); 
  
  while(TRUE) 
  { 
    delay_ms(1000); 
    
    ds1307_get_date(day,month,yr,dow); 
    ds1307_get_time(hrs,min,sec); 
    printf("%c%c",0xfe,0x01);  
    printf("Heure : %02d:%02d:%02d\r\n", hrs,min,sec);
    printf("jour  : %02d\r\n", dow);
    printf("Date  : %02d/%02d/20%02d\r\n",day,month,yr); 
  } 
}

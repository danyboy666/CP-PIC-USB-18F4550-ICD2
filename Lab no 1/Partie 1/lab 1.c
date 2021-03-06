///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 1                              //
// Programme no 1: Faire clignoter 2 LED en alternance.                      //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "lab 1.h"

#define LED1 pin_B0 //Active sur niveau bas.
#define LED2 pin_B1 //Active sur niveau haut.

void blinky(); //D�claration du sous-programme de clignotement.

void main() //Programme principal.
{
   setup_adc_ports (NO_ANALOGS|VSS_VDD);
   setup_adc (ADC_OFF);
   setup_psp (PSP_DISABLED);
   setup_spi (SPI_SS_DISABLED);
   setup_wdt (WDT_OFF);
   setup_timer_0 (RTCC_INTERNAL);
   setup_timer_1 (T1_DISABLED);
   setup_timer_2 (T2_DISABLED, 0, 1);
   setup_comparator (NC_NC_NC_NC);
   setup_vref (FALSE);

   //�teindre les deux LEDs.
   output_high (LED1);
   output_low (LED2);
   
   WHILE (TRUE) //Boucle infinie.
   {
      blinky ();
} //Fin de la boucle infinie.
} //Fin du programme principal.

void blinky() //Programme de clignotement de LEDs.
{
   output_low (LED1); //Allum� la LED 1.
   delay_ms (2000); //Pendant 2 secondes.
   output_high (LED2); //Alumer la LED 1 et 2.
   delay_ms (3000); //Pendant 3 secondes.
   output_high (LED1); //�teindre la LED 1.  
   output_low (LED2); //�teindre la LED 2.
   delay_ms (2000); //Pendant 2 secondes.
   
}


///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 1                              //
// Programme no 2: 2 LEDs contr�l�es par un boutton poussoir.                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "lab 1_Partie2.h"

//Constantes utilis�es.
#define     LED1         PIN_B0 //Active sur niveau bas.
#define     LED2         PIN_B1 //Active sur niveau haut.
#define     BUTTON       PIN_B2 //Active sur niveau haut.

   void program_button();
   void blinky();
   
void main()
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
   
   while (TRUE) //Boucle infinie.
   {
         delay_ms (200); //Pause de v�rification.
      if (input(BUTTON) == 0)program_button(); //V�rification si le bouton est appuyer.
      
         blinky (); //Appel de la boucle de clignotement.
   } //Fin de la boucle infinie.
} //Fin du programme principal.

void blinky() //Programme de lignotement des LEDs.
{
   output_low (LED1); //Allum� la LED 1.
   delay_ms (2000); //Pendant 2 secondes.
   output_high (LED1); //�teindre LED 1.
   delay_ms (1000); //Pendant 1 secondes.
}

void program_button() //Programme boutton poussoire.
{
   output_high (LED1); //�teindre LED 1.
   output_high (LED2); //Allum� la LED 1.
   delay_ms (1000); //Pendant 1 secondes.
   output_low (LED2); //�teindre LED 1.
   delay_ms (2000); //Pendant 2 secondes.
}




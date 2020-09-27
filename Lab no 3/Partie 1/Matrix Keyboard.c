///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 3                              //
// Programme no 1: Exp�rimentation d'un clavier matriciel                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "Matrix Keyboard.h"
#include "CLAVIER16T.c"

void main()
{
   char k; //Variable locale k.
   
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   printf("%c%c",0xfe,0x1); //Positionne le curseur � la position 0x1 et �fface l'�cran.
   printf("%c%c",0xfe,0x85); //Positionne le curseur � la position 0x85 et �fface l'�cran.
   printf("%s","appuyer"); //Affiche le message.
   
   do //Faire la boucle tant que...
   {
      k=kbd_getc();
      if(k!=0)
      {
         printf("%c%c",0xfe,0x84); //Positionne le curseur � la position 0x84 et �fface l'�cran.
         printf("touche pesee");  //Affiche le message.
         printf("%c%c",0xfe,0xca); //Positionne le curseur � la position 0xca et �fface l'�cran.
         printf("%c",k); //Affiche la touche appuy�e.
         delay_ms(3000); // Delai de 3 secondes.
         printf("%c%c",0xfe,0x1); //Positionne le curseur � la position 0x1 et �fface l'�cran.
         printf("%c%c",0xfe,0x85); //Positionne le curseur � la position 0x85 et �fface l'�cran.
         printf("%s","appuyer"); //Affiche le message.
      }
   }
   while(true);
}

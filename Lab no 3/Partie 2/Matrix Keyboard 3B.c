///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 3                              //
// Programme no 2: Exp�rimentation avec clavier matriciel ger� par           //
//                  interruptions.                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "Matrix Keyboard 3B.h"
#include "CLAVIER16T c-a interruption.c"
CHAR K ;

#int_EXT2    // utilisation de l'interruption EXT2 cabl� sur le portB bit 2
void  EXT2_isr(void) {   // Si une interruption se produit les instructions seront ex�cut�es   
   k=kbd_getc( );
}

void main()
{

   
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_EXT2);
   enable_interrupts(GLOBAL);
   ext_int_edge(2,H_TO_L);   //front descendant sur RB2 Interrupt ext 2

   printf("%c%c",0xfe,0x1);
   printf("%c%c",0xfe,0x85);
   printf("%s","appuyer");
   DO
   {
      set_tris_d(0xf0);   //Bit0 � bit3 en entr�e et bit 4 � bit7 en sortie
      output_low(pin_D4);   // mettre la sortie � 0
      output_low(pin_D5);
      output_low(pin_D6);
      output_low(pin_D7);
      if(k!='\0') {   
         printf("%c%c",0xfe,0xc3);
         printf("touche pesee");
         printf("%c%c",0xfe,0xd0);
         printf(": %c",k);
         delay_ms(100);
         printf("%c%c",0xfe,0x84);
         printf("%s","  appuyer    ");
         k='\0';
      }
   } while (true);
}


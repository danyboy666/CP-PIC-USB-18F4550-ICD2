///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 9                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "PWM sur LED.h"
int rapport_cyclique, selection, select_courante;

void main()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_16,200,16);              // 97,2 Hz
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   Port_b_pullups(true);
   setup_ccp1(CCP_PWM) ;
   Select_courante=(input_B() & 0x07);
   while(true)
   {
      while ((~(input_B()) & 0x7)==select_courante); 
      selection =(~(input_B()) & 0x7);
      switch(selection)
      {
         case 0x1: rapport_cyclique = 120;                  // à  44%
            break;
         case 0x2: rapport_cyclique = 150;              // à  28%
            break;
         case 0x4: rapport_cyclique = 195;              // à   3%
            break;
         default: rapport_cyclique= 0;                    // à 100%
      }
      printf("%c%c",0xfe,0x01);
      printf("sel_courante = %u\r\n",select_courante);
      printf("selection = %u\r\n",selection);
      printf("rap_cyclique = %u\r\n",rapport_cyclique);
      delay_ms(100);
      CCP_1 = rapport_cyclique;                         // registre à l'adresse 0xfbe
   }
}


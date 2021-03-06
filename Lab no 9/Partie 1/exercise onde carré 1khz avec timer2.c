///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 9                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "exercise onde carr� 1khz avec timer2.h"
int sortie = 1;

#INT_TIMER2    
void TIMER2_isr (void)
{
   sortie ^=1;
output_bit(PIN_B0, sortie);
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
   setup_timer_2(T2_DIV_BY_1,249,10);  //1/20 000 000*4*1*(249+1)*10=0.5 msec => 1KHz
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL); 
   
   while(TRUE);
}


///////////////////////////////////////////////////////////////////////////////
//            Applications des microcontrolleurs        243-444-RK           //
//                            Laboratoire no. 2                              //
// Programme no 2: Expérimentation du protocole RS232.                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright: Dany Ferron 2012                                               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "rs232.TEST.Partie2.h"
#include <LCD.c>


#define BUFFER_SIZE 32
BYTE buffer[BUFFER_SIZE];
BYTE next_in = 0;
BYTE next_out = 0;
BYTE n = 0;

#int_rda                                           //interruption RS232 Recevoir des données disponible
void serial_isr() {                            // directive précisant la fonction d'interruption
   int t;
   buffer[next_in]=getc();
   t=next_in;
   next_in=(next_in+1) % BUFFER_SIZE;
   if(next_in==next_out) next_in=t;           // Buffer full !!
}

#define bkbhit (next_in!=next_out)

BYTE bgetc() {
   BYTE c;
   while(!bkbhit) ;
   c=buffer[next_out];   
   next_out=(next_out+1) % BUFFER_SIZE;
   return(c);
}


void main()
{
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_oscillator(False);
   
   printf("%c%c",0xfe,0x1);
   printf("Lab 2a cours:243-444");
   printf("%c%c",0xfe,0xc0);
   printf("attente de reception\n\r");
   delay_ms(300);
   do {
      while(bkbhit)   putc( bgetc() );
      n=n+1;
   } while (TRUE);
}


////////////////////////////////////////////////////////////////////////////////
////                           EX_PWM.C                                     ////
////                                                                        ////
////   Ce programme montre comment utiliser les fonctions                   ////
////   intégrées dans le PIC PWM. Le programme prend une entrée             ////
////   analogique et utilise la valeur numérique pour définir               ////
////   le cycle de travail. La fréquence  est définie par                   ////
////   l'utilisateur sur le port RS-232.                                    ////
////                                                                        ////
////    Configurer la carte comme suit:                                     ////
////       Connectez un l'OSCILLOSCOPE à la broche C2                       ////
////        Connectez la broche A0 à la sortie du POTENTIOMÈTRE             ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2007 Custom Computer Services                ////
//// This source code may only be used by licensed users of the CCS         ////
//// C compiler.  This source code may only be distributed to other         ////
//// licensed users of the CCS C compiler.  No other use,                   ////
//// reproduction or distribution is permitted without written              ////
//// permission.  Derivative programs created using this software           ////
//// in object code form are not restricted in any way.                     ////
////////////////////////////////////////////////////////////////////////////////
#include "LAB_OPTO_DC_MOTOR.h"
#include "OPTO_DC_MOTOR_DRIVER.c"

void main(void)
{
   char selection;
   unsigned int8 value;

   printf("\r\nFrequency:\r\n");
   printf("    1) 20.8 khz\r\n");
   printf("    2) 5 khz\r\n");
   printf("    3) 1.2 khz\r\n");

   do {
     selection=getc();
   } while((selection<'1')||(selection>'3'));

   setup_ccp1(CCP_PWM);   // Configure CCP1 as a PWM

          //   The cycle time will be (1/clock)*4*t2div*(period+1)*post_diviseur
          //   In this program clock=20000000 and period=15, 63, ou 129 (below)
          //   For the three possible selections the cycle time is:
          //     (1/20000000)*4*16*(15+1)*1 =  48.0 us or 20.8 khz
          //     (1/20000000)*4*16*(63+1)*1 = 200.6 us or 5.0 khz
          //     (1/20000000)*4*16*(129+1)*2= 825.6 us or 1.2 khz

   switch(selection) {
     case '1' : setup_timer_2(T2_DIV_BY_16, 15, 1);
                break;
     case '2' : setup_timer_2(T2_DIV_BY_16, 63, 1);
                break;
     case '3' : setup_timer_2(T2_DIV_BY_16, 129, 2);
                break;
   }

  setup_port_a(ALL_ANALOG);
  setup_adc(adc_clock_internal);
  set_adc_channel( 0 );
  printf("%c\r\n",selection);

  while( TRUE ) {
    value=read_adc();

    printf("%2X\r",value);

    set_pwm1_duty(value);          // This sets the time the pulse is high each cycle.
                                   // We use the A/D input to make a easy demo. the high time will be :
                                   // if value is LONG INT : value*(1/clock)*t2div 
                                   // if value is INT: value*4*(1/clock)*t2div  for example a value of 30 and t2div of 1
                                   // the high time is 6 us
                                   // WARNING: A value too high or low will prevent the output from changing.
  }
}
 

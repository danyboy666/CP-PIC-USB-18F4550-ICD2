/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 7                                   //
//         Programme no 1: Exp�rimentation avec la conversion analogique       //
//                         digital du microcontrolleur 18F4550.                //
//                                                                             //
//  Ce programme utilise la fonction de conversion analogique digital          //
//  et en utilisant un �chantillonage sur 16 bits. Ceci convertie la sortie    //
//  zero du port A en voltm�tre digital.                                       //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// Dany Ferron 2012                                                            //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//     ANA0 est le port utilis� pour la conversion analogique digital          //
//              _________________                                              //
//            -|1              40|-RB7                                         //
//    RA0/ANA0-|                 |-RB6                                         //
//            -|    PIC18F4550   |-RB5                                         //
//            -|      @20MHz     |-RB4                                         //
//            -|                 |-RB3                                         //
//            -|                 |-RB2                                         //
//            -|                 |-RB1                                         //
//            -|                 |-RB0                                         //
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

#include "lab9_ADC_CON.h"

long int value;   
double Vfinal;   

void main()
{
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
      
#define TX1   PIN_C6
#define RX1   PIN_C7

   #use rs232(baud = 9600, xmit = TX1, rcv = RX1)
   #use fast_io(C)
   set_tris_c(0b10000000); //rc7 en entree, rx1.

      printf("%c%c",0xfe,0x1);

   while(true)
   {
      delay_ms(400);
      printf("\f");
      value = read_adc(); // Lecture du port et conversion de la valeure 
                          // recue sur le port et la met en variable int16(mot).

      Vfinal = value * 0.01953125; // Conversion en variable � virgule flottante.
        
      printf("%c%c",0xfe,0x84);      
      printf("%s","Voltmetre C.C");
      printf("%c%c",0xfe,0xc0);
      printf("%s","(precision 8 bits)");
      printf("%c%c",0xfe,0xd8);
      printf("%4.3f Volts",Vfinal);    
      }
}


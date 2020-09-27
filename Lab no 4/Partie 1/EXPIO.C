/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 4                                   //
// Programme no 1: Expérimentation avec registre à décalage                    //
//                                                                             //
//                                                                             //
// Ce programme décode la touche appuyé et affiche quelle touche à été         //
// appuyé  en lisant les valeurs décalés en provenance de la fonction          //
// read_expanded_inputs(). Cette valeur est retransmise par la fonction        //
// write_expanded_outputs() et la DEL correspondant à la touche s'allume.      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// Copyright@Dany Ferron 2012                                                  //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                                                                             //
//              _________________                                              //
//            -|1              40|-RB8                                         //
//            -|                 |-RB7                                         //
//            -|    PIC18F4550   |-RB6                                         //
//            -|      @20MHz     |-RB5   /Q7 (9)                               //
//            -|                 |-RB4    CP (2)                               //
//            -|                 |-RB3   /PL (1)                               //
//            -|                 |-RB2 <- SER (14)                             //
//            -|                 |-RB1 -> SRCLK (11)                           //
//            -|                 |-RB0 -> RCLK (12)                            //
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
//    => Pour le point boni j'ai changé le port pour RD0 à RD2 pour la         // 
//       connexion du CI 74595.                                                //
//                                                                             //
//                Configuration des connections sur les CI.                    //
//                 74165 pin    Protoboard                                     //
//                    10           +5V                                         //
//                    11           Button 1                                    //
//                    12           Button 2                                    //
//                    13           Button 3                                    //
//                    14           Button 4                                    //
//                    15           gnd                                         //
//                    3            Button 5                                    //
//                    4            Button 6                                    //
//                    5            Button 7                                    //
//                    6            Button 8                                    //
//                    8            gnd                                         //
//                    16           +5V                                         //
//                    9            pin B5                                      //
//                    1            pin B3                                      //
//                    2            pin B4                                      //
//                                                                             //
//                 74595 pin    Protoboard                                     //
//                    15           LED 1                                       //
//                    1            LED 2                                       //
//                    2            LED 3                                       //
//                    3            LED 4                                       //
//                    4            LED 5                                       //
//                    5            LED 6                                       //
//                    6            LED 7                                       //
//                    7            LED 8                                       //
//                    8            gnd                                         //
//                    13           gnd                                         //
//                    16           +5V                                         //
//                    10           +5V                                         //
//                    14           pin B2                                      //
//                    11           pin B1                                      //
//                    12           pin B0                                      //
/////////////////////////////////////////////////////////////////////////////////

#include "EXPIO.h"
#include "SLCD.c"

#include "74595.c"
#include "74165.c"
 
#define DATA_IN 255 // Valeur de départ pour la variable data

void main() 
{
   BYTE data;
   int8 pinValue;
   
   LCD_ClearDisplay();
   
   do 
   {
      read_expanded_inputs (&data); // Lecture de la valeur du port en entré.
      // Switch/Case pour évaluer quelle touche à été appuyé.
      switch(data)
      {       
       case DATA_IN-1:pinValue=1;break;
       case DATA_IN-2:pinValue=2;break;
       case DATA_IN-4:pinValue=3;break;
       case DATA_IN-8:pinValue=4;break;
       case DATA_IN-16:pinValue=5;break;
       case DATA_IN-32:pinValue=6;break;
       case DATA_IN-64:pinValue=7;break;
       case DATA_IN-128:pinValue=8;break;
       default: pinValue=0; // Valeur de la touche en relachant 
      }
         LCD_Position(1,2);
         printf("Touche pesee :%u",pinValue);
            
      write_expanded_outputs (&data); // Écriture de la valeur du port en sortie.
   } while (TRUE);
}


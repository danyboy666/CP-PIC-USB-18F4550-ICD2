/////////////////////////////////////////////////////////////////////////////////
//                 Applications des microcontrolleurs               243-444-RK //
//                         Laboratoire no. 3                                   //
// Programme no 3: Exp�rimentation avec clavier matriciel style matrice        //
// carr�e ger� par interruptions(point boni).                                  //
//                                                                             //
// Ce programme v�rifie et compare avec les donn�es mis en m�moires morte.     //
// Ces mot de passes sont stocker dans un tableau(array) et en appelant        //
// la fonction read_from_EEPROM() ce mot de passe stock� en EEPROM et mis      //
// dans une variable pour ensuite la comparer avec la combinaison entr� par    //
// l'utilisateur.                                                              //
//                                                                             //
// Une porte ET � quatre entr�s est reli� entre les broches RD4 et RD7. D�s    //
// qu'une touche est appuy�, un niveau bas se produit � la sortie de la        //
// porte ET ce qui � pour effet de causer une interruption EXTERNE             //
// sur l'entr� RB2 qui est reli�e � celle-ci.                                  //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
// Copyright@Dany Ferron 2012                                                  //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//                                                                             //
//              _________________                                              //
//            -|1              40|-                                            //
//            -|                 |-                                            //
//            -|    PIC18F4550   |-                                            //
//            -|      @20MHz     |-                                            //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-RB2 This is the port I use for the int_EXT2 //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-                                            //
//            -|                 |-RD7                                         //
//            -|                 |-RD6                                         //
//            -|                 |-RD5                                         //
//            -|                 |-RD4                                         //
//            -|                 |-RC7/RX <-This is the connection to the      //
//            -|                 |-RC6/TX ->MELabs serial LCD controller       //
//            -|                 |-                                            //
//            -|                 |-                                            //
//         RD0-|                 |-RD3                                         //
//         RD1-|20             21|-RD2                                         //
//              -----------------                                              //
//   => RD0 to RD7 Connex to the Matrix keypad                                 //
//   => I'm using a 4-way AND gate to provide an interrupt on port RB2.        // 
//                                                                             //
//                                                                             // 
//                                                                             //
//                                                                             //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
#include "Matrix Keyboard 3C.h"
#include "CLAVIER16T c-a interruption.c"
/////////////////////////////////////////////////////////////////////////////////
// Le d�but de l'addresse m�moire commence � 0xF00000: Il est � not� qu'il faut// 
// sp�cifier au compilateur quel est le type de variable, par d�fault il       //
// stock en m�moire un integer d'une longueur de 16 bits. Donc pas pratique si //  
// l'on veux lire et stocker un octet � la fois.                               //
/////////////////////////////////////////////////////////////////////////////////
#rom int8 0xF00000={'9','8','7','6'} // Code de d�verrouillage.

// D�finition et initialisation des variables servant au stockage de mot de passe 
// en EEPROM.
#define PASSWORD_LENGTH 4
char password[PASSWORD_LENGTH] = {};

// Variable de m�morisation des touches de clavier retourn�s par la fonction 
// kbd_getc();
char k;

////////////////////////////////////////////////////////////////////////////////
// L'appui d'une touche provoque un interruption du programme principal.      //
// En mettant au niveau bas les rang�es et les colonnes, on identifie quelle  //
// touche est pes�e en effectuant un OU logique et la fonction appel�e par    //
// l'interruption retourne la valeur de la touche appuy�e.                    //
////////////////////////////////////////////////////////////////////////////////
#int_EXT2 // Utilisation de l'interruption EXT2 cabl� sur le portB bit 2.
void EXT2_isr(void) 
   {  
    k=kbd_getc();
   }
// D�claration de la fonction de lecture du mot de passe stock� en m�moire morte.  
char read_from_EEPROM(int8 adr);

//////////////////////////// Programme principal.///////////////////////////////
void main() 
   {
    // Variables servant � la lecture du code entr� par l'utilisateur.
    int1 passwordValid=false;
    int8 inputCount=0;
    char userInput[PASSWORD_LENGTH] = {};
    int8 j=0;
    
    // Variable servant � d�finir la position du curseur de l'afficheur.
    int8 adr;
    
    // Initialisation des interruptions.
    enable_interrupts(int_EXT2);
    enable_interrupts(GLOBAL);
    ext_int_edge(2,H_TO_L);// Front descendant sur RB2 Interrupt ext 2
    
    //Initialisation de l'affichage.
    printf("%c%c",0xfe,0x1);
    printf("%c%c",0xfe,0x81);
    printf("Entrez votre code");
    
    adr=0xc7;// Adresse de retour pour le curseur.
    
    do
     {
      // Initialisation du port pour la lecture du clavier
      set_tris_d(0x0f);//Bit0 � bit3 en entr�e et bit 4 � bit7 en sortie
      output_low(pin_D4);
      output_low(pin_D5);
      output_low(pin_D6);
      output_low(pin_D7);
      // L'appel de cette fonction lit le code qui est en EEPROM � la premiere
      // case d'adresse m�moire disponible dans le Micro controlleur.
      read_from_EEPROM(0x00); 
              
      if(k!='\0') // Si une touche est appuy�e, donc si interruption
        {
         printf("%c%c",0xfe,adr);
         printf("%c",k);
         delay_ms(300); // Delai servant de fonction anti-rebond(DEBOUNCE)
         printf("%c%c",0xfe,adr);
         printf("*"); // Cache le caract�re entr� par l'utilisateur.
         delay_ms(200); 
         // Incr�mentation de l'addresse de la position du curseur pour la 
         // prochaine touche entr�e par l'utilisateur.
         adr++; 
         // V�rification du nombre d'appuis par l'utilisateur.
         if(inputCount<PASSWORD_LENGTH)
           {
            userInput[inputCount]=k;
            inputCount++;
           }
         // On s'assure de remettre une valeur NULL � la variable de lecture.
         k='\0'; 
        }
      // La validation du nombre de touche appuy�es se fait ici.  
      else if(inputCount==PASSWORD_LENGTH)
         {
          passwordValid=true;
         
         for(j=0;j<PASSWORD_LENGTH;j++)
           {
            // On compare le code entr� par l'utilisateur avec le mot de passe
            // qui � �t� lut auparavant par la fonction read_from_EEPROM().
            if(userInput[j]!=password[j]) 
             {
              passwordValid=false;
              printf("%c%c",0xfe,0x1);
              printf("%c%c",0xfe,0x97);
              printf("Votre code est");
              printf("%c%c",0xfe,0xd9);
              printf("incorrect!");
              delay_ms(500);
              printf("%c%c",0xfe,0x1);
              printf("%c%c",0xfe,0xd5);
              printf("Veuillez reessayer");
              printf("%c%c",0xfe,0x1);
              printf("%c%c",0xfe,0x81);
              printf("Entrez votre code");
              adr=0xc7;
             }
            // On remet la chaine entr�e par l'utilisateur a NULL pour 
            // un autre essai.
            userInput[j]='0'; 
           }
         // On remet la variable de touche appuy�e par l'utilisateur � 0 une
         // fois que les 4 touches on �t� valid�es.
         inputCount=0;
         
         if(passwordValid==true)
          {
           printf("%c%c",0xfe,0x1);
           printf("%c%c",0xfe,0x97);
           printf("Votre code est");
           printf("%c%c",0xfe,0xdb);
           printf("correct!");
           delay_ms(1000);
           printf("%c%c",0xfe,0x1);
           printf("%c%c",0xfe,0x81);
           printf("Entrez votre code");
           adr=0xc7;
          }
         }
      } 
    while(true);
   }
///////////////////////Fin du programme principal.//////////////////////////////

// Cette fonction lit et retourne le code qui est en EEPROM.
char read_from_EEPROM(int8 adr)
   { 
    int8 i;
    
    for(i=0;i<PASSWORD_LENGTH;i++) 
       {
        password[i]=read_eeprom(i+adr);
       }  
return password[i];  
   }

      

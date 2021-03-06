#byte kbd = 0xF83                  // adresse du porB= F81h

// #define constante �quivalence elles sont remplac�es par leur valeur lors de la compilation
#define set_tris_kbd(x) set_tris_d(x) //�quivalence entre le deux commande, configuration du port 0=ouput, 1=input

#define COL0 (1 << 4)           // COL0=d�calage � gauche de 4 bit : 0001 0000
#define COL1 (1 << 5)           // COL1=d�calage � gauche de 4 bit : 0010 0000
#define COL2 (1 << 6)           // COL2=d�calage � gauche de 4 bit : 0100 0000
#define COL3 (1 << 7)           // COL3=d�calage � gauche de 4 bit : 1000 0000

#define ROW0 (1 << 0)           // ROW0=d�calage � gauche de 4 bit : 0000 0001
#define ROW1 (1 << 1)           // ROW1=d�calage � gauche de 4 bit : 0000 0010   
#define ROW2 (1 << 2)           // ROW2=d�calage � gauche de 4 bit : 0000 0100
#define ROW3 (1 << 3)           // ROW3=d�calage � gauche de 4 bit : 0000 1000


#define ALL_ROWS (ROW0|ROW1|ROW2|ROW3) // All_ROWS=0000 1111 le r�sultat du OU entre Bits des vars ROWx
#define ALL_PINS (ALL_ROWS|COL0|COL1|COL2|COL3)  //ALL_PINS=1111 1111 le r�sultat du OU entre Bits des vars ROWx et colx

// Keypad layout:
char const KEYS[4][4] ={{'1','4','7','r'},    //  d�claration d'un tableau de 
                        {'2','5','8','0'},    //  caract�res de votre clavier
                        {'3','6','9','d'},    //  ( 4 lignes 4 rang�es)
                        {'*','p','b','e'}};
#define KBD_DEBOUNCE_FACTOR 50               // la variable = 50
                                  
char kbd_getc( ) {               // retourne le caract�re entr�e
   static BYTE kbd_call_count;   //variable=0 d�clar� et visible dans la fonction
   static short int kbd_down;
   static char last_key;
   static BYTE col;

   BYTE kchar;
   BYTE row;

   kchar='\0';                                 //la variable=une chaine nulle 
   
   if(++kbd_call_count>KBD_DEBOUNCE_FACTOR) {        // si l'incr�mentation kbd... est plus grand que 50
       switch (col) {                                // ex�cute l'instruction selon la valeur de col
         case 0   : set_tris_kbd(ALL_PINS&~COL0);    // &~ : ET logique avec le compl�ment 1 de COL0
                    kbd=~COL0&ALL_PINS;              // Le portB =~ le comp 1 de COL1 ET ALL_PIN
                    break;                           // On sort de sa structure switch
         case 1   : set_tris_kbd(ALL_PINS&~COL1);
                    kbd=~COL1&ALL_PINS;
                    break;
         case 2   : set_tris_kbd(ALL_PINS&~COL2);
                    kbd=~COL2&ALL_PINS;
                    break;
         case 3   : set_tris_kbd(ALL_PINS&~COL3);
                    kbd=~COL3&ALL_PINS;
                    break;           
      }  
      if(kbd_down) {                            // si kbd_down=TRUE
         if((kbd & (ALL_ROWS))==(ALL_ROWS)) {   // si (kbd ET logique 0000 1111) �gale 0000 1111
            kbd_down=FALSE;
            kchar=last_key;      // sauvegarde de last_key qui est la touche retourn�
            last_key='\0';       //initialisation de la variable=une chaine nulle
         }
      }
      else {
         if((kbd & (ALL_ROWS))!=(ALL_ROWS)) {  // si (le portb ET logique 0000 1111) n'�gale pas  0000 1111 
           if((kbd & ROW0)==0)       row=0;   // choix de la rang�e
           else if((kbd & ROW1)==0)  row=1;
           else if((kbd & ROW2)==0)  row=2;
           else if((kbd & ROW3)==0)  row=3;
           last_key =KEYS[row][col];
           kbd_down = TRUE;
           }
           else {                              // choix de la colonne
               ++col;
               if(col==4)
                  col=0;
           }
      }
      kbd_call_count=0;
   }
   set_tris_kbd(ALL_PINS);     // configuration du portB en I/O selon la variable ALL_PINS   
   return(kchar);
}

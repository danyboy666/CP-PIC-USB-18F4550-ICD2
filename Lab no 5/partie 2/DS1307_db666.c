//////////////////////////////////////////////////////////////////////////////// 
///                           DS1307_db666.C                                 /// 
///                     Driver for Real Time Clock                           /// 
///                                                                          /// 
/// ds1307_init() - Enable oscillator without clearing the seconds register  /// 
///                 used when PIC loses power and DS1307 run from 3V BAT     /// 
///                  (Must be called at the start of the program)            ///
/// write_DS1307() - Writes adress and data to the DS1307                    ///
/// read_DS1307()  - Reads the data from adress location                     ///
///                                                                          ///
//////////////////////////////////////////////////////////////////////////////// 
///                                                                          ///
/// (c)Copyright 2012: Dany Ferron                                           ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////
/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ ______________________________________________________________________________________________________________  +
+ | ADDRESS|  BIT7  |  BIT6  |  BIT5  |  BIT4  |  BIT3  |  BIT2  |  BIT1  |  BIT0  |  FUNCTION  |     RANGE     | +
+ |________|________|________|________|________|________|________|________|________|____________|_______________| +
+ |  00H   |  CH    |      10 SECONDS          |              SECOND               |   SECOND   |     00-59     | +
+ |________|________|__________________________|___________________________________|____________|_______________| +
+ |  01H   |   0    |      10 MINUTES          |              MINUTES              |   MINUTE   |     00-59     | +
+ |________|________|__________________________|___________________________________|____________|_______________| +
+ |        |        |   12   |   10HR  |       |               HOUR                |    HOUR    |               | +
+ |  02H   |   0    |________|_________| 10HR  |                                   |            |   1-12+AM/PM  | +
+ |        |        |   24   |  am/pm  |       |                                   |            |     00-23     | +
+ |________|________|________|_________|_______|___________________________________|____________|_______________| +
+ |  03H   |   0    |   0    |    0    |   0   |   0    |           DAY            |     DAY    |     01-07     | +
+ |________|________|________|_________|_______|________|__________________________|____________|_______________| +
+ |  04H   |   0    |   0    |     10 DATE     |               DATE                |    DATE    |     01-31     | +
+ |________|________|________|_________________|___________________________________|____________|_______________| +
+ |  05H   |   0    |   0    |    0    | 10MTH |               MONTH               |    MONTH   |     01-12     | +
+ |________|________|________|_________|_______|___________________________________|____________|_______________| +
+ |  06H   |        |         10 YEAR          |               YEAR                |    YEAR    |     00-99     | +
+ |________|________|__________________________|___________________________________|____________|_______________| +
+ |  07H   |  OUT   |   0    |    0    | SQWE  |   0    |    0   | RS0    |   RS1  |       Protocole Pin 7      | +
+ |________|________|________|_________|_______|________|________|________|________|____________________________| +
+                                                                                                                 +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

La premier colonne (ADDRESS) vous indique l’adresse mémoire qu’il faut 
communiquer au pic pour lui indiquer dans quel espace mémoire enregistrer 
l’octet qui va suivre sur le protocole i²C. Les colonnes (BITx) qui suivent 
décomposent cet octet. L’avant dernière colonne décrit la fonction de cet 
octet. Pour finir, les bornes des valeurs que va pouvoir contenir le 
registre à cette adresse. Il faut savoir que si vous forcez l’enregistrement 
d’une valeur hors-bornes, le composant électronique l’enregistrera bien mais 
va se mettre à faire n’importe quoi dans les incrémentations de son registre.

Comme vous pouvez le remarquer, la décomposition des 8 bits de data est un peu 
particulière. Prenons exemple sur la ligne des secondes, on a les bits 0, 1, 2, 
3 servant à coder les unités des secondes tandis que les bits 4, 5 et 6 sont 
dédiés à stocker les dizaines. On a donc 4 bits pour aller de 0 à 9, et 3 bits 
restant permettant de couvrir de 0 à 5. Le bit 7 (CH), servira à désactiver 
l’oscillateur si celui si est à 1. Ainsi chaque bit aura son importance et il 
faut composer avec ce registre pour en tirer les informations souhaitées. La 
première partie de l’adresse 02H permet de définir le mode de l’horloge en mode 
12 ou 24h. En mode 12h, le bit 5 sert alors à définir le matin ou l’aprés midi 
(AM/PM) en sachant que PM est en 1.

Pour finir, il reste la dernière adresse du registre qui se démarque, celle ci 
permet de définir les paramètres de la sortie sur le port 7 de votre DS1307. 
Ainsi suivant l’état des bits 7, 4, 1 et 0, vous obtenez la gestion de la 
fréquence d’un signal carré de 1Hz, 4kHz, 8kHz ou 32kHz.
*/

 #define DS1307_SDA PIN_B0
 #define DS1307_SCL PIN_B1


 ////////////////////////////////////////////
 // Initialise le module DS1307            //
 ////////////////////////////////////////////
 void ds1307_init()
 {
    output_float(DS1307_SCL);
    output_float(DS1307_SDA);
 }

 ////////////////////////////////////////////
 // Écrire des données à un octet DS1307   //
 ////////////////////////////////////////////
 void write_DS1307(byte address,BYTE data)
 {
    short int status; 
    i2c_start();
    i2c_write(0xd0);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
    i2c_start();
    status=i2c_write(0xd0);

    while(status==1)
    {
       i2c_start();
       status=i2c_write(0xd0);
    }
 }

 ////////////////////////////////////////////
 // Lire un octet de données DS1307        //
 ////////////////////////////////////////////
 BYTE read_DS1307(byte address)
 {
    BYTE data;
    i2c_start();
    i2c_write(0xd0); // Byte CH : 1101 000x (x: 0 = osc active, 1 = osc active)
    i2c_write(address);
    i2c_start();
    i2c_write(0xd1);
    data=i2c_read(0);
    i2c_stop();
    return(data);
 }


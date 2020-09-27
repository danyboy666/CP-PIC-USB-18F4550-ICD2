////////////////////////////////////////////////////////////////////////////////
//                             SLCD.c                                         //
//               Simplifies the use of a Serial LCD.                          //
//
// 
// 
// The value in decimal are:
// Line 1 = 0-19
// Line 2 = 64-83
// Line 3 = 20-39
// Line 4 = 84-103
//
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Copyright@ Dany Ferron 2012 & Mike Coombes 2007                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/*
#define clear_lcd             0x01 // Clear Display
#define return_home           0x02 // Cursor to Home position
#define entry_mode            0x06 // Normal entry mode
#define entry_mode_rev        0x04 // Normal entry mode  -reverse direction
#define entry_mode_scroll     0x07 // - with shift
#define entry_mode_scroll_rev 0x05 // reverse direction
 
#define system_set_8_bit      0x38 // 8 bit data mode 2 line ( 5x7 font )
#define system_set_4_bit      0x28 // 4 bit data mode 2 line ( 5x7 font )
#define system_set_reset      0x30 // Reset code
#define display_on            0x0C // Display ON - 2 line mode
#define display_off           0x08 // Display off
#define set_dd_line1          0x80 // Line 1 position 1
#define set_dd_line2          0xC0 // Line 2 position 1
#define set_dd_ram            0x80 // Line 1 position 1
#define write_data            0x00 // With RS = 1
#define cursor_on             0x0E // Switch Cursor ON
#define cursor_off            0x0C // Switch Cursor OFF
#define cursor_blink_on       0x0F // Cursor plus blink
#define cursor_shift_right    0x14 // Move cursor right
#define cursor_shift_left     0x10 // Move cursor left
#define display_shift_right   0x1C // Scroll display right
#define display_shift_left    0x18 // Scroll display left
*/


#include <stdio.h>       // library containing serial communication functions

void LCD_ClearDisplay(void)
{
  printf("%c%c",0xFE,0x01);
}
          
void LCD_CursorOn(void)
{
  printf("%c%c",0xFE,0x0E);
}

void LCD_CursorOff(void)
{
  printf("%c%c",0xFE,0x0C);
}

void LCD_DisplayOn(void)
{
  printf("%c%c",0xFE,0x0C);
}

void LCD_DisplayOff(void)
{
  printf("%c%c",0xFE,0x08);
}

void LCD_BlinkOn(void)
{
  printf("%c%c",0xFE,0x0D);
}

void LCD_BlinkOff(void)
{
  printf("%c%c",0xFE,0x0C);
}

void LCD_UnderlineOn(void)
{
  printf("%c%c",0xFE,0x0E);
}

void LCD_UnderlineOff(void)
{
  printf("%c%c",0xFE,0x0C);
}

void LCD_MoveRight(void)
{
  printf("%c%c",0xFE,0x14);
}

void LCD_MoveLeft(void)
{
  printf("%c%c",0xFE,0x10);
}

void LCD_ScrollRight(void)
{
  printf("%c%c",0xFE,0x1C);
}

void LCD_ScrollLeft(void)
{
  printf("%c%c",0xFE,0x18);
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// You must uncomment for your specific LCD                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/*
// This is for a 2x20 LCD
void LCD_Position(unsigned char line, unsigned char column)
{
unsigned char i;

if (line == 1)
   i = 64;
else
   i = 0;  //default is top line
 
if (column >= 0 && column <= 19) 
   i += column; 
else
   i = 0;  // default is column 0 
 
printf("%c%c",0xFE,128 + i);

}
*/

// This is for a 4x20 LCD
void LCD_Position(unsigned char line, unsigned char column)
{
unsigned char i;

if (line == 1)
   i = 0;
else if (line == 2)
   i = 64;  
else if (line == 3)
   i = 20;
else if (line == 4)
   i = 84;
 
if (column >= 0 && column <= 19) 
   i += column; 
else
   i = 0;  // default is column 0 
 
printf("%c%c",0xFE,128 + i);

}




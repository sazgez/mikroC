// Lcd pinout settings
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D4 at RB2_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D7_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB2_bit;

int i;

void main() {
 LCD_INIT(); // start LCD
 LCD_CMD(_LCD_CLEAR);
 delay_ms(1000);
 LCD_OUT(1, 2, "Hello!"); // write on 1.row 2.column
 
 while(1)
 {
  for(i = 0; i < 7; i++)
  {
   LCD_CMD(_LCD_SHIFT_LEFT);
   delay_ms(1000);
  }
  for(i = 0; i < 12; i++)
  {
    LCD_CMD(_LCD_SHIFT_RIGHT);
    delay_ms(1000);
  }
 }
 /*
 for(i = 0; i < 12; i++) // sola git
 {
   LCD_CMD(_LCD_SHIFT_LEFT);
   delay_ms(1000);
 }
 for(i = 0; i < 12; i++) // saga git
 {
   LCD_CMD(_LCD_SHIFT_RIGHT);
   delay_ms(1000);
 }
 */
 delay_ms(1000);
 LCD_CMD(_LCD_CLEAR);
 LCD_CHR(1, 5, "i"); // write on 1.row 5.column
}
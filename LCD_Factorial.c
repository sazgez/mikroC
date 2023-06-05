// LCD pin ayarla
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D4 at RB2_bit;

// Pin yönlendirme
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D7_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB2_bit;

int number = 6, i, factorial = 1;

void main() {
  LCD_INIT();
  LCD_CMD(_LCD_CLEAR);
  delay_ms(500);
  
  for(i = number; i > 0; i--)
  {
    factorial *= i;
  }
  
  LCD_OUT(1, 1, "Number: ");
  LCD_OUT(1, 9, number);
  delay_ms(200);
  LCD_OUT(2, 1, "Factorial: ");
  LCD_OUT(2, 12, factorial);
}
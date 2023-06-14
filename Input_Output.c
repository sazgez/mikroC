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

char sayi_txt[10], fak_txt[10];
int i, sayi, fak = 1;

void main()
{
  LCD_INIT();
  LCD_OUT(1, 2, "Sayi = ");
  LCD_OUT(2, 2, "Fak = ");
  TRISD = 255; // all pins are 1 (input)
  PORTD = 0;   // all pins are 0
  delay_ms(1000);
  while(1)
  {
    sayi = portd;
    for(i = 2; i <= sayi; i++)
    {
      fak *= i;
    }
    IntToStr(sayi, sayi_txt);
    LCD_OUT(1, 9, sayi_txt);
    IntToStr(fak, fak_txt);
    LCD_OUT(2, 9, fak_txt);
    fak = 1;
  }
}
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

int sayi1 = 89, sayi2 = 10, top;
char deger1[9], deger2[9], toplam[9];

void main() {
  top = sayi1 + sayi2;
  LCD_INIT();
  LCD_CMD(_LCD_CLEAR);
  
  IntToStr(sayi1, deger1);
  LCD_OUT(1, 2, deger1);
  
  IntToStr(sayi2, deger2);
  LCD_OUT(1, 5, deger2);
  
  IntToStr(top, toplam);
  LCD_OUT(2, 6, toplam);
}
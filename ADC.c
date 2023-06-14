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

float gelen_deger;
char gelen_deger_txt[10];

void main() {
 LCD_INIT();
 ADC_INIT();
 adcon1 = 0b00001110; // the 0.pinout of register A have been set as analog
 TRISA.B0 = 1;
 PORTA.B0 = 0;

 while(1)
 {
  gelen_deger = ADC_Read(0); // between 0 - 1023
  delay_ms(1000);
  FloatToStr(gelen_deger, gelen_deger_txt);
  LCD_OUT(1, 3, gelen_deger_txt);
 }
}
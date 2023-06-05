// Lcd pinout settings
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D7 at RB7_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D4 at RB4_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D7_Direction at TRISB7_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB4_bit;

void PWM_ayar() // PWM1 ayari
{
 TRISC.B2 = 0; // PWM 1
 PR2 = 124;
 T2CKPS1_BIT = 1; // PS 1:16
 T2CKPS0_BIT = 1; // PS 1:16
 PWM1_Set_Duty(150); // 0 - 255
 PWM1_Start();
}

void LCD_ayar()
{
 LCD_INIT();
 LCD_CMD(_LCD_CLEAR);
 LCD_CMD(_LCD_CURSOR_OFF);
}

unsigned short duty_degeri = 150;
float duty_degeri_yuzde, duty_volt_degeri;
char duty_degeri_txt [10], duty_degeri_yuzde_txt[15], duty_volt_degeri_txt[15];

void main() {
 LCD_ayar();
 PWM_ayar();

 TRISB.B0 = 1;
 TRISB.B1 = 1;

 while(1)
 {
   ByteToStr(duty_degeri, duty_degeri_txt);
   LCD_OUT(1, 3, duty_degeri_txt);

  if(PORTB.B0 == 0) // anahtara basildigi zaman
  {
   if(duty_degeri < 256) // Register max degeri 255
   {
     duty_degeri++;
     PWM1_Set_Duty(duty_degeri);
     LCD_OUT(1, 3, duty_degeri_txt);
     delay_ms(200);
   }
  }

  if(PORTB.B1 == 0) // anahtara basildigi zaman
  {
   if(duty_degeri >= 0) // Register min degeri 0
   {
     duty_degeri--;
     PWM1_Set_Duty(duty_degeri);
     LCD_OUT(1, 3, duty_degeri_txt);
     delay_ms(200);
   }
  }

  duty_degeri_yuzde = (float) duty_degeri / 255;
  FloatToStr(duty_degeri_yuzde, duty_degeri_yuzde_txt);
  LCD_OUT(2, 3, duty_degeri_yuzde_txt);

  duty_volt_degeri = (float) duty_degeri_yuzde * 5;
  FloatToStr(duty_volt_degeri, duty_volt_degeri_txt);
  LCD_OUT(3, 3, duty_volt_degeri_txt);
 }
}
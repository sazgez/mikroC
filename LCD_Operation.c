/*
   Variance islemi
   birden fazla deger bu degerler arasinda degisim gösterir.
   hata orani = 0.4;
   degerler = {2, 2.3, 2.1, 1.9, 2.1, 2}
   degerler = {2, 3.4, 5, 2.3, 1.2, 0.8}
   variance: x'ler, x degerlerin ortalamasi
   x ile ortalamanin farklari toplanarak variance hesapla
*/

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

void main() {
   int i;
   int counter = 0;
   int gelen_deger [6] = {2, 3, 2, 4, 2, 3};
   int toplam = 0; // 16
   float ortalama = 0; // 2.66
   char txt_toplam[7];
   char txt_ortalama[7];
   float fark = 0;
   float fark_power = 0;
   float variance = 0;

   LCD_INIT();
   LCD_CMD(_LCD_CLEAR);

   // birden fazla toplama islemi
   for(i = 0; i < 6; i++)
   {
      toplam = toplam + gelen_deger[i];
      counter++;
   }

   INTTOSTR(toplam, txt_toplam);
   LCD_OUT(1, 6 , txt_toplam);

   ortalama = toplam / (counter * 1.0);

   FLOATTOSTR(ortalama, txt_ortalama);
   LCD_OUT(2, 6 , txt_ortalama);

   // birden fazla cikarma islemi
   toplam = 0;
   for(i = 0; i < 6; i++)
   {
      fark = gelen_deger[i] * 1.0 - ortalama;
      fark_power = pow(fark, 2);
      toplam = toplam + fark_power;
   }

   variance = toplam / (counter * 1.0);
}
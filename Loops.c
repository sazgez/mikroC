void main() {
  short i;
  int dizi [4] = {4,5,6,8};
  trisb = 0; // PORTB output
  portb = 0; // PORTB has acquired 0 Volt
  
  if(portd.B0 == 1)
  {
    portb = dizi[1];
  }
  
  /*lolo : portb = 0;
  delay_ms(400);
  portb = 255;
  delay_ms(400);
  goto lolo;*/
  
  /*for(i = 0; i < 256; i++)
   {
     portb = i;
     delay_ms(500);
   }*/
}
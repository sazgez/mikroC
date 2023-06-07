void set_RB0() {
 OPTION_REG.INTEDG = 0;
 INTCON.INTE = 1;
 INTCON.PEIE = 1;
 INTCON.GIE = 1;
}

void set_RB4567() {
 OPTION_REG.INTEDG = 0;
 INTCON.RBIE = 1; // RB4, RB5, RB6, RB7
 INTCON.PEIE = 1;
 INTCON.GIE = 1;
}

void interrupt() {
 if(INTCON.RBIF == 1)
 {
  if(PORTB.B4 == 1)
  {
   // perform operations
  }
  if(PORTB.B5 == 1)
  {
   // perform operations
  }
  if(PORTB.B6 == 1)
  {
   // perform operations
  }
  if(PORTB.B7 == 1)
  {
   // perform operations
  }
  INTCON.RBIF = 0;
 }
 
 if(INTCON.INTF == 1)
 {
  INTCON.INTF = 0;
  PORTD = 0;
  while(1)
  {
   PORTC = 255;
   delay_ms(300);
   PORTC = 0;
   delay_ms(300);
  }
 }
}

void main() {
 set_RB0();
 TRISB.B0 = 1;
 TRISC = 0;
 TRISD = 0;
 PORTB.B0 = 0;
 PORTC = 152;
 PORTD = 0;
 
 while(1)
 {
  PORTD = 255;
  delay_ms(500);
  PORTD = 0;
  delay_ms(500);
 }
}
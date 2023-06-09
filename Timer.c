int counter_1s = 0, counter_2s = 0;

void setTimer0() // configurations is for 10 ms
{
 OPTION_REG.T0CS = 0; // internal clock usage
 OPTION_REG.PSA = 0; // prescaler assignment
 // set prescaler as 1:64
 OPTION_REG.PS0 = 1;
 OPTION_REG.PS1 = 0;
 OPTION_REG.PS2 = 1;
 TMR0 = 99; // starting value of Timer0 | configTimer0 = 255 - (T * Frekans) / (4 * Prescaler) = 255 - (10*10^-3 * 4 * 10^6) / (4 * 64) ~= 99
 INTCON.TMR0IE = 1; // 1 = enables the TMR0 Interrupt
 INTCON.PEIE = 1; // enables all unmasked peripheral interrupts
 INTCON.GIE = 1; // 1 = enables all interrupts
}

void interrupt() {
  if(INTCON.TMR0IF == 1) // overflow happened in TMR0 (FFH -> 00H)
  {
    INTCON.TMR0IF = 0;
    TMR0 = 99;
    // several operations can be executed in 10 ms
    counter_1s++; // increases every 10 ms
    if(counter_1s == 100) // every 1 second (10 ms * 100 = 1000 ms => 1 s)
    {
     PORTB = ~PORTB;
     counter_1s = 0;
    }
    counter_2s++; // increases every 10 ms
    if(counter_2s == 200) // every 2 seconds
    {
     PORTC = ~PORTC;
     counter_2s = 0;
    }
  }
}

void main() {
  TRISB = 0;
  PORTB = 0;
  TRISC = 0;
  PORTC = 0;
  TRISD = 0;
  PORTD = 0;
  // call functions after PORTs have set
  setTimer0(); // call function
  while(1) // using delay function
  {
   delay_ms(1000);
   PORTD = ~PORTD;
  }
}
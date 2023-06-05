void main() {                                                                    //           PORTC            PORTB
  int i, number, factorial = 1, upperBits, lowerBits;                            //        _ _ _ _ _ _ _ _     _ _ _ _ _ _ _ _    --> total 16 bits
  // gets the number                                                             //       2^15   ...    2^8   2^7    ...    2^0
  TRISA = 255; // all pins are set as input.
  PORTA = 0;
  // stores the lower 8 bits of the result
  TRISB = 255; // all pins are set as input.
  PORTB = 0;
  // stores the upper 8 bits of the result
  TRISC = 255; // all pins are set as input.
  PORTC = 0;
  while(1)
  {
    number = PORTA; // the value of the number is assumed to be set from user through the buttons
    if(number >= 0 && number <= 8) // factorial of numbers between 0 and 8 can be calculated
    {
      if(number == 0 || number == 1) // if number is either 0 or 1 the result is 1
      {
        PORTB = 0; // clear the previous set values
        PORTB = 0b00000001;
      }
      else // if number is greater than 1
      {
        for(i = 2; i <= number; i++)
        {
          factorial *= i;
          if(factorial > 255) // use also the second register
          {
            upperBits = (factorial >> 8) & 0xFF; // extracting the upper 8 bits by using the AND Bitwise Operator (0xFF is 8 bit long)
            lowerBits = factorial & 0xFF; // extracting the lower 8 bits by using the AND Bitwise Operator (0xFF is 8 bit long)
            PORTB = 0;          // clear the previous set values
            PORTC = 0;          // clear the previous set values
            PORTB = lowerBits;  // set the new value into PORTB
            PORTC = upperBits;  // set the new value into PORTC
          }
          else // use only the first register
          {
            PORTB = 0;         // clear the previous set values
            PORTB = factorial; // set the new value into the lower 8 bits of PORTB
          }
        }
        factorial = 1; // prepare for the next calculation
      }
    }
  }
}
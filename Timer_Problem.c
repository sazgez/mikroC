/*
    Problem: The values of the specified two dimension array have to be stored, 
    every 1.5 seconds in F1, 2 seconds in F2, and 2.5 seconds in F.
    F = F1 + F2 + ... + Fn (n = array length)
    F1 = sum of the numbers that aren't in the 1st row and column
    F2 = sum of the numbers that aren't in the 2nd row and column
*/

int count1 = 0, count2 = 0, count3 = 0, i, j, f1 = 0, f2 = 0, f3 = 0, f4 = 0, f = 0;
int array [4][4] = {{3,4,1,3},{2,5,3,5},{1,3,9,2},{2,6,5,4}};

void setTimer0() // configurations is for 10 ms
{
 OPTION_REG.T0CS = 0; // internal clock usage
 OPTION_REG.PSA = 0; // prescaler assignment
 // set prescaler as 1:128
 OPTION_REG.PS0 = 0;
 OPTION_REG.PS1 = 1;
 OPTION_REG.PS2 = 1;
 TMR0 = 255 - (0.01 * 8000000) / (4 * 128); // ~= 99
 INTCON.TMR0IE = 1; // 1 = enables the TMR0 Interrupt
 INTCON.PEIE = 1; // enables all unmasked peripheral interrupts
 INTCON.GIE = 1; // 1 = enables all interrupts
}

void interrupt() {
  if(INTCON.TMR0IF == 1) // overflow happened in TMR0 (FFH -> 00H)
  {
    INTCON.TMR0IF = 0;
    TMR0 = 255 - (0.01 * 8000000) / (4 * 128); // ~= 99
    // several operations
    count1++; // increases every 10 ms
    if(count1 == 150) // every 1.5 second (10 ms * 150 = 1500 ms => 1.5 s)
    {
     count1 = 0;
     for(i = 1; i < 4; i++) // calculate f1
     {
      for(j = 1; j < 4; i++)
      {
       f1 += array[i][j];
      }
     }
     PORTA.B0 = f1;
    }
    count2++; // increases every 10 ms
    if(count2 == 200) // every 2 seconds
    {
     count2 = 0;
     for(i = 0; i < 4; i++) // calculate f2
     {
      if(i == 1)
      {
       continue;
      }
      else
      {
        for(j = 0; j < 4; i++)
        {
         if(j == 1)
         {
          continue;
         }
         else
         {
          f2 += array[i][j];
         }
        }
      }
     }
     PORTA.B1 = f2;
    }
    count3++; // increases every 10 ms
    if(count3 == 250) // every 2.5 seconds
    {
     count3 = 0;
     for(i = 0; i < 4; i++) // calculate f3
     {
      if(i == 2)
      {
       continue;
      }
      else
      {
        for(j = 0; j < 4; i++)
        {
         if(j == 2)
         {
          continue;
         }
         else
         {
          f3 += array[i][j];
         }
        }
      }
     }
     
     for(i = 0; i < 4; i++) // calculate f4
     {
      if(i == 3)
      {
       continue;
      }
      else
      {
        for(j = 0; j < 4; i++)
        {
         if(j == 3)
         {
          continue;
         }
         else
         {
          f4 += array[i][j];
         }
        }
      }
     }
     f = f1+f2+f3+f4;
     PORTA.B2 = f;
    }
  }
}

void main() {
  setTimer0(); // call function
  TRISA.B0 = 1;
  TRISA.B1 = 1;
  TRISA.B2 = 1;
  PORTA.B0 = 0;
  PORTA.B1 = 0;
  PORTA.B2 = 0;
}
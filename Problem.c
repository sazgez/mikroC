/* 
   Problem: According to the analog input to be entered from the RA0, the LCD is 
            going to display its increment or decrement that have been acquired from 
            the RA1, regarding to the first value. The change will be calculated & 
            displayed every second.
*/

// Lcd pinout settings
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

int counter = 0;
float initial_value, current_value, difference;
char difference_txt [10];

void setTimer0() // configuration is for 10 ms
{
 OPTION_REG.T0CS = 0; // internal clock usage
 OPTION_REG.PSA = 0; // prescaler assignment to the TimerO module
 // set prescaler as 1:128
 OPTION_REG.PS0 = 0;
 OPTION_REG.PS1 = 1;
 OPTION_REG.PS2 = 1;
 TMR0 = 99; // 255 - (10*10^(-3) * 8*10^6) / (4 * 128) ~= 99
 INTCON.TMR0IE = 1; // 1 = enables the TMR0 Interrupt
 INTCON.PEIE = 1; // enables all unmasked peripheral interrupts
 INTCON.GIE = 1; // 1 = enables all interrupts
}

void interrupt()
{
 if(INTCON.TMR0IF == 1) // overflow happenes every 10 ms, and the codes below execute
 {
  INTCON.TMR0IF = 0;
  TMR0 = 99;
  counter++;
  if(counter == 100) // every 1 second (10 ms * 100 = 1000 ms => 1 s)
  {
   current_value = ADC_Read(1); // get the input from second pinout
   difference = (float) current_value - initial_value; // calculate the difference
   FloatToStr(difference, difference_txt); // conversion
   if(current_value > initial_value) // increment happened
   {
    LCD_OUT(1, 2, "+ ");
    LCD_OUT(1, 3, difference_txt);
   }
   else if(current_value == initial_value) // no difference
   {
    LCD_OUT(1, 2, "Same");
   }
   else // decrement happened
   {
    LCD_OUT(1, 2, difference_txt);
   }
  }
 }
}

void ADC_config()
{
 ADC_INIT();
 //ADCON1 = 0b00001110; // only first pinout of PORTA has been set as analog
 ADCON1 = 0b00000101; // first two pinouts (RA0 & RA1) of PORTA have been set as analog
}

void LCD_config()
{
 LCD_INIT();
 LCD_CMD(_LCD_CLEAR);
 LCD_CMD(_LCD_CURSOR_OFF);
}

void main() {
 setTimer0(); // configuration of Timer0
 ADC_config(); // configuration of ADC
 LCD_config(); // configuration of LCD
 // pinout settings
 TRISA.B0 = 1; // 1. pinout of PORTA has been set as input
 PORTA.B0 = 0; // 0 voltage have been sent
 TRISA.B1 = 1; // 2. pinout of PORTA has been set as input
 PORTA.B1 = 0; // 0 voltage have been sent
 // get the initial value of the input
 initial_value = ADC_Read(0); // get it from first pinout
}
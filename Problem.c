/* 
   Problem: According to the analog inputs to be read from the RA0 and RA1, the LCD is
            going to display them. After that some operations will be performed, and finally
            the result will also displayed on LCD & sent as an analog output.
            The operation will take place every second for the simultaniousness.
            The PWM has to produce 2 KHz frequency and the MCU has to work by
            8 MHz.
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
float adc_value1, adc_value2, temperature, damp, result;
char temperature_txt [10], damp_txt [10], result_txt [10];

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
   counter = 0;
   adc_value1 = ADC_Read(0); // get the input from first analog pinout
   adc_value2 = ADC_Read(1); // get the input from second analog pinout
   temperature = adc_value1 * (5 / 1024);
   damp = adc_value2 * (5 / 1024);
   result = (float) (temperature * damp) / 6; // assume that the formula is (T * D) / 6
   // conversion
   FloatToStr(temperature, temperature_txt);
   FloatToStr(damp, damp_txt);
   FloatToStr(result, result_txt);
   // display on LCD (assume the LCD has 6 rows & 16 columns at least)
    LCD_OUT(1, 1, "Temperature: ");
    LCD_OUT(2, 14, temperature_txt);
    LCD_OUT(3, 1, "Damp: ");
    LCD_OUT(4, 7, damp_txt);
    LCD_OUT(5, 1, "Result: ");
    LCD_OUT(6, 9, result_txt);
   // send the result through the DAC
   PWM1_Set_Duty(result);
   PORTA.B2 = result;
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

void PWM1_config()
{
 TRISC.B2 = 0; // PWM1
 PR2 = ((1/2000)/(1/8000000*4*4)) - 1; // = 249 | Period Register = ( (1/Frequency as Herz) / (1/Speed as Herz * 4 * Prescaler) ) - 1
 // set the prescaler 1:4
 T2CKPS0_BIT = 1;
 T2CKPS1_BIT = 0;
 PWM1_Set_Duty(0); // zero has been set as default value
 PWM1_Start();
}

void main() {
 setTimer0(); // configuration of Timer0
 ADC_config(); // configuration of ADC
 LCD_config(); // configuration of LCD
 PWM1_config(); // configuration of PWM1
 // pinout settings
 TRISA.B0 = 1; // input
 PORTA.B0 = 0; // reset the voltage
 TRISA.B1 = 1; // input
 PORTA.B1 = 0; // reset the voltage
 TRISA.B2 = 0; // output
 PORTA.B2 = 0; // reset the voltage
}
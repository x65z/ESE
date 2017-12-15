

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "DC.h"
int ntest = 0;
void openloopMotor(unsigned int mNum, unsigned char Dty, unsigned int Dir)  //Function to control motors - mNum is motor number, 1 for 1, 2for 2, 3 for both - Dty is duty cycle, Dir is direction, 1 or -1
{
  int delayTime = 1000; //Length of delay between Steps
  
    
    if (mNum == 1) {
    ntest = mNum;
      DDRB = 0x04; //Turn on motor chip   
    } else if (mNum == 2){
      DDRB = 0x07;
    } else {
      DDRB = 0xFF;
    }
      
      //DDRP = 0x30; //Enable motor chip with no PWM
      //PTP = 0x30;
  
    if(Dir == 1) {
      PORTB = 0xAA;  //Controls direction of both motors
    } else {
      PORTB = 0x55;
    }
    //DDRT = 0xF0;
    
         
  
  PWMCTL = 0x00;                              //set for 8 bits
  PWMPRCLK = 0;                             //Don't prescale e-clocks
  
  PWMSCLA = 1;
    
       //PWM Ch 4 Starts  

  PWMCLK |= PWMCLK_PCLK4_MASK;          //Select B as the clock source for PWM2  
  PWMPOL |=  PWMPOL_PPOL4_MASK;         //Channel 2 output high at the start of the period  
  PWMCAE &= (~PWMCAE_CAE4_MASK )&0xFF;  //Select left aligned  
  PWMPER4 = 180;                        //set period value  
  PWMDTY4 = Dty;                         //set duty value  
  PWMCNT4 = 0;                          //reset the PWM2 counter  
  //PWME |= PWME_PWME2_MASK;              //enable PWM channel 2
  
  //PWM Ch 4 Ends
  
   //PWM Ch 5 Starts  
  
  PWMCLK |= PWMCLK_PCLK5_MASK;           //Select B as the clock source for PWM3  
  PWMPOL |=  PWMPOL_PPOL5_MASK;         //Channel 3 output high at the start of the period  
  PWMCAE &= (~PWMCAE_CAE5_MASK )&0xFF;  //Select left aligned  
  PWMPER5 = 180;                        //set period value  
  PWMDTY5 = Dty;                         //set duty value  
  PWMCNT5 = 0;                          //reset the PWM3 counter  
  //PWME |= PWME_PWME3_MASK;              //enable PWM channel 3
  
  //PWM Ch 5 Ends
  
  PWME |= (PWME_PWME4_MASK | PWME_PWME5_MASK); //Enable all channels 
}
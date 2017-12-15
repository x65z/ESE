//Code for controlling all motors on bot at once, WIP
//2 DC motors for driving, stepper for turning camera, servo for moving camera up or down
//Zack H - Oct. 5, 2017 - Proj. V

//The int step can be -2, -1, 1, 2 and controls step size

//DDR:
//0001 - 1 to enable reg 0
//0010 - 2 to enable reg 1
//0100 - 4 to enable reg 2
//1000 - 8 to enable reg 3
// and etc.
//Combine these values to enable multiple registers

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

// defines
#define DOWN_COUNT_VALUE      1               // number of RTI interrupts between Duty Cycle change
#define RTI_PERIOD            0x75              // RTI period setup in RTICTL (see manual)
#define LED_BITS_MASK         (PTS_PTS2_MASK | PTS_PTS3_MASK)       // LED bits on port S
#define LED_DDR_MASK          (DDRS_DDRS2_MASK | DDRS_DDRS3_MASK)   // DDR for LED bits on port S
#define LED_BITS_INIT         PTS_PTS2_MASK     // initial value written to port S LED bits

//Global Vars
unsigned int idelay = 1500u;   //Controls angle of motor, values between 600 - 2400, 1500 is centre
unsigned int iperiod = 20000u;
unsigned int iOnTime;   
unsigned int iOffTime;

//LCD defines

#define LCD_O(value)      FORCE_BITS(PORTA, (PORTA_BIT0_MASK | PORTA_BIT1_MASK | PORTA_BIT2_MASK | PORTA_BIT3_MASK), (value))
#define FORCE_BITS(reg, mask, value)      ((reg) = (((reg)&LO_BYTE(~mask))|((value)&(mask))))
#define LO_BYTE(value)                    ((value)&0x00FF)

#define   LNYB(value)                  ((value)&0x000F)
#define   HNYB(value)                  (((value)&0x00F0)>>4)



//Functions
void sleep (volatile unsigned long time  )  
{
    while  (time>0)
    {
        volatile unsigned long i = 10;   // 1333333 This number is equivalent to 100 ms
        while (i>0)
        {
            i--;
        }
        time--;
    }
}

void openloopMotor(int mNum, unsigned char Dty, int Dir)  //Function to control motors - mNum is motor number, 1 for 1, 2for 2, 3 for both - Dty is duty cycle, Dir is direction, 1 or -1
{
  int delayTime = 1000; //Length of delay between Steps
  
    
    if (mNum == 1) {
      DDRB = 0x04; //Turn on motor chip   
    } else if (mNum == 2)
    {
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
void stepper(int steps, int step, int delayTime) {
  
    int k;
    int i = 0;
    int ArrStep[8];
    ArrStep[0] = 0x80;
    ArrStep[1] = 0xA0;
    ArrStep[2] = 0x20;
    ArrStep[3] = 0x60;
    ArrStep[4] = 0x40;
    ArrStep[5] = 0x50;
    ArrStep[6] = 0x10;
    ArrStep[7] = 0x90; //Array for stepper motor 
    
    DDRA = 0x80; //Turn on switcher enable
    PORTA = 0x80;     
    DDRT = 0xF0;
    
   while(i < steps)
    {
      i++;
      if (step > 0)
      {
        k = 0;  
      } 
      else 
      {
       k = 7; 
      }
      for(; k < 8 && k >= 0; (k = k+step+step)) //Set both sleep to 1000 for approx 5.5Hz
      {
        PTS = 4; //Turn on left LED
        PTT = ArrStep[k];
        sleep(delayTime);
        PTS = 8; //Turn on right LED
        PTT =ArrStep[k+step];
        sleep(delayTime);
      }
    }     
}

//LCD functions start-------------------------------

void entryLCD(void){
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA &= ~(PORTA_BIT5_MASK) & 0xFF; //set RS low
    PORTA &= ~(PORTA_BIT6_MASK) & 0xFF; //set RW low, write
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x00 ); //output 00
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x05 ); //output 06 with bit flip
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    sleep (300);

 
}

void func_ctrlLCD(void){

    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA &= ~(PORTA_BIT5_MASK) & 0xFF; //set RS low
    PORTA &= ~(PORTA_BIT6_MASK) & 0xFF; //set RW low, write
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x1 ); //output 02 with bit flip
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x8 ); //output 08
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    sleep (300);


    //while(LCDbusy());  
}

void disp_ctrlLCD(void){

    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA &= ~(PORTA_BIT5_MASK) & 0xFF; //set RS low
    PORTA &= ~(PORTA_BIT6_MASK) & 0xFF; //set RW low, write
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x0 ); //output 02
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0xF ); //output 08
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    sleep (300);
    
     
}


void clearLCD() {    //function to clear LCD
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA &= ~(PORTA_BIT5_MASK) & 0xFF; //set RS low
    PORTA &= ~(PORTA_BIT6_MASK) & 0xFF; //set RW low, write
    
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x00 ); //output 00

    
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O(0x01); //output 01
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    
    sleep (1500); //sleep at least 15ms  
     
}

void initLCD() {
    DDRA |= 0x0F; //Set LCD Port to output
    clearLCD();
    PORTA &= ~PORTA_BIT5_MASK & 0xFF; //set RS HIGH
    func_ctrlLCD();
    disp_ctrlLCD();
    clearLCD();
    entryLCD(); 
    
}

void printLCD(unsigned char Out) {
    unsigned char s1;
    unsigned char s2;
    
    s1 = Out << 1;
    s2 = Out >> 1;
    s1 &= 0x22;
    s2 &= 0x11;
    
    Out &= 0xCC;
    Out |= (s1 | s2);
    
  
    sleep (800);
    
    PORTA |= PORTA_BIT4_MASK; //set E high
    
    LCD_O(HNYB(Out));
    
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
   
   //sleep(600); 
     
    PORTA |= PORTA_BIT4_MASK; //set E high
    
    LCD_O(LNYB(Out));
    
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low
    
    //clearLCD();
  
    
}

void printmessageLCD(unsigned char Buf[]){
    unsigned char cBuf[] = "            ";
    int i = 0;
    unsigned char Out;
    
 
	  DDRA = 0xF0;
    TSCR2 	= 0x06; 	/* set prescaler to 64, no interrupt */
   	TSCR1 	= 0xB0; 
    DDRA |= 0x0F; //set ddra out
    
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x03 );
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low  
    
    sleep (300);
    
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x03 );
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low 
    
    sleep (200); 
    
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x03 );
    PORTA &= ~(PORTA_BIT4_MASK) & 0xfF; //set E low
    
    PORTA |= PORTA_BIT4_MASK; //set E high
    LCD_O( 0x01 );  //set 4 bit mode
    PORTA &= ~(PORTA_BIT4_MASK) & 0xFF; //set E low 
    
    sleep (300); 

	 
    initLCD();

    PORTA |= PORTA_BIT5_MASK; //set RS HIGH
	//EnableInterrupts;


  while (i < 12) {      //12 is length of string
      
        printLCD(cBuf[i]);
            
        i++;
    }
    i = 0;

  //clearLCD();
  //sleep (300); 
  initLCD();
  PORTA |= PORTA_BIT5_MASK; //set RS HIGH
  
    while (i < 12) {
      
        printLCD(Buf[i]);
            
        i++;
    }
    i = 0;
}
//LCD functions end-------------------------------

//Main Starts
void main(void) {        
   //LCD demo stuff starts ------------   
   unsigned char Buf[] = "Bot Code V1 "; 
   printmessageLCD(Buf);  
   //LCD demo stuff ends ------------   
   openloopMotor(1, 140, -1); //Parameters : Motors 1, 2 or both - Duty cycle 100 - 255 approx - Direction 1 or -1 
   stepper(10, -2, 800); //num steps, step size, delay time
   stepper(10, 2, 800); //num steps, step size, delay time
    
  //setup servo
  TSCR2 = (TSCR2_PR0_MASK | TSCR2_PR1_MASK);
  TCTL2 |= TCTL2_OL2_MASK;
 
  TSCR1  |= TSCR1_TEN_MASK | TSCR1_TFFCA_MASK ;
  TIOS |= TIOS_IOS2_MASK;
  TC2 = TCNT + idelay; //initialize compare

  iOnTime = idelay;
  iOffTime = iperiod - idelay;
   //servo ends
   
  iOnTime = idelay;
  iOffTime = iperiod - idelay;
    
  TIE |= TIE_C2I_MASK;  
  
    
    //DDRT = 0xF0;
    EnableInterrupts; 
    openloopMotor(2, 255, 1); //Parameters : Motors 1, 2 or both - Duty cycle 100 - 255 approx - Direction 1 or -1
    //stepper(10, 2, 800); //num steps, step size, delay time
    
   
    
    //DDRS = (12);  //Enable LEDs DDR
    
  for(;;) {
  
   stepper(10, -2, 800); //num steps, step size, delay time
   stepper(10, 2, 800); //num steps, step size, delay time
  
    //_FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


// RTI interrupt handler for Servo
// downcount interrupts using a static variable
// toggle LEDs when counter hits 0 and reset for the same number of counts
// RTI is interrupt #7
interrupt VectorNumber_Vtimch2 void RTIhandler( void ){

static int countDown = DOWN_COUNT_VALUE;        // counter for number of interrupts until LED toggle
static char flag = 0;        

       flag = !flag;
       
       if (flag) { //Set duty cycle
        
          TC2 += idelay;
       } else {
          TC2 += (iperiod - idelay);
          iOnTime = idelay;
          iOffTime = iperiod - idelay;
       }

      //CRGFLG = CRGFLG_RTIF_MASK;                // acknowledge the interrupt
      
      //if (--countDown == 0){                    // count this interupt -- if counted down to 0, toggle LEDs
        //TCTL1_OL4 = 0; //disable
        //TCTL1_OL4 = 1; //enable     
      //}
          
      
} // end of RTIhandler()

//Code for controlling Servo Motor
//Zack H - April 16 - Proj. IV

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
#include <mc9s12c32.h>

#include "Servo.h"

// defines
#define DOWN_COUNT_VALUE      1               // number of RTI interrupts between Duty Cycle change
#define RTI_PERIOD            0x75              // RTI period setup in RTICTL (see manual)
#define LED_BITS_MASK         (PTS_PTS2_MASK | PTS_PTS3_MASK)       // LED bits on port S
#define LED_DDR_MASK          (DDRS_DDRS2_MASK | DDRS_DDRS3_MASK)   // DDR for LED bits on port S
#define LED_BITS_INIT         PTS_PTS2_MASK     // initial value written to port S LED bits

//Global Vars
   
//extern unsigned int idelay;  //Controls angle of motor, values between 600 - 2400, 1500 is centre
unsigned int iperiod = 20000u;
unsigned int iOnTime;   
unsigned int iOffTime;



//Main Starts
void ServoSetup(void) {
  /* put your own code here */
    int delayTime = 1000; //Length of delay between Steps   
  
 
    
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
  //EnableInterrupts; 
    
    //DDRT = 0xF0;
    
   // DDRS = (12);  //Enable LEDs DDR
    
	
}


// RTI interrupt handler
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

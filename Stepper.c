#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <mc9s12c32.h>

#include "Stepper.h"


void sleep (volatile unsigned long time);
void stepper(int steps, int step, unsigned char delayTime) {
  
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
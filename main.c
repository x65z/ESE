#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SCI.h"
#include "LCD.h"
#include "DC.h"
#include "Servo.h"
#include "Stepper.h"



#define RDRF_MASK 0x20
#define BaudRate 38400
#define ClockRate 8000000
#define Divider (ClockRate/16/BaudRate)


void setLCD(int start, int size); 
void getInt(int start,int size);
void setDC(void);  
void setStepper(void);


 int i = 0;int j = 0;
 unsigned char motor,speed,dir = 0;//DC Motor vars
 unsigned int steps,stepsize,del = 0;//Stepper Motor vars 
 int strStart = 0;
 int steppos = 0;
 unsigned char fullInstruction[300] = "";
 unsigned char instructOffset = 0;
 int instructStart = 0;
 int instructEnd = 0;
 extern unsigned int idelay = 1500u;
 unsigned int temp = 0u;
 unsigned char InstructInt[5] = "";
 
void main(void) 
{
 unsigned int temp = 0;
 DDRS   = 0b00001100; 
 DDRA   = 0xF0;
 TSCR2 	= 0x06; 	
 TSCR1 	= 0xB0;
 //LCD Setup 
 LCD_DDR_DATA_OUT;
 FBitInit();
 LCDinit();
 //SCI Setup
 InitSCI(52U,0,SCICR2_RE_MASK | SCICR2_TE_MASK|SCICR2_RIE_MASK);//Initialize the SCI
 //Servo Setup
 ServoSetup();
 //stepper(10, -2, 800); //num steps, step size, delay time
 EnableInterrupts;



//openloopMotor(1, 150, -1);   //For motor control
//Parameters : Motors 1, 2 or both - Duty cycle 100 - 255 approx - Direction 1 or -1 
   
for(;;){ //Wait for an interupt flag
 
 if (myMessageFlag == 1){  //End character has been found.
         DisableInterrupts;
         //PTS = 0b00000100;
         //instructOffset = instructStart
         for (i = 0; i < 30; i++) //change back for full command
        {
           fullInstruction[i] = rxBuffer[i]; //copy instruction
           if(fullInstruction[i] == '~'){ //Find start character
            instructStart = i;
           }
           if(fullInstruction[i] == '?'){ //Find end character
            instructEnd = i;
           }
           
           //instructOffset++;
        }
        
        //instructSize = (instructEnd - instructStart);
        myMessageFlag = 0;
        EnableInterrupts; 
        
        switch(fullInstruction[instructStart+1])
        {
          case 'A'://LED_1
          //PTS = 0b00000100;
          break;
          case 'B'://LED_2
          //PTS = 0b00001000; 
          break;
          case 'C'://LCD          
          setLCD(instructStart+2,instructEnd-instructStart-2);
          break;
          case 'D'://DC Motors
          //openloopMotor(1,200,1);
          setDC();
          break;
          case 'E'://Servo
          /*if(fullInstruction[instructStart+2] == '0'){
            if(idelay != 1000){
              idelay += 100; //Up
            }
          } 
          else{
            if(idelay != 2100){
              idelay += 100; //Down
            }
          } */
          getInt(instructStart+2,instructEnd-instructStart-2);
          temp = atoi(InstructInt);
          if(temp > 2000)
          temp = 2000;
          idelay = temp;
          break;
          case 'F'://Stepper
          /*if(fullInstruction[instructStart+2] == '0'){
            if(steppos != 20){
              stepper(5, 1, 800); //num steps, step size, delay time
              steppos += 5;
            }
          } 
          else{
            if(steppos != -20){             
              stepper(5, -1, 800); //num steps, step size, delay time
              steppos -= 5;
            }
          }*/
          //stepper(10, 2, 800); //num steps, step size, delay time
          setStepper();
          break;  
        }


       }
    }
}

/* OLD SERVO SETUP
getInt(instructStart+2,instructEnd-instructStart-2);
          temp = atoi(InstructInt);
          if(temp > 2000)
          temp = 2000;
          idelay = temp;
*/


//Set string to LCD
void setLCD(int start, int size){

  for(j = 0; j < size; j++){
        LCDdata(fullInstruction[start]);
        start++;
  } 
}
//Get int from instruction
void getInt(int start, int size){

  for(j = 0; j < size; j++){
    InstructInt[j] = fullInstruction[start];
    start++;    
  } 

}
void setDC(void){  //Set DC Motor

          motor = fullInstruction[instructStart+2] - 48;//Which motor: 1=left,2=right,3=both
          
          if(motor == 0){
            openloopMotor(0,0,0);
            return;
          }
          getInt(instructStart+3,3);
          speed = atoi(InstructInt); //Speed: between 100-255
          dir = fullInstruction[instructStart+6] - 48; //Diriection: 1 for forward (NOT)1 for backwards
                  
          openloopMotor(motor,speed,dir);
}
void setStepper(void){  //Set Stepper Motor
          getInt(instructStart+2,2);
          steps = atoi(InstructInt);//How many steps to take (10-99)
     
          stepsize = fullInstruction[instructStart+4] - 48; //Which direction(+ or -) and what size(1 or 2)
          if(stepsize == 2) //Test
          stepsize = -1;
          //getInt(instructStart+5,3);
          //del = atoi(InstructInt); //Diriection: 1 for forward (NOT)1 for backwards
                  
          stepper(steps,stepsize,800);               
}


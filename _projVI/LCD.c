#include <hidef.h>      /* common defines and macros */
#include <stdarg.h>
#include <string.h>
#include "derivative.h"      /* derivative-specific definitions */
#include "LCD.h"
#include "utils.h"





const unsigned char DISP_STATE = 0x0F;
const unsigned char FUNC_STATE = 0x28;


unsigned char reverse_nybbles(unsigned char original) {
	  unsigned char HI_NYBBLE = HI_NYBBLE(original);
	  unsigned char LO_NYBBLE = LO_NYBBLE(original);
	  unsigned char reversed = 0;
	  int i;

  	for (i = 0; i < 8; i++)
  		reversed |= ((HI_NYBBLE >> i) & 1) << (7 - i);

	  HI_NYBBLE = reversed << 4;

	  reversed = 0;

	  for (i = 0; i<8; i++)
		    reversed |= ((LO_NYBBLE >> i) & 1) << (7 - i);

	  LO_NYBBLE = reversed >> 4;

  	reversed = HI_NYBBLE | LO_NYBBLE;

	  return reversed;
}   

void LCDdata(char ch) {
    //value = reverse_nybbles(value);
    LCD_DDR_DATA_OUT;
    LCD_E_LO;
    LCD_RS_DR;
    LCD_RW_WRITE;
    LCD_E_HI;
    LCD_BUS(HI_NYBBLE(ch));
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(LO_NYBBLE(ch));
    LCD_E_LO;
    Delay_ms(1);
    //while(LCDbusy());   
}


int LCDbusy(void){    
    LCD_DDR_DATA_IN;
    LCD_E_LO;
    LCD_RS_IR;
    LCD_RW_READ;
    LCD_E_HI;
    
    return (LCD_PORT&1 == 1) ? 1 : 0; 
}

void LCDclear(void){
    LCD_E_LO;
    LCD_RS_IR;
    LCD_RW_WRITE;
    LCD_E_HI;
    LCD_BUS(0x00);
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(0x01);
    LCD_E_LO;
    Delay_ms(15); 
}

void LCDhome(void){
    LCD_E_LO;
    LCD_RS_IR;
    LCD_RW_WRITE;
    LCD_E_HI;
    LCD_BUS(0x00);
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(0x02);
    LCD_E_LO;
    Delay_ms(1);  
}

void LCDentry(void){
    LCD_E_LO;
    LCD_RS_IR;
    LCD_RW_WRITE;
    LCD_E_HI;
    LCD_BUS(0x00);
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(0x06);
    LCD_E_LO;
    Delay_ms(1);
 
}

void LCDfunc_ctrl(void){
    LCD_E_LO;
    LCD_RS_IR;
    LCD_RW_WRITE;
    LCD_E_HI;
    LCD_BUS(HI_NYBBLE(FUNC_STATE));
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(LO_NYBBLE(FUNC_STATE));
    LCD_E_LO;
    Delay_ms(1);
  
}

void LCDdisp_ctrl(void){
    LCD_E_LO;
    LCD_RS_IR;
    LCD_RW_WRITE;
    LCD_E_HI;
    LCD_BUS(HI_NYBBLE(DISP_STATE));
    LCD_E_LO;
    LCD_E_HI;
    LCD_BUS(LO_NYBBLE(DISP_STATE));
    LCD_E_LO;
    Delay_ms(1);
     
}

void LCDinit(void){
    LCD_DDR_DATA_OUT;
    LCDclear();
    LCDfunc_ctrl();
    LCDdisp_ctrl();
    LCDclear();
    LCDentry(); 
}



//Delay by k ms//
void Delay_ms( int k )
{
   	int ix;			/* counter for number of ms delayed */

 	TC0 	= TCNT + 125;		/* preset TC0 for first OC event */
	TIOS   |= TIOS_IOS0_MASK;	/* ready to go - enable TC0 as OC */

	for (ix = 0; ix < k; ix++) {	/* for number of ms to delay… */
		while(!(TFLG1 & TFLG1_C0F_MASK));	/* wait for OC event */
          	TC0 += 125;		/* rearm the OC register, this clears TFLG1 */
   	}

   	TIOS  &= LO_BYTE(~TIOS_IOS0_MASK);  	/* all done – turn-off OC on TC0 */
} /* end of msDelay() */



//Initialize to 4 Bit Mode//
void FBitInit(void){
    LCD_E_HI;
    LCD_BUS( 0x03 );      // wake up display & sync
    LCD_E_LO;
    
    Delay_ms( 5 );

    LCD_E_HI;
    LCD_BUS( 0x03 );      // wake up display & sync
    LCD_E_LO;

    Delay_ms( 1 );   
    
    LCD_E_HI;
    LCD_BUS( 0x03 );      // wake up display & sync
    LCD_E_LO;
    
    LCD_E_HI;
    LCD_BUS( 0x02 );      // wake up display & sync - go to 4-bit mode
    LCD_E_LO;

	  Delay_ms( 1 );
  
}
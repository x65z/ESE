#include "utils.h"

#ifndef _LCD_H
#define _LCD_H


#define LCD_PORT_DDR        DDRA
#define LCD_PORT            PORTA
#define LCD_E_BIT           PORTA_BIT4_MASK
#define LCD_RS_BIT          PORTA_BIT5_MASK
#define LCD_RW_BIT          PORTA_BIT6_MASK
#define LCD_DATA_BITS       (PORTA_BIT0_MASK | PORTA_BIT1_MASK | PORTA_BIT2_MASK | PORTA_BIT3_MASK)

#define LCD_DDR_DATA_IN     CLR_BITS(LCD_PORT_DDR, 0x0F) //LCD DDR set Low Nybble to input
#define LCD_DDR_DATA_OUT    SET_BITS(LCD_PORT_DDR, 0x0F) //LCD DDR set Low Nybble to Output

#define LCD_BUS(value)      FORCE_BITS(LCD_PORT, LCD_DATA_BITS, (value))

#define LCD_E_HI            SET_BITS(LCD_PORT, LCD_E_BIT)
#define LCD_E_LO            CLR_BITS(LCD_PORT, LCD_E_BIT)
#define LCD_RW_READ         SET_BITS(LCD_PORT, LCD_RW_BIT)
#define LCD_RW_WRITE        CLR_BITS(LCD_PORT, LCD_RW_BIT)
#define LCD_RS_DR           SET_BITS(LCD_PORT, LCD_RS_BIT)
#define LCD_RS_IR           CLR_BITS(LCD_PORT, LCD_RS_BIT)




unsigned char reverse_nybbles(unsigned char original);
void LCDdata(char ch);
int  LCDbusy(void);
void LCDclear(void);
void LCDhome(void);
void LCDdisp_ctrl(void);
void LCDfunc_ctrl(void);
void LCDinit(void);
void LCDentry(void);
void Delay_ms( int k ); //Delay Function
void FBitInit(void);

#endif
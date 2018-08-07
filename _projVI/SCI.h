#include "utils.h"

#ifndef _SCI_H
#define _SCI_H

#define TURN_ON_TRANS SET(SCICR2,SCICR2_TE_MASK)
#define TURN_ON_RECIV SET(SCICR2,SCICR2_RE_MASK)
#define TURN_OFF_TRANS CLR(SCICR2,SCICR2_TE_MASK)
#define TURN_OFF_RECIV CLR(SCICR2,SCICR2_RE_MASK)


#define rxBufSize 300
void InitSCI(unsigned int baudRate,unsigned char SCIData,unsigned char config);
void putcSCI(char cx);
void putsSCI(char *str);
void getcSCI(char cx);
 
extern volatile char rxBuffer[rxBufSize];
extern volatile unsigned int rxIndex;
extern volatile unsigned int myMessageFlag;

#endif
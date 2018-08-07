/*Parity.h : Header file for parity calculations 
*/


#ifndef PARITY_H
#define PARITY_H
/* ^^ The above are include guards to prevent repeats of the prototyoes */

enum PARITY { PAR_EVEN, PAR_ODD, PAR_ERROR };


// Function prototypes
PARITY ParityOnBytes(char *buf, int iBufLen); 
PARITY Parity( unsigned char *buf, int iBuffLen ); 

#endif



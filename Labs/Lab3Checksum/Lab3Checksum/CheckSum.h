/* Checksum.h : Header file for parity calculations.
 */

enum CHECKSUM { CHK_16BIT, CHK_8BIT, CHK_ERROR };

// function prototypes
unsigned int Checksum( void *buf, int iBufLen, CHECKSUM iType );


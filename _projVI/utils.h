#ifndef _UTILS_H
#define _UTILS_H


// Macro to grab only the lower byte of an argument
#define LOW( value )    ((value) & 0xFF)
#define   LO_NYBBLE(value)                  ((value)&0x000F)

// Macro to set specified bits
#define SET_BITS( port, bits )            (port) |= (bits)
//#define   SET_BITS(port, mask)              ((port) |= (mask))

// Macro to clear specified bits
#define CLR_BITS( port, bits )            (port) &= LOW(~(bits))
//#define   CLR_BITS(port, mask)              ((port) &= (LO_BYTE(~mask)))

//Macro to flip specified bits
#define FLIP_BITS( port, bits )           (port) ^= (bits)
#define TOG_BITS(port, mask)              ((port) ^= (mask))
// Macro to force the bits identified by mask to take on the values of the matching bits in value
#define FORCE_BITS( port, mask, value)    (port) = ((port) & LOW(~(mask)) | ((value) & (mask)))
#define FORCE_WORD( port, mask, value)    (port) = ((port) & ((~(mask)) & 0xFFFF) | ((value) & (mask)))


#define PORT_B PORTB
#define B_DDR DDRB
#define POWER_MASK PORTAB_BIT6_MASK
#define WRITE_POWER_DDR SET_BITS(B_DDR,POWER_MASK)
#define ANALOG_ON       SET_BITS(PORT_B,POWER_MASK) 

#define   LO_BYTE(value)                    ((value)&0x00FF)
#define   HI_BYTE(value)                    ((value)&0xFF00)

#define   HI_NYBBLE(value)                  (((value)&0x00F0)>>4)



//#define   FORCE_BITS(reg, mask, value)      ((reg) = (((reg)&LO_BYTE(~mask))|((value)&(mask))))

#endif
#ifndef _KORITH_CTYPE_H_
#define _KORITH_CTYPE_H_

#define _U  0x01 
#define _L  0x02

extern const unsigned char _ctypes[]; 

#define isdigit(c)  __builtin_isdigit(c)

#endif

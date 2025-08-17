#ifndef _KORITH_STRING_H_
#define _KORITH_STRING_H_

#include <korith/types.h> 

size_t strlen(const char *str); 

#define memcpy(s, c, n) __builtin_memcpy(s, c, n)

#define memset(d, s, n) __builtin_memset(d, s, n)

#endif /* _KORITH_STRING_H_ */ 

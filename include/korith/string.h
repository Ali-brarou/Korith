#ifndef _KORITH_STRING_H_
#define _KORITH_STRING_H_

#include <korith/types.h> 

size_t __strlen(const char *str); 
#define strlen(s) __strlen(s)

#define memcpy(s, c, n) __builtin_memcpy(s, c, n)
#define ARCH_HAS_MEMCPY

#define memset(d, s, n) __builtin_memset(d, s, n)
#define ARCH_HAS_MEMSET

#endif /* _KORITH_STRING_H_ */ 

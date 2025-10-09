#ifndef _KORITH_SPRINTF_H_
#define _KORITH_SPRINTF_H_

#include <korith/types.h> 
#include <korith/stdarg.h> 
#include <korith/compiler.h> 

__printf(2, 3) int sprintf(char *buf, const char *fmt, ...); 
__printf(3, 4) int snprintf(char *buf, size_t size, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list ap); 
int vsnprintf(char *buf, size_t size, const char *fmt, va_list ap); 

#endif

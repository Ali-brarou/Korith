#ifndef _KORITH_LIMITS_H_
#define _KORITH_LIMITS_H_

#define INT_MAX     2147483647
#define INT_MIN     (-INT_MAX - 1)
#define UINT_MAX    4294967295U

#define LONG_MAX    2147483647L
#define LONG_MIN    (-LONG_MAX - 1) 
#define ULONG_MAX   4294967295UL

/* maximum size_t (since it's a 32 bit kernel) */ 
#undef SIZE_MAX /* undefine size_max from stdint */ 
#define SIZE_MAX    4294967295U

#endif

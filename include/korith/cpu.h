#ifndef _KORITH_CPU_H_
#define _KORITH_CPU_H_

#include <korith/compiler.h> 

static always_inline void cpu_halt(void) 
{
    asm volatile("hlt" ::: "memory"); 
}; 

#endif 

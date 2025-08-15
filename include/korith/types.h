#ifndef _KORITH_TYPES_H_
#define _KORITH_TYPES_H_

/* just include the gnu stddef for now */ 
#include <stddef.h> 
#include <stdint.h> 
#include <stdbool.h> 

/* will be using a linked list design based on the Linux kernel */ 
struct list_head {
    struct list_head *next, *prev; 
}; 

struct cpu_regs {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 
}; 

#endif /* _KORITH_STDDEF_H_ */

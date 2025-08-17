#ifndef _KORITH_TYPES_H_
#define _KORITH_TYPES_H_

#include <stddef.h> 
#include <stdint.h> 
#include <stdbool.h> 

/* will be using a linked list design based on the Linux kernel */ 
struct list_head {
    struct list_head *next, *prev; 
}; 

struct cpu_regs {
    uint32_t eax, ebx, ecx, edx, esi, edi, ebp;  
    uint16_t ds, __pds; 
    uint16_t es, __pes; 
    uint16_t fs, __pfs; 
    uint16_t gs, __pgs; 
    uint32_t err_code; /* used only with faults */  
    uint32_t eip; 
    uint32_t cs; 
    uint32_t flags; 

    uint32_t esp; 
    uint16_t ss, __pss; 
}; 

#endif /* _KORITH_STDDEF_H_ */

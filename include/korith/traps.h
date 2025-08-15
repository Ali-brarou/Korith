#ifndef _KORITH_TRAPS_H_
#define _KORITH_TRAPS_H_

#include <korith/types.h> 

#define NR_TRAPS    32

struct trap_desc {
    void (*handler)(struct cpu_regs* regs, uint32_t err_code); 
}; 

void trap_handle(void); 

#endif

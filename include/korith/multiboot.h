#ifndef _KORITH_MULTIBOOT_H_
#define _KORITH_MULTIBOOT_H_

#include <korith/types.h> 

struct multiboot_mem_map {
    uint32_t size;  
    uint32_t base_addr_lo, base_addr_hi; 
    uint32_t len_lo, len_hi; 
    uint32_t type; 
}; 

#endif

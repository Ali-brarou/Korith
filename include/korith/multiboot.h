#ifndef _KORITH_MULTIBOOT_H_
#define _KORITH_MULTIBOOT_H_

#define MULTIBOOT_HEADER_MAGIC      0x1BADB002 
#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002 

/* flags */ 
#define MULTIBOOT_ALIGN     0x00000001
#define MULTIBOOT_MEMINFO   0x00000002

#ifndef __ASSEMBLER__

#include <korith/types.h> 

struct multiboot_mem_map {
    uint32_t size;  
    uint32_t base_addr_lo, base_addr_hi; 
    uint32_t len_lo, len_hi; 
    uint32_t type; 
}; 

#endif /* __ASSEMBLER__ */ 

#endif /* _KORITH_MULTIBOOT_H_ */

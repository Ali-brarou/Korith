#ifndef _KORITH_MMAP_H_
#define _KORITH_MMAP_H_

#include <korith/types.h> 
#include <korith/multiboot1.h> 

#define NR_MEM_REGIONS  32

void mmap_init_multiboot(u32 mmap_addr, u32 mmap_length); 

#endif

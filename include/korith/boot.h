#ifndef _KORITH_BOOT_H_
#define _KORITH_BOOT_H_

#include <korith/multiboot1.h> 

struct boot_info {

}; 

void multiboot_parse(uint32_t magic, struct multiboot_info *mb_info);

#endif

#include <korith/multiboot1.h> 
#include <korith/boot.h>
#include <korith/panic.h> 

void multiboot_parse(u32 magic, struct multiboot_info *mb_info)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        panic("Invalid Multiboot magic 0x%x (expected: 0x%x)\n", 
              magic, 
              MULTIBOOT_BOOTLOADER_MAGIC);
    (void) mb_info; 
}

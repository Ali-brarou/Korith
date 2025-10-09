#include <korith/multiboot1.h> 
#include <korith/mmap.h> 
#include <korith/boot.h>
#include <korith/tty.h> 
#include <korith/panic.h> 

void multiboot_parse(u32 magic, struct multiboot_info *mb_info)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        panic("Invalid Multiboot magic 0x%x (expected: 0x%x)\n", 
              magic, 
              MULTIBOOT_BOOTLOADER_MAGIC);

    if (!(mb_info->flags & MULTIBOOT_INFO_MEM_MAP))
        panic("Invalid memory map\n");
    mmap_init_multiboot(mb_info->mmap_addr, mb_info->mmap_length); 
}

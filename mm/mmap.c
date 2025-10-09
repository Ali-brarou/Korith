#include <korith/mmap.h> 
#include <korith/tty.h> 
#include <korith/panic.h> 

struct mem_map {
    u32 base; 
    u32 size; 
    u32 type; 
} mem_map[NR_MEM_REGIONS]; 

void mmap_init_multiboot(u32 mmap_addr, u32 mmap_length) 
{
    struct multiboot_memory_map *mmt; 
    unsigned int i; 

    for (i = 0; i < mmap_length; i += sizeof(struct multiboot_memory_map))
    {
        mmt = (struct multiboot_memory_map *) (mmap_addr + i); 
        printk("%d %d %d\n", (u32)mmt->addr, (u32)mmt->len, mmt->type); 
    }
}

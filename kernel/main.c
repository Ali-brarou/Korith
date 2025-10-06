#include <korith/compiler.h> 
#include <korith/cpu.h>
#include <korith/tty.h> 
#include <korith/idt.h> 
#include <korith/irq.h> 
#include <korith/pic.h> 
#include <korith/timer.h> 
#include <korith/multiboot1.h>
#include <korith/boot.h> 

static void kernel_init(u32 magic, struct multiboot_info *mb_info)
{
    (void)magic; 
    (void)mb_info; 
    cli(); /* disable interrupts */  
    tty_init();
    multiboot_parse(magic, mb_info); 
    idt_init(); 
    pic_init(); 
    irq_init(); 
    timer_init(); 
}

void divide_by_zero(void)
{
    volatile int zero = 0; 
    volatile int a = 1 / zero; 
    (void)a; 
}

void kernel_main(u32 magic, struct multiboot_info *mb_info)
{
    kernel_init(magic, mb_info); 

    while (1)
    {
        sti();          /* enable interrupts for testing */  
        cpu_halt();     /* halt the cpu */ 
    }
    __unreachable(); 
}

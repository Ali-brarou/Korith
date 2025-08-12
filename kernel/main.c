#include <korith/compiler.h> 
#include <korith/tty.h> 
#include <korith/idt.h> 
#include <korith/irq.h> 

static always_inline void kernel_init(void)
{
    irq_disable(); /* disable interrupts */  
	tty_init();
    idt_init(); 
    irq_init(); 
}

void kernel_main(void)
{
    kernel_init(); 
    tty_write_string("Hello, Kernel!\n"); 

    irq_enable(); /* enable interrupts for testing */  
    while (1) 
        asm("hlt"); 
}

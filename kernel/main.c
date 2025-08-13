#include <korith/compiler.h> 
#include <korith/assert.h> 
#include <korith/tty.h> 
#include <korith/idt.h> 
#include <korith/irq.h> 
#include <korith/cpu.h> 
#include <korith/io.h> 

static always_inline void kernel_init(void)
{
    cli(); /* disable interrupts */  
    tty_init();
    idt_init(); 
    irq_init(); 
}

static const char scancode_map[] =
"\0\0331234567890-=\b"    /* 0x00–0x0E */
"\tqwertyuiop[]\n\0"      /* 0x0F–0x1C (0x1D = Ctrl, so \0) */
"asdfghjkl;'`\0\\zxcvbnm,./\0*\0 \0"; /* 0x1E–0x39 etc. */

static void keyboard_handler(uint32_t irq)
{
    uint8_t scancode = inb(0x60);
    char buff[2] = {scancode_map[scancode], 0x0};
    tty_write_string(buff);
}

struct irq_action keyboard_action = {
    .handler = keyboard_handler, 
}; 

void kernel_main(void)
{
    kernel_init(); 
    irq_register(0x1, &keyboard_action); 
    tty_write_string("Hello, Kernel!\n"); 

    while (1)
    {
        sti(); /* enable interrupts for testing */  
        cpu_halt();   /* halt the cpu */ 
    }
    __builtin_unreachable(); 
}

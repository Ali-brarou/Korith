#include <korith/idt.h> 
#include <korith/entry.h> 
#include <korith/i8259.h> 
#include <korith/tty.h>

__attribute__((aligned(0x10)))
static struct gate_desc idt_table[IDT_ENTRIES];  
static struct idt_ptr idt_descriptor; 

static inline void lidt(void *p)
{
    asm volatile("lidt (%0)" :: "r"(p) : "memory"); 
}

void default_interrupt_handler(void)
{
    /* do nothing */ 
    pic_send_eoi(0); 
}

const char scancode_map[] =
"\0\0331234567890-=\b"    /* 0x00–0x0E */
"\tqwertyuiop[]\n\0"      /* 0x0F–0x1C (0x1D = Ctrl, so \0) */
"asdfghjkl;'`\0\\zxcvbnm,./\0*\0 \0"; /* 0x1E–0x39 etc. */


void keyboard_wrapper(void); 
void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60); 
    char buff[2] = {scancode_map[scancode], 0x0}; 
    tty_write_string(buff); 
    pic_send_eoi(0x21); 
}

void idt_init(void)
{ 
    for (int i = 0; i < IDT_ENTRIES; i++)    
    {
        idt_set_entry(i, isr_wrapper, 0x08, 0x8E); 
    }
    
    idt_set_entry(0x21, keyboard_wrapper, 0x08, 0x8E); 
    idt_descriptor.limit = sizeof(idt_table) - 1; 
    idt_descriptor.base = (uint32_t)&idt_table; 

    lidt(&idt_descriptor); 
}

void idt_set_entry(uint8_t vector, void (*handler), uint16_t selector, uint8_t type_attr)
{
    uint32_t handler_addr = (uint32_t)handler;  

    idt_table[vector].offset_low = handler_addr & 0xFFFF; 
    idt_table[vector].selector = selector; 
    idt_table[vector].zero = 0; 
    idt_table[vector].type_attributes = type_attr; 
    idt_table[vector].offset_high = (handler_addr >> 16) & 0xFFFF; 
}

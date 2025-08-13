#include <korith/idt.h> 
#include <korith/entry.h> 
#include <korith/traps.h> 
#include <korith/irq.h> 
#include <korith/irq_vectors.h> 
#include <korith/tty.h>

extern void (*trap_entry_table[NR_TRAPS])(void); 
extern void (*irq_entry_table[NR_IRQS])(void); 

__attribute__((aligned(0x10)))
static struct gate_desc idt_table[IDT_ENTRIES];  
static struct idt_ptr idt_descriptor; 

static inline void lidt(void *p)
{
    asm volatile("lidt (%0)" :: "r"(p) : "memory"); 
}

void idt_init(void)
{ 
    int i; 
    for (i = 0; i < NR_TRAPS; i++)
    {
        idt_set_entry(i, trap_entry_table[i], 0x08, 0x8E); 
    }
    for (i = 0; i < NR_IRQS; i++)
    {
        idt_set_entry(i + IRQ0_VECTOR, irq_entry_table[i], 0x08, 0x8E); 
    }
    
    /* load idt */ 
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

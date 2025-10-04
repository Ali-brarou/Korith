#ifndef _KORITH_IDT_H_
#define _KORITH_IDT_H_

#include <korith/types.h> 
#include <korith/compiler.h> 

#define IDT_ENTRIES 256

struct __packed gate_desc {
    uint16_t    offset_low;  
    uint16_t    selector; 
    uint8_t     zero;  
    uint8_t     type_attributes; 
    uint16_t    offset_high; 
}; 

struct __packed idt_ptr {
    uint16_t limit; 
    uint32_t base; 
}; 

void idt_init(void); 
void idt_set_entry(uint8_t vector, void (*handler), uint16_t selector, uint8_t type_attr); 
#define idt_set_intr_gate(vector, handler) \
    idt_set_entry(vector, (void*)handler, 0x8, 0x8E)
#define idt_set_trap_gate(vector, handler) \
    idt_set_entry(vector, (void*)handler, 0x8, 0x8F)
void default_interrupt_handler(void); 

#endif

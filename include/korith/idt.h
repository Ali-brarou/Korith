#ifndef _KORITH_IDT_H_
#define _KORITH_IDT_H_

#include <korith/types.h> 
#include <korith/compiler.h> 

#define IDT_ENTRIES 256

struct gate_desc {
    u16    offset_low;  
    u16    selector; 
    u8     zero;  
    u8     type_attributes; 
    u16    offset_high; 
} __packed; 

struct idt_ptr {
    u16 limit; 
    u32 base; 
} __packed; 

void idt_init(void); 
void idt_set_entry(u8 vector, void (*handler), u16 selector, u8 type_attr); 
#define idt_set_intr_gate(vector, handler) \
    idt_set_entry(vector, (void*)handler, 0x8, 0x8E)
#define idt_set_trap_gate(vector, handler) \
    idt_set_entry(vector, (void*)handler, 0x8, 0x8F)
void default_interrupt_handler(void); 

#endif

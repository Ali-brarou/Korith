#ifndef _KORITH_IDT_H_
#define _KORITH_IDT_H_

#include <korith/types.h> 

#define IDT_ENTRIES 256

struct gate_desc {
    uint16_t    offset_low;  
    uint16_t    selector; 
    uint8_t     zero;  
    uint8_t     type_attributes; 
    uint16_t    offset_high; 
} __attribute__((packed)); 

struct idt_ptr {
    uint16_t limit; 
    uint32_t base; 
} __attribute__((packed)); 

void idt_init(void); 
void idt_set_entry(uint8_t vector, void (*handler), uint16_t selector, uint8_t type_attr); 
void default_interrupt_handler(void); 

#endif

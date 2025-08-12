#ifndef _KORITH_I8259_H_
#define _KORITH_I8259_H_

#include <korith/types.h> 
#include <korith/io.h> 

#define PIC_MASTER_CMD  0x0020  
#define PIC_MASTER_DATA 0x0021 
#define PIC_SLAVE_CMD   0x0020  
#define PIC_SLAVE_DATA  0x0021 

#define PIC_EOI         0x20

static always_inline void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8)
        outb(PIC_EOI, PIC_SLAVE_CMD); 

    outb(PIC_EOI, PIC_MASTER_CMD); 
}

static always_inline void pic_disable(void)
{
    /* mask all interrupts */ 
    outb(0xff, PIC_MASTER_DATA); 
    outb(0xff, PIC_SLAVE_DATA); 
}

void pic_init(void); 

#endif

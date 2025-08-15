#include <korith/pic.h> 
#include <korith/irq.h> 
#include <korith/irq_vectors.h> 

/* https://wiki.osdev.org/8259_PIC */ 
#define ICW1_ICW4       0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	   0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	   0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	   0x10		/* Initialization - required! */

#define ICW4_8086	   0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	   0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	   0x10		/* Special fully nested (not) */

#define CASCADE_IRQ 2


void pic_init(void)
{
    /* mask all interrupts */ 
    outb(0xff, PIC_MASTER_DATA); 
    outb(0xff, PIC_SLAVE_DATA); 

    /* initilaztion sequence */ 
    outb(ICW1_INIT | ICW1_ICW4, PIC_MASTER_CMD); 
    io_wait(); 
    outb(ICW1_INIT | ICW1_ICW4, PIC_SLAVE_CMD); 
    io_wait(); 
    outb(IRQ0_VECTOR, PIC_MASTER_DATA); 
    io_wait(); 
    outb(IRQ8_VECTOR, PIC_SLAVE_DATA); 
    io_wait(); 
    outb(1 << CASCADE_IRQ, PIC_MASTER_DATA); 
    io_wait(); 
    outb(2, PIC_SLAVE_DATA); 
    io_wait(); 

    /* use 8086 mode */ 
    outb(ICW4_8086, PIC_MASTER_DATA); 
    io_wait(); 
    outb(ICW4_8086, PIC_SLAVE_DATA); 
    io_wait(); 

    /* umask interrupts */ 
    outb(0x00, PIC_MASTER_DATA); 
    outb(0x00, PIC_SLAVE_DATA); 

}

#include <korith/irq.h> 
#include <korith/i8259.h> 

void irq_init(void)
{
    pic_init(); 
}

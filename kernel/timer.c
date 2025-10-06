#include <korith/timer.h> 
#include <korith/types.h> 
#include <korith/pit.h> 
#include <korith/irq.h> 
#include <korith/io.h> 
#include <korith/tty.h> 

u32 tick = 0; 

static void timer_handler(u32 irq)
{
    (void)irq; 
    tick++; 
    if (tick % HZ == 0)
        tty_write_string("A second passed\n"); 
}

struct irq_action timer_action = {
    .handler = timer_handler, 
}; 

void timer_init(void)
{
    pit_init(HZ); 
    
    irq_register(IRQ_TIMER0, &timer_action); 
}

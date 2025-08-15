#include <korith/irq.h> 
#include <korith/assert.h> 
#include <korith/list.h> 
#include <korith/pic.h> 
#include <korith/tty.h> 

struct irq_desc irq_desc[NR_IRQS]; 

void irq_init(void)
{
    pic_init(); 
    int i; 
    for (i = 0; i < NR_IRQS; i++)
    {
        list_head_init(&irq_desc[i].action_list); 
    }
}

void irq_handle(uint32_t irq)
{
    /* sanity check */ 
    assert(irq < NR_IRQS); 

    struct list_head *pos;  
    list_for_each(pos, &irq_desc[irq].action_list)
    {
        struct irq_action *action = list_entry(pos, struct irq_action, list); 
        /* call the handler */ 
        action->handler(irq); 
    }

    pic_send_eoi(irq); 
}

int irq_register(uint32_t irq, struct irq_action *action)
{
    /* sanity check */ 
    assert(irq < NR_IRQS); 

    list_add_tail(&action->list, &irq_desc[irq].action_list); 
    return 0;      
}

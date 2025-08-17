#include <korith/irq.h> 
#include <korith/irq_vectors.h> 
#include <korith/idt.h> 
#include <korith/debug.h> 
#include <korith/list.h> 
#include <korith/pic.h> 
#include <korith/tty.h> 

extern void (*irq_entry_table[NR_IRQS])(void);

struct irq_desc irq_desc[NR_IRQS]; 

void irq_init(void)
{
    int i; 

    pic_init(); 
    for (i = 0; i < NR_IRQS; i++)
    {
        list_head_init(&irq_desc[i].action_list); 
    }
    for (i = 0; i < NR_IRQS; i++)
    {
        idt_set_intr_gate(i + IRQ0_VECTOR, irq_entry_table[i]); 
    }
}

void irq_handle(uint32_t irq, struct cpu_regs* regs)
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

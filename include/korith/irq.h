#ifndef _KORITH_IRQ_H_
#define _KORITH_IRQ_H_

#include <korith/compiler.h> 
#include <korith/types.h>

#define NR_IRQS     16

struct irq_desc {
    struct list_head action_list; 
}; 

struct  irq_action {
    void (*handler)(u32); 
    struct list_head list;
}; 

static __always_inline void cli(void)
{
    asm volatile("cli" ::: "memory");
}

static __always_inline void sti(void)
{
    asm volatile("sti" ::: "memory");
}

void irq_init(void); 
void irq_handle(u32 irq, struct cpu_regs *regs); 
int  irq_register(u32 irq, struct irq_action *action); 

#endif

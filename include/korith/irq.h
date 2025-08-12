#ifndef _KORITH_IRQ_H_
#define _KORITH_IRQ_H_

#include <korith/compiler.h> 

#define MAX_IRQS    256

static always_inline void irq_disable(void)
{
    asm volatile("cli" ::: "memory");
}

static always_inline void irq_enable(void)
{
    asm volatile("sti" ::: "memory");
}

void irq_init(void); 

#endif

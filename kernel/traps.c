#include <korith/traps.h> 
#include <korith/panic.h> 
#include <korith/debug.h> 

/* oh no it's a trap */ 
void trap_handle(uint32_t trap, struct cpu_regs *regs) 
{
    regs_dump(regs);
    panic("it's a trap %d %d", regs->err_code, trap);
}

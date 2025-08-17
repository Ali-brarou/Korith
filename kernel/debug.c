#include <korith/debug.h> 
#include <korith/panic.h> 
#include <korith/tty.h> 

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
void regs_dump(struct cpu_regs *regs)
{
    printk("*** DUMPING REGISTERS ***\n"); 
    printk("eax: %x, ebx: %x\n", regs->eax, regs->ebx); 
    printk("ecx: %x, edx: %x\n", regs->ecx, regs->edx); 
    printk("esi: %x, edi: %x\n", regs->esi, regs->edi); 
    printk("ebp: %x, eflags: %x\n", regs->ebp, regs->flags); 
    printk("cs: %x, ds: %x\n", regs->cs, regs->ds); 
    printk("es: %x, fs: %x\n", regs->es, regs->fs); 
    printk("gs: %x, err_code: %x\n", regs->gs, regs->err_code); 
    printk("-------------------------\n"); 
}
#pragma GCC diagnostic pop

void fatal_error(const char *expr, 
                 unsigned int line,
                 const char *file)
{
    panic("FATAL: %s at %s:%d\n", expr, file, line); 
}

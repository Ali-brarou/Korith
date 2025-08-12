#include <korith/panic.h> 
#include <korith/irq.h> 
#include <korith/cpu.h> 

noreturn void panic(char* fmt, ...) 
{
    (void)fmt; 
    while (1)
    {
        irq_disable(); 
        cpu_halt(); 
    }
}

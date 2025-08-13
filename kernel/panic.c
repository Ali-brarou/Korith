#include <korith/panic.h> 
#include <korith/irq.h> 
#include <korith/cpu.h> 
#include <korith/tty.h> 

noreturn void panic(char* fmt, ...) 
{
    (void)fmt; 
    while (1)
    {
        cli(); 
        cpu_halt(); 
    }
    __builtin_unreachable(); 
}

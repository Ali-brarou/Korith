#include <korith/panic.h> 
#include <korith/compiler.h> 
#include <korith/sprintf.h> 
#include <korith/irq.h> 
#include <korith/cpu.h> 
#include <korith/tty.h> 

void panic(char* fmt, ...) 
{
    va_list ap; 
    va_start(ap, fmt); 
    vprintk(fmt, ap); 
    va_end(ap); 

    while (1)
    {
        cli(); 
        cpu_halt(); 
    }
    __unreachable(); 
}

#include <korith/assert.h> 
#include <korith/panic.h> 

noreturn void fatal_error(const char *expr, 
                          unsigned int line,
                          const char *file)
{
    (void)expr; 
    (void)line; 
    (void)file; 
    panic(""); 
}

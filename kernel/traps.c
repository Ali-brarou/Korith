#include <korith/traps.h> 
#include <korith/panic.h> 



/* oh no it's a trap */ 
void trap_handle() 
{
    panic(""); 
}

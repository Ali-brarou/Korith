#include <korith/libgcc.h>
#include <korith/compiler.h> 
#include <korith/types.h> 

/* TODO: I don't know how optimized is this */ 
unsigned long long __udivmoddi4(unsigned long long num,
                                unsigned long long den,
                                unsigned long long *rem_p)
{
    unsigned long long quot = 0, qbit = 1; 
    int shift; 

    if (unlikely(den == 0))
        return 1 / den; /* Divide intentionally by zero */

    if (num == 0)
    {
        if (rem_p)
            *rem_p = 0; 
        return 0;
    }
    
    shift = __builtin_clzll(den) - __builtin_clzll(num);
    if (shift < 0)
        shift = 0; 
    qbit <<= shift; 
    den <<= shift; 

    while (qbit)
    {
        if (den <= num)
        {
            num -= den;
            quot |= qbit; 
        }
        den >>= 1; 
        qbit >>= 1; 
    }

    if (rem_p)
        *rem_p = num; 

    return quot; 
}

#include <stddef.h> 
#include <korith/string.h> 


size_t __strlen(const char *str)
{
    const char *p = str;
    while (*p)
        p++;

    return p - str;
}


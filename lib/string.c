#include <korith/types.h> 
#include <korith/string.h> 

int strlen(const char *str)
{
    const char *p; 

    p = str;
    while (*p)
        p++;

    return p - str;
}

void *memcpy(void *dest, const void *src, unsigned int n)
{
    unsigned char *d; 
    const unsigned char *s; 

    d = dest; 
    s = src; 
    while (n--)
        *d++ = *s++; 

    return dest; 
}

void *memset(void *dest, int value, unsigned int n)
{
    unsigned char *d; 
    unsigned char v; 
    
    d = dest; 
    v = value; 
    while (n--)
        *d++ = v; 
    return dest; 
}

#include <stddef.h> 
#include <korith/string.h> 

/* generic fallback */
#ifndef ARCH_HAS_STRLEN 
size_t __strlen(const char *str)
{
    const char *p = str;
    while (*p)
        p++;

    return p - str;
}
#endif

#ifndef ARCH_HAS_MEMSET 
void *__memset(void *s, int c, size_t n)
{
    uint8_t *p = s; 
    while (n--)
        *p++ = (uint8_t)c; 

    return s; 
}
#endif 

#ifndef ARCH_HAS_MEMCPY 
void *__memcpy(void *dest, void *src, size_t n)
{
    uint8_t *p = dest; 
    while(n--)
        *p++ = *(uint8_t*)src++; 

    return dest; 
}
#endif

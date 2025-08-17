#include <korith/sprintf.h> 
#include <korith/limits.h> 

int sprintf(char *buff, const char *fmt, ...)
{
    va_list ap;   
    va_start(ap, fmt); 

    const int ret = vsprintf(buff, fmt, ap); 
    va_end(ap); 

    return ret; 
}

int snprintf(char *buff, size_t size, const char *fmt, ...) 
{
    va_list ap;   
    va_start(ap, fmt); 

    const int ret = vsnprintf(buff, size, fmt, ap); 
    va_end(ap); 

    return ret; 
}

int vsprintf(char *buff, const char *fmt, va_list ap)
{
    return vsnprintf(buff, INT_MAX, fmt, ap); 
}

/* doesnt handle sign for now */ 
static char *number(char *p, char *end, uint64_t num, int base)
{
    char temp[66]; 
    const char* digits = "0123456789abcdef";
    int i; 

    i = 0; 
    do 
    {
        temp[i++] = digits[num % base]; 
    } while (num /= base); 

    while (i-- && p < end)
        *p++ = temp[i]; 

    return p; 
}

/* a minimalistic vsnprintf */ 
int vsnprintf(char *buff, size_t size, const char *fmt, va_list ap)
{
    char *p = buff, *end = buff + size; 
    while (*fmt && p < end)
    {
        if (*fmt != '%')
        {
            *p++ = *fmt++; 
            continue; 
        }

        fmt++; 
        switch (*fmt)
        {
            case 's': 
                const char *str = va_arg(ap, const char *); 
                while (*str && p < end )
                    *p++ = *str++; 
                break; 
            case 'd': 
                int d = va_arg(ap, int); 
                p = number(p, end, d, 10); 
                break; 
            case 'x': 
                int x = va_arg(ap, int); 
                p = number(p, end, x, 16); 
                break; 
            default: 
                *p++ = *fmt; 
                break; 
        }
        fmt++; 
    }
    *p = '\0'; 
    return (int)(p - buff); 
}

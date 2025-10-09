#include <korith/sprintf.h> 
#include <korith/limits.h> 
#include <korith/compiler.h>
#include <korith/string.h> 

/*
 * Inspired by the Linux kernel's vsnprintf implementation
 * (see lib/vsprintf.c), GPL-2.0 licensed.
 * Reimplemented from scratch
 */

struct fmt {
    const char *str;
#define FMT_STATE_TEXT  0
#define FMT_STATE_PERC  1
#define FMT_STATE_NUM   2
#define FMT_STATE_STR   3
    unsigned char state;
    unsigned char size;
};

struct fmt_spec {
    unsigned char base;
#define FMT_SPEC_SIGN   0x01
    unsigned char flags;
};

static struct fmt fmt_parse(struct fmt fmt, struct fmt_spec *spec)
{
    const char *start = fmt.str;
    fmt.state = FMT_STATE_TEXT;

    for (;*fmt.str; fmt.str++)
    {
        if (*fmt.str == '%')
            break;
    }

    if (fmt.str != start || !*fmt.str)
        return fmt;

    fmt.str++; /* ignore the percent char */
    switch (*fmt.str)
    {
        case '\0':
            return fmt;

        case '%':
            fmt.state = FMT_STATE_PERC;
            break;

        case 'd':
            spec->base = 10;
            spec->flags = FMT_SPEC_SIGN;
            fmt.state = FMT_STATE_NUM;
            fmt.size  = sizeof(int);
            break;

        case 'x':
            spec->base = 16;
            spec->flags = 0;
            fmt.state = FMT_STATE_NUM;
            fmt.size  = sizeof(int);
            break;

        case 's':
            fmt.state = FMT_STATE_STR;
            break;
        default:
            break;
    }

    fmt.str++;
    return fmt;
}

static char *number(char *p, char *end, unsigned long long num, struct fmt_spec spec)
{
    char temp[3 * sizeof(num)];
    char sign = '\0';
    const char* digits = "0123456789abcdef";
    int i = 0;

    if (spec.flags & FMT_SPEC_SIGN)
    {
        if ((signed long long)num < 0)
        {
            sign = '-';
            num = -(signed long long)num;
        }
    }

    do
    {
        temp[i++] = digits[num % spec.base];
    } while (num /= spec.base);

    /* add sign to the end of the temp buffer since it will be reversed */
    if (sign)
        temp[i++] = sign;

    while (--i >= 0)
    {
        if (p < end)
            *p = temp[i];
        p++;
    }

    return p;
}

static char *string(char *p, char *end, const char *s, struct fmt_spec __unused spec)
{
    int len;

    if (!s)
        s = "(null)";

    len = strlen(s);
    if (p < end)
    {
        int copy = len;
        if (copy > end - p)
            copy = end - p;
        memcpy(p, s, copy);
    }

    p += len;
    return p;
}

int vsnprintf(char *buf, size_t size, const char *fmt_str, va_list ap)
{
    char *p = buf, *end = buf + size;
    struct fmt fmt = {0};
    struct fmt_spec spec = {0};

    if (end < buf)
    {
        end = (void *)-1;
        size = end - buf;
    }

    if (size > INT_MAX)
        return 0;

    fmt.str = fmt_str;

    while (*fmt.str)
    {
        const char *old_fmt = fmt.str;
        fmt = fmt_parse(fmt, &spec);

        switch (fmt.state)
        {
            case FMT_STATE_TEXT:
            {
                int read = fmt.str - old_fmt;
                if (p < end)
                {
                    int copy = read;
                    if (copy > end - p)
                        copy = end - p;
                    memcpy(p, old_fmt, copy);
                }
                p += read;
                continue;
            }

            case FMT_STATE_NUM:
            {
                int num = va_arg(ap, int);
                p = number(p, end, (unsigned int)num, spec);
                continue;
            }

            case FMT_STATE_STR:
            {
                const char *str = va_arg(ap, char *);
                p = string(p, end, str, spec);
                continue;
            }

            case FMT_STATE_PERC:
            {
                if (p < end)
                    *p = '%';
                p++;
                continue;
            }

            default:
                break;
        }
    }

    if (size > 0)
    {
        if (p < end)
            *p = '\0';
        else
            end[-1] = '\0';
    }
    return (int)(p - buf);
}

int sprintf(char *buf, const char *fmt_str, ...)
{
    va_list ap;
    va_start(ap, fmt_str);

    const int ret = vsprintf(buf, fmt_str, ap);
    va_end(ap);

    return ret;
}

int snprintf(char *buf, size_t size, const char *fmt_str, ...)
{
    va_list ap;
    va_start(ap, fmt_str);

    const int ret = vsnprintf(buf, size, fmt_str, ap);
    va_end(ap);

    return ret;
}

int vsprintf(char *buf, const char *fmt_str, va_list ap)
{
    return vsnprintf(buf, INT_MAX, fmt_str, ap);
}

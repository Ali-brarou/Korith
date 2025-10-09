#ifndef _KORITH_DEBUG_H_
#define _KORITH_DEBUG_H_

#include <korith/compiler.h> 
#include <korith/types.h> 
#include <korith/tty.h> 

void regs_dump(struct cpu_regs *regs); 
__noreturn void fatal_error(const char *msg,
                            unsigned int line,
                            const char *file); 

#define BUG() fatal_error("Bug hit!", __LINE__, __FILE__)

#define WARN(cond, fmt, ...)    \
    do {                        \
        if (cond)               \
        {                       \
            printk("Warning: " fmt "\n", ##__VA_ARGS__); \
        }                       \
    } while(0)

#define static_assert(expr, msg) _Static_assert(expr, msg)

#endif

#ifndef _KORITH_DEBUG_H_
#define _KORITH_DEBUG_H_

#include <korith/compiler.h> 
#include <korith/types.h> 

void regs_dump(struct cpu_regs *regs); 
__noreturn void fatal_error(const char *msg,
                            unsigned int line,
                            const char *file); 

#define bug() fatal_error("Bug hit!", __LINE__, __FILE__)

#ifdef NDEBUG
#define assert(expr) (void)(0)
#else 
#define assert(expr) \
    (expr) ? (void)(0) : fatal_error("Assertion failed : (" #expr ")", __LINE__, __FILE__)
#endif


#endif

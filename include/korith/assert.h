#ifndef _KORITH_ASSERT_H_
#define _KORITH_ASSERT_H_

#include <korith/compiler.h> 

noreturn void fatal_error(const char *msg,
                          unsigned int line,
                          const char *file); 

#define bug() fatal_error("Bug hit!", __LINE__, __FILE__)

#ifdef NDEBUG
#define assert(expr) (void)(0)
#else 
#define assert(expr) \
    (expr) ? (void)(0) : fatal_error("Assertion failed : " #expr, __LINE__, __FILE__)
#endif


#endif

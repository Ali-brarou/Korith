#ifndef _KORITH_COMPILER_H_
#define _KORITH_COMPILER_H_

#if !defined(__GNUC__) && !defined(__clang__)
#error "This code requires GCC or Clang compiler."
#endif

#define __always_inline     inline __attribute__((always_inline))
#define noinline            __attribute__((__noinline__))
#define __noreturn          __attribute__((noreturn))
#define __weak              __attribute__((weak)) 
#define __printf(a, b)      __attribute__((format(printf, a, b)))

#define __packed            __attribute__((packed))

#define likely(x)           __builtin_expect(!!(x), 1)
#define unlikely(x)         __builtin_expect(!!(x), 0)

#define __unreachable()     __builtin_unreachable()
#define __unused            __attribute__((unused))

#endif

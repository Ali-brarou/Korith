#ifndef _KORTIH_COMPILER_H_
#define _KORITH_COMPILER_H_

#if !defined(__GNUC__) && !defined(__clang__)
#error "This code requires GCC or Clang compiler."
#endif

#define always_inline   inline __attribute__((always_inline))
#define noreturn        __attribute__((noreturn))
#define weak            __attribute__((weak))

#endif

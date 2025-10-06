#ifndef _KORITH_STDDEF_H_
#define _KORITH_STDDEF_H_

enum {
    false = 0, 
    true  = 1
}; 

#undef offsetof
#define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

#endif

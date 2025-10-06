#ifndef _KORITH_TYPES_H_
#define _KORITH_TYPES_H_

typedef unsigned char       __u8; 
typedef unsigned short      __u16; 
typedef unsigned int        __u32; 
typedef unsigned long long  __u64; 

typedef signed char         __s8; 
typedef signed short        __s16; 
typedef signed int          __s32; 
typedef signed long long    __s64; 

typedef __u8    u8; 
typedef __u16   u16; 
typedef __u32   u32; 
typedef __u64   u64; 

typedef __s8    s8; 
typedef __s16   s16; 
typedef __s32   s32; 
typedef __s64   s64; 

typedef __u32   size_t; 

/* will be using a linked list design based on the Linux kernel */ 
struct list_head {
    struct list_head *next, *prev; 
}; 

struct cpu_regs {
    u32 eax, ebx, ecx, edx, esi, edi, ebp;  
    u16 ds, __pds; 
    u16 es, __pes; 
    u16 fs, __pfs; 
    u16 gs, __pgs; 
    u32 err_code; /* used only with faults */  
    u32 eip; 
    u32 cs; 
    u32 flags; 

    u32 esp; 
    u16 ss, __pss; 
}; 

#endif /* _KORITH_STDDEF_H_ */

#ifndef _KORITH_IO_H_
#define _KORITH_IO_H_

#include <korith/types.h> 
#include <korith/compiler.h> 

static __always_inline u8 inb(u16 port)
{
    u8 ret; 
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory"); 
    return ret; 
}

static __always_inline void outb(u8 value, u16 port)
{
    asm volatile("outb %b0, %w1" :: "a"(value), "Nd"(port) : "memory"); 
}

static __always_inline void io_wait(void)
{
    outb(0, 0x80); 
}

#endif

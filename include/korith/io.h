#ifndef _KORITH_IO_H_
#define _KORITH_IO_H_

#include <korith/types.h> 
#include <korith/compiler.h> 

static __always_inline uint8_t inb(uint16_t port)
{
    uint8_t ret; 
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory"); 
    return ret; 
}

static __always_inline void outb(uint8_t value, uint16_t port)
{
    asm volatile("outb %b0, %w1" :: "a"(value), "Nd"(port) : "memory"); 
}

static __always_inline void io_wait(void)
{
    outb(0, 0x80); 
}

#endif

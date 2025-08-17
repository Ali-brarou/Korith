#ifndef _KORITH_TTY_H_
#define _KORITH_TTY_H_

#include <korith/types.h>
#include <korith/compiler.h> 
#include <korith/stdarg.h> 

void tty_init(void); 
void tty_set_color(uint8_t color); 
void tty_put_entry_at(char c, uint8_t color, size_t x, size_t y); 
void tty_putchar(char c); 
void tty_write(const char *data, size_t size); 
void tty_write_string(const char *data); 

/* a temporary solution */ 
__printf(1, 2) void printk(char *fmt, ...); 
void vprintk(char *fmt, va_list ap); 

#endif /* _KORITH_TTY_H_ */ 

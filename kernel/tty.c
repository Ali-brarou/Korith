#include <korith/tty.h> 
#include <korith/vga.h> 
#include <korith/string.h>  
#include <korith/sprintf.h> 

size_t      tty_row;
size_t      tty_column;
u8     tty_color; 
u16    *tty_buffer = (u16*)VGA_MEMORY;

void tty_init(void)
{
    tty_row = 0; 
    tty_column = 0; 
    tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK); 
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            tty_buffer[index] = vga_entry(' ', tty_color);
        }
    }
}

void tty_set_color(u8 color)
{
    tty_color = color; 
}

void tty_put_entry_at(char c, u8 color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    tty_buffer[index] = vga_entry(c, color);
}

void tty_scroll(void)
{
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
    {
        memcpy(&tty_buffer[y * VGA_WIDTH], &tty_buffer[(y+1) * VGA_WIDTH], VGA_WIDTH * 2); 
    }
    /* clear last line */ 
    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        tty_buffer[index] = vga_entry(' ', tty_color);
    }
    if (tty_row > 0)
        tty_row--; 
}

void tty_putchar(char c)
{
    if (c == '\n')
    {
        tty_column = 0;
        tty_row++;
        if (tty_row == VGA_HEIGHT)
            tty_scroll(); 
        return;
    }
    tty_put_entry_at(c, tty_color, tty_column, tty_row);
    if (++tty_column== VGA_WIDTH) {
        tty_column = 0;
        if (++tty_row == VGA_HEIGHT)
            tty_scroll(); 
    }
}

void tty_write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        tty_putchar(data[i]);
}

void tty_write_string(const char *data)
{
    tty_write(data, strlen(data));
}

void printk(char *fmt, ...)
{
    va_list ap; 
    va_start(ap, fmt); 
    vprintk(fmt, ap); 
    va_end(ap); 
}

void vprintk(char *fmt, va_list ap)
{
    char buff[256]; 
    int size; 

    size = vsnprintf(buff, sizeof buff, fmt, ap); 
    tty_write(buff, size); 
}

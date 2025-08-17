#include <korith/pit.h> 
#include <korith/io.h> 

#define PIT_FREQ    1193182

#define PIT_CMD     0x43
#define PIT_CH0     0x40
#define PIT_CH1     0x41
#define PIT_CH2     0x42

#define PIT_MODE0   0x00 /* interrupte on terminal count    */
#define PIT_MODE1   0x02 /* hardware retriggerable on shot  */
#define PIT_MODE2   0x04 /* rate generator                  */
#define PIT_MODE3   0x06 /* square wave                     */

#define PIT_CNT0    0x00
#define PIT_CNT1    0x40
#define PIT_CNT2    0x80
#define PIT_RB      0xC0

#define PIT_LATCH   0x00
#define PIT_LO      0x10
#define PIT_HI      0x20
#define PIT_LOHI    0x30

#define PIT_BIN     0x00
#define PIT_BCD     0x01

void pit_init(uint32_t hz)
{
    uint32_t divisor = PIT_FREQ / hz;

    outb(PIT_CNT0 | PIT_LOHI | PIT_MODE3 | PIT_BIN, PIT_CMD);
    outb(divisor & 0xff, PIT_CH0);
    outb(divisor >> 8, PIT_CH0);
}

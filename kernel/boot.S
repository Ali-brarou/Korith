#include <korith/multiboot1.h>

.set MULTIBOOT_FLAGS,         MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO 
.set MULTIBOOT_CHECKSUM,      -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_FLAGS)

/* Multiboot header */ 
.section .multiboot
.align 16
.long MULTIBOOT_HEADER_MAGIC    /* Header */ 
.long MULTIBOOT_FLAGS           /* Flags */  
.long MULTIBOOT_CHECKSUM        /* Checksum */  
/* Unused. Only valid if MULTIBOOT_AOUT_KLUDGE is set */ 
.long 0
.long 0
.long 0
.long 0
.long 0 
/* Unused. Only valid if MULTIBOOT_VIDEO_MODE is set */ 
.long 0
.long 0
.long 0
.long 0

/* stack */  
.section .bss
stack_bottom: 
.skip 16384
stack_top: 

.section .rodata
.align 8
gdt_start: 
    .long 0x0
    .long 0x0

    /* Code segment descriptor */
    .word 0xFFFF          /* Limit low */
    .word 0x0000          /* Base low */
    .byte 0x00            /* Base middle */
    .byte 0x9A            /* Access: Present, ring 0, code segment */
    .byte 0xCF            /* Flags: 4K granularity, 32-bit */
    .byte 0x00            /* Base high */

    /* Data segment descriptor */
    .word 0xFFFF          /* Limit low */
    .word 0x0000          /* Base low */
    .byte 0x00            /* Base middle */
    .byte 0x92            /* Access: Present, ring 0, data segment */
    .byte 0xCF            /* Flags: 4K granularity, 32-bit */
    .byte 0x00            /* Base high */ 
gdt_end: 

gdt_ptr: 
    .word gdt_end - gdt_start - 1 
    .long gdt_start            

.section .text
.code32
.global _start
.type _start, @function 
_start:     
    /* load gdt */ 
    cli             /* disable interrupts */ 
    lgdt gdt_ptr 

    /* reload segment registers */ 
    mov $0x10, %cx 
    mov %cx, %ds
    mov %cx, %es
    mov %cx, %fs
    mov %cx, %gs
    mov %cx, %ss
    ljmp $0x8, $reload_cs /* setup cs */  

reload_cs: 
    /* Setup the stack */ 
    mov $stack_top, %esp 


    /* Main kernel function */ 
    push %ebx /* push Multiboot info struct */
    push %eax /* push Multiboot magic value */ 
    call kernel_main 

    /* Unreachable. Enter an infinit loop */
    cli 
hang: 
    hlt
    jmp hang

.size _start, . - _start

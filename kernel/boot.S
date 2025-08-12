.code32
.set ALIGN_FLAG,    1<<0
.set MEMINFO_FLAG,  1<<1
.set FLAGS,         ALIGN_FLAG | MEMINFO_FLAG  
.set MAGIC,         0x1BADB002  
.set CHECKSUM,      -(MAGIC + FLAGS)

.section .multiboot
.align 16
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Manually creating a stack */ 
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
.global _start
.type _start, @function 
_start:     
    /* load gdt */ 
    cli             /* disable interrupts */ 
    lgdt gdt_ptr 

    /* reload segment registers */ 
    mov $0x10, %ax 
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ljmp $0x8, $reload_cs /* setup cs */  
reload_cs: 

    /* Setup the stack */ 
    mov $stack_top, %esp 

    /* Main kernel function */ 
    call kernel_main 

    /* Enter an infinit loop */
    cli 
hang: 
    hlt
    jmp hang

.size _start, . - _start

.code32
#include <korith/irq_vectors.h> 

/* put the table in text section for security in non nx old cpus*/ 
.section .text 
.global trap_entry_table

/* cpu exceptions */ 
.altmacro
.macro TRAP_NOERRCODE num
trap\num: 
    push $0 /* dummy error code */ 
    push num
    jmp trap_common_entry
    popal
.endm

.macro TRAP_ERRCODE num 
trap\num: 
    push num
    jmp trap_common_entry
.endm

TRAP_NOERRCODE 0
TRAP_NOERRCODE 1
TRAP_NOERRCODE 2
TRAP_NOERRCODE 3
TRAP_NOERRCODE 4
TRAP_NOERRCODE 5
TRAP_NOERRCODE 6
TRAP_NOERRCODE 7
TRAP_ERRCODE   8
TRAP_NOERRCODE 9
TRAP_ERRCODE   10
TRAP_ERRCODE   11
TRAP_ERRCODE   12
TRAP_ERRCODE   13
TRAP_ERRCODE   14
TRAP_NOERRCODE 15
TRAP_NOERRCODE 16
TRAP_ERRCODE   17
TRAP_NOERRCODE 18
TRAP_NOERRCODE 19
TRAP_NOERRCODE 20
TRAP_ERRCODE   21
TRAP_NOERRCODE 22
TRAP_NOERRCODE 23
TRAP_NOERRCODE 24
TRAP_NOERRCODE 25
TRAP_NOERRCODE 26
TRAP_NOERRCODE 27
TRAP_NOERRCODE 28
TRAP_ERRCODE   29
TRAP_ERRCODE   30
TRAP_NOERRCODE 31

trap_common_entry: 
    pushal
    cld
    call trap_handle 
    popal
    add $8, %esp
    iret

.macro insert_trap num
    .long trap\num
.endm

.align 4
trap_entry_table: 
.set i, 0
.rept 32
    insert_trap %i
    .set i, i+1
.endr 

.global isr_wrapper
.global keyboard_wrapper
isr_wrapper: 
    pushal
    cld
    call default_interrupt_handler
    popal
    iret

keyboard_wrapper: 
    pushal
    cld
    call keyboard_handler 
    popal
    iret
    

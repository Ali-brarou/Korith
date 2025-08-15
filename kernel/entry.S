.code32
#include <korith/irq_vectors.h> 

/* put the table in text section for security in non nx old cpus*/ 
.section .text 
.global trap_entry_table
.global irq_entry_table

.macro SAVE_ALL 
    pushal
.endm 

.macro RESTORE_ALL 
    popal
.endm 

/* cpu exceptions */ 
.altmacro
.macro BUILD_TRAP_NOERRCODE num
trap\num: 
    push $0 /* dummy error code */ 
    push $\num
    jmp trap_common
.endm

.macro BUILD_TRAP_ERRCODE num 
trap\num: 
    push $\num
    jmp trap_common
.endm

BUILD_TRAP_NOERRCODE 0
BUILD_TRAP_NOERRCODE 1
BUILD_TRAP_NOERRCODE 2
BUILD_TRAP_NOERRCODE 3
BUILD_TRAP_NOERRCODE 4
BUILD_TRAP_NOERRCODE 5
BUILD_TRAP_NOERRCODE 6
BUILD_TRAP_NOERRCODE 7
BUILD_TRAP_ERRCODE   8
BUILD_TRAP_NOERRCODE 9
BUILD_TRAP_ERRCODE   10
BUILD_TRAP_ERRCODE   11
BUILD_TRAP_ERRCODE   12
BUILD_TRAP_ERRCODE   13
BUILD_TRAP_ERRCODE   14
BUILD_TRAP_NOERRCODE 15
BUILD_TRAP_NOERRCODE 16
BUILD_TRAP_ERRCODE   17
BUILD_TRAP_NOERRCODE 18
BUILD_TRAP_NOERRCODE 19
BUILD_TRAP_NOERRCODE 20
BUILD_TRAP_ERRCODE   21
BUILD_TRAP_NOERRCODE 22
BUILD_TRAP_NOERRCODE 23
BUILD_TRAP_NOERRCODE 24
BUILD_TRAP_NOERRCODE 25
BUILD_TRAP_NOERRCODE 26
BUILD_TRAP_NOERRCODE 27
BUILD_TRAP_NOERRCODE 28
BUILD_TRAP_ERRCODE   29
BUILD_TRAP_ERRCODE   30
BUILD_TRAP_NOERRCODE 31

trap_common: 
    SAVE_ALL
    cld
    call trap_handle 
    RESTORE_ALL
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

.macro BUILD_IRQ num
irq\num: 
    push $\num
    jmp irq_common
.endm

irq_common: 
    cld
    call irq_handle
    add $4, %esp
    iret 

.set i, 0
.rept 16
    BUILD_IRQ %i
    .set i, i+1
.endr 

.macro insert_irq num
    .long irq\num
.endm

.align 4
irq_entry_table: 
.set i, 0
.rept 16
    insert_irq %i 
    .set i, i+1
.endr

.text
.global _start

_start:
    b _reset
    ldr pc, =_undirq

_undirq:
    .word handle_und_exception

_reset:
    // [0] disable watchdog
    ldr r0, =0x53000000
    mov r1, #0
    str r1, [r0]

    // [1] init sys clock
    ldr r0, =0x4C000000
    ldr r1, =0xffffffff
    str r1, [r0]

    ldr r0, =0x4C000014
    mov r1, #0x5
    str r1, [r0]

    mrc p15,0,r0,c1,c0,0
    orr r0,r0,#0xc0000000
    mcr p15,0,r0,c1,c0,0

    ldr r0, =0x4C000004
    ldr r1, =(0x5c << 12) | (1 << 4) | 1
    str r1, [r0]

    // [2] set stack for C function call ...
    mov r1, #0
    ldr r0, [r1]  // backup 0 addr to value
    str r1, [r1]  // [w] try write 0 addr
    ldr r2, [r1]  // read 0 addr
    cmp r1, r2   // [w] suc, nand boot. [w] fail nor. write == read, CPSR.Z == 1
    ldr sp, =0x40000000 + 0x1000 // if nor boot, using Internal SRAM for stack
    moveq sp, #4096
    streq r0, [r1]    

    // [3] init sdram
    bl mini2440_sdram_init

    // [4] relocation (copy operator)
    mov r1, #0;             // src_addr
    ldr r2, =_start         // dst_addr
    ldr r3, =_bss_beg

_copy:
    ldr r4, [r1]
    str r4, [r2]

    add r1, r1, #4          // modify src_addr
    add r2, r2, #4          // modify dst_addr

    cmp r2, r3
    ble _copy

    // [5] set bss zero
    mov r1, #0
    ldr r2, =_bss_beg
    ldr r3, =_end

_clr_bss:
    str r1, [r2]
    add r2, r2, #4
    cmp r2, r3
    ble _clr_bss

undirq_str:
    .string "the str defined in asm!!"

.align 4
    // [6] init uart
    bl init_uart0

    // [7.0]
    mrs r0, cpsr
    bl before_undirq_happend

    // [7.1] unddefined interrupt happened by blow instruction
    .word 0xdeadc0de

    ldr pc, =main
 
 _loop:
    b _loop

handle_und_exception:
    ldr sp, =0x34000000

    stmdb sp!, {r0-r12, lr}
    
    mrs r0, cpsr
    ldr r1, =undirq_str
    bl do_undefined_execption

    ldmia sp!, {r0-r12, pc}^

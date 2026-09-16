
.text
.global _start

_start:
    
    // [0] disable watchdog
    ldr r0, =0x53000000
    mov r1, #0
    str r1, [r0]

    // [1] init sys clock
    bl _init_sysclk

    // run main
    bl main
   
_init_sysclk:
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

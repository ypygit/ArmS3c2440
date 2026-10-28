.text
.global _entry

_entry:
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
    ldr r0, [r1] 
    str r1, [r1] 
    ldr r2, [r1] 
    cmp r1, r2   
    ldr sp, =0x40000000 + 0x1000  // assume nor boot, using Internal SRAM for stack
    moveq sp, #4096
    streq r0, [r1]    

    // [4] init sdram
    bl mini2440_sdram_init

    // [5] using mmu
    bl make_mmu_descriptors_table
    bl mmu_enable
    
    // [6] relocation (copy operator)
    bl copy_code_to_sdram 
    
    // [7] set bss zero
    bl clear_bss;

    // [8] run main in sdram
    ldr pc, =main

_loop:
    b _loop

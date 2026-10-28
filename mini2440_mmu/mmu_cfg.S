.text

.global mmu_enable

mmu_enable:
    // using CP15`C2 for seting page base addr
    mov r0, #0x32000000
	mcr p15, 0, r0, c2, c0, 0
  
    // using CP15`C3 set all domain 11, don`t check access level
	ldr r0, =0xffffffff
	mcr p15, 0, r0, c3, c0, 0
    
    // using CP15`C1 enable icache dcache mmu
	mrc p15, 0, r0, c1, c0, 0
	orr r0, r0, #(1<<12) 
    orr r0, r0, #(1<<2)
	orr r0, r0, #(1<<0)
	mcr p15, 0, r0, c1, c0, 0	
    
    mov pc, lr

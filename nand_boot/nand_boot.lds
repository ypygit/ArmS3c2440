SECTIONS
{
    . = 0x30000000;

    . = ALIGN(4);
    __code_beg = .;
    .text :
    {
        start.o(.text)
        *(.text)
    }

    . = ALIGN(4);
    .rodata :
    {
        *(.rodata)
    }

    . = ALIGN(4);
    .data : {*(.data)}

    . = ALIGN(4);
    __bss_beg = .;
    .bss : {*(.bss)}
    __end = .;
}

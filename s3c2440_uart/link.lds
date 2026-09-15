SECTIONS
{
    . = 0x30000000;

    . = ALIGN(4);
    .text : {
        start.o(.text)
        *(.text)
    }
}

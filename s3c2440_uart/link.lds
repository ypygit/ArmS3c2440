SECTIONS
{
    . = 0x00000000;

    . = ALIGN(4);
    .text : {
        start.o(.text)
        *(.text)
    }
}

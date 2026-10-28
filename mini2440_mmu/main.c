#include "hwuart.h"
#include "led.h"

unsigned int g_v = 1;
const char g_s = 'S';
char g_e = 'E';

void delay()
{
    volatile unsigned int i = 0;

    for (; i < 800000; ++i);
}

int main(void)
{
    int x = 0, y = 0;

    init_uart0();
    led2_init();

    __asm__(
        "add %0, %1, #0x1000"
        :"=r"(y)
        :"r"(x)
    );

    put_string("main run base mmu\r\n");
    put_string("gcc inline asm call value=");
    print_hex(y);
    put_string("\r\n");

    while (1) {
        put_c(g_s);
        put_string("\r\n");
        led2_switch(LED_ON);
        delay();
        print_hex(g_v++);
        put_string("\r\n");
        led2_switch(LED_OFF);
        put_c(g_e);
        put_string("\r\n");
        delay();
    }

    return 0;
}


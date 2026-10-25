#include "hwuart.h"
#include "led.h"

unsigned int g_v = 1;
const char g_s = 'S';
char g_e = 'E';
int g_bootFlag = 0; 

void delay()
{
    volatile unsigned int i = 0;

    for (; i < 800000; ++i);
}

int main(void)
{
    init_uart0();
    led1_init();

    put_string(g_bootFlag == 1 ? "from nand boot\r\n" : "from nor boot\r\n");
    put_string("main run in sdram\r\n");

    while (1) {
        put_c(g_s);
        put_string("\r\n");
        led1_switch(LED_ON);
        delay();
        print_hex(g_v++);
        put_string("\r\n");
        led1_switch(LED_OFF);
        put_c(g_e);
        put_string("\r\n");
        delay();
    }

    return 0;
}

#include "hwuart.h"
#include "nand.h"
#include "led.h"

void delay()
{
    volatile int i = 0;

    for (; i < 100000; ++i);
}

int main(void)
{
    init_uart0();
    led1_init();

    put_string("boot from nand\r\n");

    nand_flash_read_id();

    while (1) {
        led1_switch(LED_ON);
        delay();
        led1_switch(LED_OFF);
    }

    return 0;
}

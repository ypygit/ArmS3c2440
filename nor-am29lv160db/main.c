#include "hwuart.h"
#include "led.h"
#include "am29lv160db.h"

int main(void)
{
    int i = 0;

    init_uart0();
    led1_init();

    put_string("AM29LV160DB run\r\n");

    led1_switch(LED_ON);

    while (1) {
        i = get_c();
        
        if (i != 'N') {
            continue;
        }

        qry_am29lv160db_info();
    }

    return 0;
}

#include "led.h"
#include "mini2440friendly.h"

void led2_init(void)
{
    GPBCON |= 1 << 12;
}

void led2_switch(enum LED_ACTION action)
{
    switch (action) {
    case LED_ON:
        GPBDAT &= ~(1 << 6);
        break;
    case LED_OFF:
        GPBDAT |= (1 << 6);
        break;
    default:
        break;
    }
}

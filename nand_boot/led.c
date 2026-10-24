#include "led.h"
#include "s3c2440friend.h"

void led1_init(void)
{
    GPBCON |= 0x1 << 10;
}

void led1_switch(enum LED_ACTION action)
{
    switch (action) {
    case LED_ON:
        GPBDAT &= ~(1 << 5);
        break;
    case LED_OFF:
        GPBDAT |= (1 << 5);
        break;
    default:
        break;
    }
}

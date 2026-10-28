#ifndef _FRIDARM_MNI2440_LED_H
#define _FRIDARM_MNI2440_LED_H

enum LED_ACTION {
    LED_ON = 0,
    LED_OFF
};

void led2_init(void);

void led2_switch(enum LED_ACTION action);

#endif

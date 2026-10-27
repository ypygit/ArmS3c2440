// #include "mini2440friendly.h"

int main(void)
{
    int x = 0, y = 0;

    __asm__(
        "add %0, %1, #0x1000"
        :"=r"(y)
        :"r"(x)
    );

    return y;
}

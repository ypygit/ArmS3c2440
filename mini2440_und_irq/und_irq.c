#include "hwuart.h"

void before_undirq_happend(unsigned int state)
{
    put_string(__FUNCTION__);
    put_string(":\r\n");
    print_hex(state & 0x1f);
    put_string("\r\n");
}

void do_undefined_execption(unsigned int state, const char *str)
{
    while (*str) {
        put_c(*str++);
    }
 
    put_string("\r\n");
    print_hex(state & 0x1f);
    put_string("\r\n");
}

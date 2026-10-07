#ifndef _HWUART_H
#define _HWUART_H

#if defined(__cplusplus)
extern "C" {
#endif

void init_uart0(void);

void put_c(int c);

int get_c(void);

void put_string(const char *str);

void print_hex(unsigned int const v);

#if defined(__cplusplus)
}
#endif

#endif // _HWUART_H


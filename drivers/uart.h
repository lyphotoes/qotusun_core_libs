#ifndef UART_H_
#define UART_H_

#include "config.h"


void uart_init();
int uart_putchar(char c,FILE *unused);
#endif // UART_H_

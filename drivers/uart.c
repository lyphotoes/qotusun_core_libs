//#include "includes/drivers/uart.h"
/*
 * Note [6]
 * Send character c down the UART Tx, wait until tx holding register
 * is empty.
 */

 //#include "common.h"
#include "config.h"
int uart_putchar(char c, FILE *unused)
{

  if (c == '\n')
    uart_putchar('\r', 0);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

void uart_init(void)
{
    UBRR0 = (F_CPU / (16 * 9600UL)) - 1; /* 9600 Bd */

    UCSR0B = _BV(TXEN0);		/* tx enable */
}

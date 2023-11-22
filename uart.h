#ifndef __UART_H__
#define __UART_H__

#include "config.h"

void uart1_init(void);

void uart1_send_array(u8 *p, u8 len);

u8 uart1_len(void);
	
void uart1_reset_len(void);

void print(char *p, ...);

u8* uart1_get();
#endif // __UART_H__
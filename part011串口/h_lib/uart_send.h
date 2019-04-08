#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
	

void init_uart();
void uart_sendbyte(uchar value);
void uart_sendstring(uchar *s);
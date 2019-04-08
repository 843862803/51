#include <uart_send.h>


void init_uart()
{
	SCON = 0x50;
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	EA = 1;
	ES = 1;
	TR1 = 1;
}

void uart_sendbyte(uchar value)
{
	SBUF = value;
	while(!TI);
	TI = 0;
}

void uart_sendstring(uchar *s)
{
	while(*s != '\0')
	{
		uart_sendbyte(*s);
		s++;
	}
}
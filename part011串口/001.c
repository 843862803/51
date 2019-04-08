#include <reg51.h>
#include <delay.h>
#include <uart_send.h>
#include <led.h>
#define uchar unsigned char
#define uint unsigned int

sbit led4 = P2^3;

uint rec_dat = 'b';
uchar receive[20] = {0};
uchar x = 0;

/*void delayms(uint t)		//延时函数ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110;x>0;x--)		//延时一毫秒
		{
		}
	}
}*/

/*void init_uart()
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
}*/

void main()
{
	led8();
	P2 = 0xff;
	init_uart();
	while(1)
	{
	}
	/*while(1)
	{
		if(x==1)
		{
			uchar i = 0x01;
			//uart_sendbyte(rec_dat);
			//delayms(1000);
			i<<=rec_dat;
			P2 = i;
			P2 = ~P2;
			x = 0;
		}

	}*/
}

void Uart_Interrupt () interrupt 4		//中断接收数据
{
	uchar i = 0x01;
	RI = 0;
	rec_dat = SBUF;
	rec_dat = (i<<rec_dat);
	rec_dat^=0xff;		//取反  
	P2 = rec_dat;
}
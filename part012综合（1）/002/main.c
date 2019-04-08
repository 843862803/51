#include <reg52.h>
#include <string.h>
#include <esp8266.h>
#include <lcd1602.h>
#include <delay.h>
#define uchar unsigned char
#define uint unsigned int

sbit led1 = P2^0;
bit Usart_AT_flage;
uchar receive[30] = {0};
uchar count = 0,c =0;
uchar num,num1,i;

uchar code START[]="Starting up...";		//14
uchar code OK[]="  OK!";		//5
uchar code REC[]="Received:";		//9


void main()		//主函数
{
	init_1602();
	write_com(0x80);
	for(num=0;num<14;num++)
	{
		write_data(START[num]);
		delay(1);
	}
	Init_Uart();
	Set_AP();
	//REN = 0;
	write_com(0x80+0x40);
	for(num=0;num<5;num++)
	{
		write_data(OK[num]);
		delay(1);
	}
	delayms(1500);
	//REN = 1;
	while(1)
	{
		if(Usart_AT_flage == 1)
		{
			//REN = 0;
			init_1602();		//进入显示接收数据页面。
			write_com(0x80);
			for(num=0;num<9;num++)
			{
				write_data(REC[num]);
				delay(1);
			}
			if(c<21 && c !=0)
			{
				for(i=c-1;i<30;i++)
				{
					receive[i] = ' ';
				}
				write_com(0x80+0x40);
				for(num=0;num<16;num++)
				{
					num1 = num + 9;
					write_data(receive[num1]);
					delay(1);
				}
				c = 0;
				Usart_AT_flage = 0;
			}
			if(c>21 && c != 0)
			{
				for(i=c-1;i<30;i++)
				{
					receive[i] = ' ';
				}
				write_com(0x80+0x40);
				for(num=0;num<16;num++)
				{
					num1 = num + 10;
					write_data(receive[num1]);
					delay(1);
				}
				c = 0;
				Usart_AT_flage = 0;
			}
		}
		//while(Usart_AT_flage ==0);
	}
}

void Uart_Interrupt () interrupt 4		//中断接收数据
{
//	for(i=0;i<30;i++)
//	{
//		receive[i] = ' ';
//	}
	if(RI)
	{
		RI = 0;
		receive[count] = SBUF;
		count++;
		if(receive[count-2]=='\r' && receive[count-1]=='\n' && count >= 2)
		{
			c = count;
			count = 0;
			Usart_AT_flage = 1;
		}
		else if(count>30)
		{
			c = 30;
			count = 0;
		}
	}
}
#include <delay.h>

void delayms(uint t)		//延时函数 ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110;x>0;x--)		//延时一毫秒
		{
		}
	}
}

void delay(uint t)		//延时函数 0.5ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110/2;x>0;x--)		//延时一毫秒
		{
		}
	}
}
#include <delay.h>

void delayms(uint t)		//��ʱ���� ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110;x>0;x--)		//��ʱһ����
		{
		}
	}
}

void delay(uint t)		//��ʱ���� 0.5ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110/2;x>0;x--)		//��ʱһ����
		{
		}
	}
}
#include <reg52.h>
#include <delay.h>
#include <display.h>
#define uchar unsigned char
#define uint unsigned int

void keyscan();
void delayms(uint t);
void display(uint dis_num);

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

void keyscan()
{
	if(k1==0)
	{
		delayms(1);
		if(k1==0)
		{
			num++;
			while(!k1)
			{
				display(num);
			}
		}
	}
	if(k2==0)
	{
		delayms(1);
		if(k2==0)
		{
			if(num==0)
			{
				while(!k2)
				{
					display(num);
				}
				goto dot1;
			}
			num--;
			while(!k2)
			{
				display(num);
			}
		}
	}
	dot1:
	if(k3==0)
	{
		delayms(1);
		if(k3==0)
		{
			num=0;
		}
	}
}

void main()
{
	num = 0;
	while(1)
	{
		keyscan();
		display(num);
	}
}
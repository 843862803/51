#include <reg52.h>
#include <delay.h>
#include <keyscan.h>
#define uchar unsigned char
#define uint unsigned int



sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

void keyscan()
{
	if(key_1==0)
	{
		if(k1==0)
		{
			delayms(1);
			if(k1==0)
			{
				key = 1;
			}
		}
		if(k2==0)
		{
			delayms(1);
			if(k2==0)
			{
				key = 2;
			}
		}
		if(k3==0)
		{
			delayms(1);
			if(k3==0)
			{
				key = 3;
			}
		}
		if(k4==0)
		{
			delayms(1);
			if(k4==0)
			{
				key = 4;
			}
		}
		key_1 = 1;
	}
}
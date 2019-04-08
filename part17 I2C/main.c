#include <reg52.h>
#include "I2C.h"
#include "display.h"
#define uchar unsigned char
#define uint unsigned int

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

uchar num = 0;
									
void delay(uint i);     //延时u秒
void Keypros();         //按键函数

									
void main()  //主函数
{
	while(1)
	{
		Keypros();
		display(num);
	}
}


void delay(uint i)
{
	while(i--);
}

void Keypros() //按键函数
{
	if(k1 == 0)
	{
		delay(100);
		if(k1 == 0)
		{
			At24c02_Write(1,num);
		}
		while(!k1)
		{
			display(num);
		}
	}
	if(k2 == 0)
	{
		delay(100);
		if(k2 == 0)
		{
			num = At24c02_Read(1);
		}
		while(!k2)
		{
			display(num);
		}
	}
	if(k3 == 0)
	{
		delay(100);
		if(k3 == 0)
		{
			num++;
			if(num>255)
			{
				num = 0;
			}
		}
		while(!k3)
		{
			display(num);
		}
	}
	if(k4 == 0)
	{
		delay(100);
		if(k4 == 0)
		{
			num = 0;
		}
		while(!k4)
		{
			display(num);
		}
	}
}

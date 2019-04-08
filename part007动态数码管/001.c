#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;
sbit lsa = P2^2;
sbit lsb = P2^3;
sbit lsc = P2^4;

uchar code txt1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
									0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x0};

uint num1=0;
uchar y1,y2,y3,y4;
uchar i;
									
void delayms(uint xms)
{
	uchar x1;
	for(xms;xms>0;xms--)
		for(x1=20;x1>0;x1--);
}

void display(uint num)
{
	y1 = num/1000;
	y2 = (num%1000)/100;
	y3 = ((num%1000)%100)/10;
	y4 = ((num%1000)%100)%10;
	
	for(i=0;i<4;i++)
	{
		switch(i)
		{
			case(0):
				//P0 = txt1[17];
				lsa=0;lsb=0;lsc=0;
				P0 = txt1[y4];
				break;
			case(1):
				//P0 = txt1[17];
				lsa=1;lsb=0;lsc=0;
				P0 = txt1[y3];
				break;
			case(2):
				//P0 = txt1[17];
				lsa=0;lsb=1;lsc=0;
				P0 = txt1[y2];
				break;
			case(3):
				//P0 = txt1[17];
				lsa=1;lsb=1;lsc=0;
				P0 = txt1[y1];
				break;
			/*case(4):
				lsa=0;lsb=0;lsc=1;break;
			case(5):
				lsa=1;lsb=0;lsc=1;break;
			case(6):
				lsa=0;lsb=1;lsc=1;break;
			case(7):
				lsa=1;lsb=1;lsc=1;break;*/
		}
		delayms(20);
	}
}

void keyscan()
{
	if(k1==0)
	{
		delayms(1);
		if(k1==0)
		{
			num1++;
			while(!k1)
			{
				display(num1);
			}
		}
	}
	if(k2==0)
	{
		delayms(1);
		if(k2==0)
		{
			if(num1==0)
			{
				while(!k2)
				{
					display(num1);
				}
				goto dot1;
			}
			num1--;
			while(!k2)
			{
				display(num1);
			}
		}
	}
	dot1:
	if(k3==0)
	{
		delayms(1);
		if(k3==0)
		{
			num1=0;
		}
	}
}

void main()
{
	while(1)
	{
		keyscan();
		display(num1);
	}
}
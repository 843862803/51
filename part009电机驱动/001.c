#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit in1 = P1^0;
sbit in2 = P1^1;
sbit ENA = P1^2;

void delay(uint z);
void delay_us(uint aa);


void delay(uint z)
{
	uchar y;
	for(z;z>0;z--)
		for(y=110;y>0;y--);
}

void delay_us(uint aa)
{
	while(aa--);
}

/*void main()
{
	uint cycle=0,T=1024;
	ENA = 1;
	in1 = 0;
	in2 = 1;
	while(cycle != T)
		{
			ENA = 1;
			delay_us(cycle++);
			ENA = 0;
			delay_us(T-cycle);
		}
		in1 = 1;
		in2 = 1;
}*/

void main()
{
	while(1)
	{
		uint i;
		uint cycle=0,T=1024;
		ENA = 1;
		in1 = 1;
		in2 = 0;
		
		for(i=0;i<400;i++)
		{
			delay(10);
			ENA = ~ENA;
		}
		
		in1 = 0;
		in2 = 1;
		
		for(i=0;i<400;i++)
		{
			delay(10);
			ENA = ~ENA;
		}
		
		in1 = 1;
		in2 = 0;
		cycle = 0;
		while(cycle != T)
		{
			ENA = 1;
			delay_us(cycle++);
			ENA = 0;
			delay_us(T-cycle);
		}
		while(cycle != 0)
		{
			ENA = 1;
			delay_us(cycle--);
			ENA = 0;
			delay_us(T-cycle);
		}
		in1 = 0;
		in2 = 1;
		while(cycle != T)
		{
			ENA = 1;
			delay_us(cycle++);
			ENA = 0;
			delay_us(T-cycle);
		}
		in1 = 1;
		in2 = 1;
		while(cycle != 0)
		{
			ENA = 1;
			delay_us(cycle--);
			ENA = 0;
			delay_us(T-cycle);
		}
	}
}

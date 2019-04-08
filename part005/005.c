#include <reg52.h>
#include <intrins.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define led P2

//sbit k1 = P3^1;
//sbit k2 = P3^0;
//sbit moto = P1^0;

ucrha code smgduan[9] = {0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};

//void delay(uint t)
//{
//	while(t--);
//}

void delay(uint t)
{
	uint a,j;
	for(a=0;a<t;a++)
		for(j=110;j>0;j--);
}

void display()
{
		char i;
		for(i=0;i<9;i++)
		{
				led = smgduan[i];
				delay(300+100*i);
				led = smgduan[0];
				delay(300);
		}
		for(i=7;i>0;i--)
		{
				led = smgduan[i];
				delay(300+100*i);
				led = smgduan[0];
				delay(300);
		}
	
}

void main()
{
	while(1)
	{
		display();
	}
}

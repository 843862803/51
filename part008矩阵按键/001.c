#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit lsa = P2^2;
sbit lsb = P2^3;
sbit lsc = P2^4;

uchar code txt1[]={0x3f,0x06,0x5b,0x4f,0x66,
0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,
0x79,0x71,0x0};

uchar key = 0;

void delay(uint x);
void display(uchar num);
void martrixkeyscan();


void delay(uint x)
{
	uchar x2;
	for(x;x>0;x--)
		for(x2=20;x2>0;x2--);
}

void display(uchar num)
{
	/*lsa=0;lsb=0;lsc=0;
	P0 = txt1[num];
	delay(20);*/
	uchar y1,y2,i;
	y1 = num/10;
	y2 = num%10;
	
	for(i=0;i<2;i++)
	{
		switch(i)
		{
			case(0):
				P0 = txt1[y2];
				lsa=0;lsb=0;lsc=0;
				//P0 = txt1[y2];
				break;
			case(1):
				P0 = txt1[y1];
				lsa=1;lsb=0;lsc=0;
				//P0 = txt1[y1];
				break;
		}
		delay(20);
		P0 = txt1[16];
	}
}


void martrixkeyscan()
{
	uchar x1,x2;
	P1 = 0x7f;
	x1 = P1;
	x2 = x1&0x7f;
	if(x2 != 0x7f)
	{
		switch(x1)
		{
			case 0x77:
				key = 1;
				break;
			case 0x7b:
				key = 2;
					break;
			case 0x7d:
				key = 3;
				break;
			case 0x7e:
				key = 4;
				break;
		}
		while(x1 != 0x7f)
		{
			P1 = 0x7f;
			x1 = P1;
			display(key);
		}
	}
	
	P1 = 0xbf;
	x1 = P1;
	x2 = x1&0xbf;
	if(x2 != 0xbf)
	{
		switch(x1)
		{
			case 0xb7:
				key = 5;
				break;
			case 0xbb:
				key = 6;
					break;
			case 0xbd:
				key = 7;
				break;
			case 0xbe:
				key = 8;
				break;
		}
		while(x1 != 0xbf)
		{
			P1 = 0xbf;
			x1 = P1;
			display(key);
		}
	}
	
	P1 = 0xdf;
	x1 = P1;
	x2 = x1&0xdf;
	if(x2 != 0xdf)
	{
		switch(x1)
		{
			case 0xd7:
				key = 9;
				break;
			case 0xdb:
				key = 10;
					break;
			case 0xdd:
				key = 11;
				break;
			case 0xde:
				key = 12;
				break;
		}
		while(x1 != 0xdf)
		{
			P1 = 0xdf;
			x1 = P1;
			display(key);
		}
	}
	
	P1 = 0xef;
	x1 = P1;
	x2 = x1&0xef;
	if(x2 != 0xef)
	{
		switch(x1)
		{
			case 0xe7:
				key = 13;
				break;
			case 0xeb:
				key = 14;
					break;
			case 0xed:
				key = 15;
				break;
			case 0xee:
				key = 16;
				break;
		}
		while(x1 != 0xef)
		{
			P1 = 0xef;
			x1 = P1;
			display(key);
		}
	}
}	

void main()
{
	while(1)
	{
		display(key);
		martrixkeyscan();
	}
}
									
									
									


									
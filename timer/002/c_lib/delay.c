#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

void delay(uint t)
{
	uchar a = 0;
	for(t;t>0;t--)
	{
		for(a=120/2;a>0;a--)
		{
		}
	}
}

//void delay(uint t)
//{
//	uchar a = 0;
//	for(t;t>0;t--)
//	{
//		for(a=10;a>0;a--)
//		{
//		}
//	}
//}
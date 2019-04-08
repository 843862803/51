#include "display.h"

sbit lsa = P2^2;
sbit lsb = P2^3;
sbit lsc = P2^4;

uchar code txt1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
									0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x0};

void dis_delayms(uint t)
{
	uchar a = 0;
	for(t;t>0;t--)
	{
		for(a=120;a>0;a--)
		{
		}
	}
}
									
void display(uint dis_num)
{
	uchar y1,y2,y3,y4,i;

	y1 = dis_num/1000;
	y2 = (dis_num%1000)/100;
	y3 = ((dis_num%1000)%100)/10;
	y4 = ((dis_num%1000)%100)%10;
	
	for(i=0;i<4;i++)
	{
		switch(i)
		{
			case(0):
				P0 = 0;
				lsa=0;lsb=0;lsc=0;
				P0 = txt1[y4];
				break;
			case(1):
				P0 = 0;
				lsa=1;lsb=0;lsc=0;
				P0 = txt1[y3];
				break;
			case(2):
				P0 = 0;
				lsa=0;lsb=1;lsc=0;
				P0 = txt1[y2];
				break;
			case(3):
				P0 = 0;
				lsa=1;lsb=1;lsc=0;
				P0 = txt1[y1];
				break;
		}
		dis_delayms(1);
	}
}

//void display8(uint dis_num)
//{
//	uchar y1,y2,y3,y4,y5,y6,y7,y8,i;
//	
//	y1 = dis_num/1000;
//	y2 = (dis_num%1000)/100;
//	y3 = ((dis_num%1000)%100)/10;
//	y4 = ((dis_num%1000)%100)%10;
//	
//	for(i=0;i<4;i++)
//	{
//		switch(i)
//		{
//			case(0):
//				lsa=0;lsb=0;lsc=0;
//				P0 = txt1[y4];
//				break;
//			caes(1):
//				lsa=1;lsb=0;lsc=0;
//				P0 = txt1[y3];
//				break;
//			case(2):
//				lsa=0;lsb=1;lsc=0;
//				P0 = txt1[y2];
//				break;
//			case(3):
//				lsa=1;lsb=1;lsc=0;
//				P0 = txt1[y1];
//				break;
//			case(4):
//				lsa=0;lsb=0;lsc=1;
//				P0 = txt1[y8];
//				break;
//			case(5):
//				lsa=1;lsb=0;lsc=1;
//				P0 = txt1[y7];
//				break;
//			case(6):
//				lsa=0;lsb=1;lsc=1;
//				P0 = txt1[y6];
//				break;
//			case(7):
//				lsa=1;lsb=1;lsc=1;
//				P0 = txt1[y5];
//				break;
//		}
//		delayms(20);
//	}
//}
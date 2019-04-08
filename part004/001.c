#include <reg52.h>
#include<intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

#define led P2	

sbit k1=P3^1;
//sbit k2=P3^0;
sbit moto=P1^0;	

void delay(u16 i)
{
	while(i--);	
}


void keypros()
{
		u8 l;
		if(k1==0)			 //开始
		{
			while(!k1);
			moto=1;
			led=0xfe;
			delay(20000);
			while(1)
			{	
				for(l=0;l<7;l++)	 //将led左移一位
				{
					led=_crol_(led,1);
					delay(10000);
					if(k1==0)
					{
						delay(500);
						if(k1==0)
						{
							delay(15000);
							goto dot1;
						}
					}
					delay(10000);
					if(k1==0)
					{
						delay(500);
						if(k1==0)
					{
						delay(15000);
						goto dot1;
					}
					}
				}
				for(l=0;l<7;l++)	//将led右移一位
					{
					led=_cror_(led,1);
					delay(10000);
					if(k1==0)
					{
					delay(500);
					if(k1==0)
					{
					delay(15000);
					goto dot1;
					}
					}
					delay(10000);
					if(k1==0)
					{
					delay(500);
					if(k1==0)
					{
					delay(15000);
					goto dot1;
					}
					}
					}
			}
		}
		
		dot1: moto=0;
		led=0xff;
		delay(5000);
}

void main()
{
	moto=0;
	while(1)
	{
		keypros();
	}	
}
#include "reg52.h"
#include<intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

#define led P2	

sbit k1=P3^1;
sbit k2=P3^0;
sbit moto=P1^0;	

//sbit beep=P1^5;

void delay(u16 i)
	{
		while(i--);	
	}


void keypros()
{
		u8 l;
		if(k1==0)			 //��ʼ
		{
			delay(1000);
			if(k1==0)
				{
					moto=1;
					led=0xfe;
					delay(20000);
					while(1)
						{	
							for(l=0;l<7;l++)	 //��led����һλ
							{
								led=_crol_(led,1);
								delay(10000);
								if(k2==0)
								{
								delay(500);
								if(k2==0)
								{
								break;
								}
								}
								delay(10000);
								if(k2==0)
								{
								delay(500);
								if(k2==0)
								{
								break;
								}
								}
							}
							if(k2==0)
							{
							delay(500);
							if(k2==0)
							{
							break;
							}
							}
							for(l=0;l<7;l++)	//��led����һλ
								{
								led=_cror_(led,1);
								delay(10000);
								if(k2==0)
								{
								delay(500);
								if(k2==0)
								{
								break;
								}
								}
								delay(10000);
								if(k2==0)
								{
								delay(500);
								if(k2==0)
								{
								break;
								}
								}
								}
							if(k2==00)
							{
							delay(500);
							if(k2==0)
							{
							break;
							}
							}
						}
				}
			while(!k1);
		}
		if(k2==0)			  //ֹͣ
			{
			delay(500);
			if(k2==0)
				{
				moto=0;
				led=0xff;
				}
			while(!k2);
			}
}

void main()
{
	moto=0;
	while(1)
	{
		keypros();
		}	
}
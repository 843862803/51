#include "delay.h"

void delay(uint t)   //11.0592MHZ Îó²î -0.00000000024us
{
	while(t--)
	{
			unsigned char a,b,c;
			for(c=95;c>0;c--)
					for(b=26;b>0;b--)
							for(a=185;a>0;a--);
	}
}

void delayms(uint t)   //11.0592MHZ Îó²î -0.651041666667us
{
	while(t--)
	{
			unsigned char a,b;
			for(b=4;b>0;b--)
					for(a=113;a>0;a--);
	}
}

void delay10us(uint t)   //11.0592MHZ Îó²î -0.234375us
{
	while(t--)
	{
			unsigned char a;
			for(a=2;a>0;a--);
	}
}
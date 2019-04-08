#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int


sbit  led0 = P2^7;
sbit  led1 = P2^6;
sbit  led2 = P2^5;
sbit  led3 = P2^4;
sbit  led4 = P2^3;
sbit  led5 = P2^2;
sbit  led6 = P2^1;
sbit  led7 = P2^0;

int x;
void delayms(x)
{
	int z;
	for(x;x>0;x--)
	{
		for(z=124;z>0;z--)
		{
		}
	}
 }

void main()
{
	uchar i;
	led7 = 0;
	while(1)
	{
	for(i=0;i<7;i++)
	{
		P2=_crol_(P2,1);
		delayms(50);

	}
	for(i=0;i<7;i++)
	{
		P2=_cror_(P2,1);
		delayms(50);
	}
	}
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

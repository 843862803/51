#include <reg51.h>
#include <delay.h>
	
sbit led = P2^0;
sbit led4 = P2^3;

void main ()
{
	led = 0;
	while(1)
	{
		led = 0;
		delayms(500);
		led4 = ~led4;
	}
}
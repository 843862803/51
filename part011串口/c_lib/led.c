#include <delay.h>
#include <led.h>

void led8()
{
	uchar i = 0;
	P2 = 0xfe;
	delayms(300);
	for(i=0;i<7;i++)
	{
		P2<<=1;
		delayms(300);
	}
}
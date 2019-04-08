#include <reg52.h>
#define unit unsigned int
sbit led1 = P2^0;
unit i,j;
void main()
{
	while(1)
	{
		led1 = 0;
		for(i = 300;i > 0;i--)
			for(j = 110;j > 0;j--);
		led1 = 1;
		for(i = 300;i > 0;i--)
			for(j = 110;j > 0;j--);
	}
}
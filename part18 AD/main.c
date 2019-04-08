#include <reg52.h>
#include <display.h>
#include <XPT2046.h>

void main()
{
	unsigned int temp;
	while(1)
	{
		temp = SPI_AD_Read(0x94);
		display(temp);
	}
}
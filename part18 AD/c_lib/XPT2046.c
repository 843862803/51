#include "XPT2046.h"

void SPI_Write(uchar dat) //写入数据
{
	uchar i;
	CLK = 0;
	for(i=0;i<8;i++)
	{
		DIN = dat>>7;
		dat <<= 1;
		CLK = 0;
		CLK = 1;
	}
}

uint SPI_Read() //读取数据
{
	uchar i;
	uint dat = 0;
	CLK = 0;
	for(i=0;i<12;i++)
	{
		dat <<= 1;
		CLK = 1;
		CLK = 0;
		dat |= DOUT;
	}
	return dat;
}

uint SPI_AD_Read(uchar cmd) //AD转换函数
{
	uchar i;
	uint AD_Value;
	CS = 0;
	SPI_Write(cmd);
	for(i=0;i<6;i++);
	AD_Value = SPI_Read();
	CS = 1;
	return AD_Value;
	
}

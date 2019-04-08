#include <lcd1602.h>
#define uchar unsigned char
#define uint unsigned int
	
void init_1602();
void write_com(uchar com);
void write_data(uchar date);

sbit lcden = P2^7;
sbit lcdrs = P2^6;
sbit lcdrw = P2^5;

void init_1602()
{
	lcdrw=0;
	lcden = 0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

void write_com(uchar com)
{
	lcdrs = 0;
	P0 = com;
	delay(1);
	lcden = 1;
	delay(1);
	lcden = 0;
}

void write_data(uchar date)
{
	lcdrs = 1;
	P0 = date;
	delay(1);
	lcden = 1;
	delay(1);
	lcden = 0;
}
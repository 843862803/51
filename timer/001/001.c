#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit lcden = P2^7;
sbit lcdrs = P2^6;
sbit lcdrw = P2^5;
sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;
sbit k5 = P3^4;

uchar code txt1[]="1. Timer Mode";
uchar code txt2[]="2. Counting Mode";
uchar code txt3[]="Timing...";
uchar code txt4[]="Counting...";
uchar code txt5[]="0000";
uchar code txt6[]="0123456789";

uchar  num,num1,num2;
uchar x1,x2,x3,x4;

void delay(uint z)
{
	uint x;
	for(z;z>0;z--)
		for(x=123;x>0;x--);
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

void init()
{
	lcden = 0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

void main()
{
	lcdrw=0;
	init();
	write_com(0x80);
	for(num=0;num<13;num++)
	{
		write_data(txt1[num]);
		delay(2);
	}
	write_com(0x80+0x40);
	for(num=0;num<16;num++)
	{
		write_data(txt2[num]);
		delay(2);
	}
	while(k1&k2);
	if(k1==0)
	{
		dot3:
		x1=x2=x3=x4=num1=num2=0;
		while(!k1);
		init();
		write_com(0x80);
		for(num=0;num<9;num++)
		{
			write_data(txt3[num]);
			delay(2);
		}
		write_com(0x80+0x40);
		for(num=0;num<4;num++)
		{
			write_data(txt5[num]);
			delay(2);
		}
		while(k1);
		if(k1==0)
		{
			TMOD=0X01;
			TH0=60;
			TL0=176;
			EA=1;
			ET0=1;
			TR0=1;
			while(1)
			{
				dot2:
				init();
				write_com(0x80);
				for(num=0;num<9;num++)
				{
					write_data(txt3[num]);
					delay(1);
				}
				write_com(0x80+0x40);
				write_data(txt6[x1]);
				delay(1);
				write_data(txt6[x2]);
				delay(1);
				write_data(txt6[x3]);
				delay(1);
				write_data(txt6[x4]);
				delay(1);
				delay(20);
			}
			dot1:
			while(1)
			{
				if(k1==0)
				{
					TR0=1;
					goto dot2;
				}
				if(k3==0)
				{
					goto dot3;
				}
			}
		}
	}
	if(k2==0)
	{
		while(!k2);
		init();
		for(num=0;num<11;num++)
		{
			write_data(txt4[num]);
			delay(2);
		}
		while(1);
	}
}

void T0_time() interrupt 1
{
		 TH0=60;
		 TL0=176;
		 num1++;
		 if(num1==20)
		 {
				num1=0;
				num2++;
				x1=num2/1000;
				x2=(num2%1000)/100;
				x3=((num2%1000)%100)/10;
				x4=((num2%1000)%100)%10;
		 }
		 if(num2++>9999)
		 {
			num2=0;
		 }
		 if(k2==0)
		 {
				TR0=0;
				goto dot1;
		 }
}


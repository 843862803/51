#include <reg52.h>
#include <delay.h>
#include <lcd1602.h>
#define uchar unsigned char
#define uint unsigned int

//sbit lcden = P2^7;
//sbit lcdrs = P2^6;
//sbit lcdrw = P2^5;
sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

uchar code txt1[]="1. Timer Mode";    //13
uchar code txt2[]="2. Counting Mode"; //16
uchar code txt3[]="Timing...";        //9
uchar code txt4[]="Counting...";      //11
uchar code txt5[]="0000";             //4
uchar code txt6[]="0123456789";       //10
uchar code txt7[]="   Error";         //8

uchar  num,num1;
uchar x1,x2,x3,x4;
uint num2;

void delay(uint z);

void write_com(uchar com);

void write_data(uchar date);

//char k()
//{
//		if(k1==0)
//			return 1;
//		else if(k2==0)
//			return 2;
//		else if(k3==0)
//			return 3;
//		else if(k4==0)
//			return 4;
//		else return 0;
//}

void main()
{
	init();
	write_com(0x80);
	for(num=0;num<13;num++)
	{
		write_data(txt1[num]);
		delay(1);
	}
	write_com(0x80+0x40);
	for(num=0;num<16;num++)
	{
		write_data(txt2[num]);
		delay(1);
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
			delay(1);
		}
		write_com(0x80+0x40);
		for(num=0;num<4;num++)
		{
			write_data(txt5[num]);
			delay(1);
		}
		while(k1&k2);
		if(k2==0)
		{
			goto dot4;
		}
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
				delay(50);
				if(k3==0)
				{
					TR0=0;
					goto dot1;
				}
				if(k4==0)
				{
					TR0=0;
					goto dot3;
				}
				if(k2==0)
				{
					TR0=0;
					goto dot4;
				}
			}
			dot1:
			while(1)
			{
				if(k1==0)
				{
					TR0=1;
					goto dot2;
				}
				if(k4==0)
				{
					goto dot3;
				}
				if(k2==0)
				{
					goto dot4;
				}
			}
		}
	}
	if(k2==0)
	{
		dot4:
		x1=x2=x3=x4=num2=0;
		while(!k2);
		dot5:
		x1=num2/1000;
		x2=(num2%1000)/100;
		x3=((num2%1000)%100)/10;
		x4=((num2%1000)%100)%10;
		init();
		write_com(0x80);
		for(num=0;num<11;num++)
		{
			write_data(txt4[num]);
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
		while(1)
		{
			if(k3==0)
			{
				while(!k3);
				num2++;
				goto dot5;
			}
			if(k4==0)
			{
				while(!k4);
				if(num2==0)
				{
						init();
						write_com(0x80);
						for(num=0;num<11;num++)
						{
							write_data(txt4[num]);
							delay(1);
						}
						write_com(0x80+0x40);
						for(num=0;num<8;num++)
						{
							write_data(txt7[num]);
							delay(1);
						}
						delay(2000);
						goto dot4;
				}
				num2--;
				goto dot5;
			}
			if(k2==0)
			{
				goto dot4;
			}
			if(k1==0)
			{
				goto dot3;
			}
		}
	}
}

void T0_time() interrupt 1
{
		 TH0=76;
		 TL0=0;
		 num1++;
		 if(num1>=20)
		 {
			 num1=0;
			 num2++;
			 x1=num2/1000;
			 x2=(num2%1000)/100;
			 x3=((num2%1000)%100)/10;
			 x4=((num2%1000)%100)%10;
		 }
		 if(num2>9999)
		 {
		  num2=0;
		 }
}


/****************************************
*     ��·�����������ļ�����            *
*****************************************/

#include <reg52.h>
#include <delay.h>          //��ʱģ��
#include <lcd1602.h>        //LCD1602��ʾģ��
#include <martrixkeyscan.h> //�������ɨ��ģ��
#include <number.h>         //����ʱ����ģ�飨LCD1602��
#define uchar unsigned char
#define uint unsigned int

uchar z,num,number_s_1,number_s_2;
uchar code txt1[]="0123456789";   //10

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

void main()
{
	
}

char k()
{
		if(k1==0)
			return 1;
		else if(k2==0)
			return 2;
		else if(k3==0)
			return 3;
		else if(k4==0)
			return 4;
		else return 0;
}

//void main()
//{
//	while(1)
//	{
//		z = number();
//		number_s_1 = z/10;
//		number_s_2 = z%10;
//		init_1602();
//		write_com(0x80);
//		write_data(txt1[number_s_1]);
//		delay(1);
//		write_data(txt1[number_s_2]);
//		while(k1);
//	}
//}
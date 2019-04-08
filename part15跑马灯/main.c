#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

uint de_t1,de_n1 = 0,de_n2 = 1; //��ʱ����ȫ�ֱ���

void led1(int n1);      //����һ����
void led2(int n2);      //���ܶ�����
void led3(int n3);      //����������
void delay_us(uint aa); //��ʱ���� aa΢��
void delay(int a);      //��ʱ���� 50a����

void main ()            //������
{
	while(1)
	{
		led1(2);
		led2(2);
		led3(1);
	}
}


/***********����һ����*************/
void led1(int n1)
{
	while(n1--)
	{
		uint i,num1 = 0x1ff;
		for(i=0;i<8;i++)
		{
			num1 = (num1-1)/2;
			P2 = num1;
			delay(4);
		}
		P2 = 0x00;
		delay(4);
		P2 = 0xff;
	}
}

/***********���ܶ�����*************/
void led2(int n2)
{
	while(n2--)
	{
		uint code txt1[] = {0xf,0x87,0xc3,0xe1,0xf0};
		uint i = 0;
		for(i;i<5;i++)
		{
			P2 = txt1[i];
			delay(4); //��ʱ200����
		}
		P2 = 0xff;
		//delay(4);
	}
}

/***********����������*************/
void led3(int n3)
{
	while(n3--)
	{
		uint led3_1=0,T=2000; //T�ɿ���Ƶ��
		while(led3_1 != T)
		{
			P2 = 0x00;
			delay_us(led3_1 = led3_1+16);
			P2 = 0xff;
			delay_us(T-led3_1);
		}
		while(led3_1 != 0)
		{
			P2 = 0x00;
			delay_us(led3_1 = led3_1-16);
			P2 = 0xff;
			delay_us(T-led3_1);
		}
	}
}


/**************��ʱ����************/
void delay_us(uint aa) //��ʱ1΢��
{
	while(aa--);
}

void delay(int a) //��ʱʱ��Ϊ50a ms
{
	de_t1 = a;
	TMOD = 0X01;    //���ö�ʱ��0Ϊ������ʽ1
	TH0 = (65536-45872)/256;
	TL0 = (65536-45872)%256;
	EA=1;  //�����ж�
	ET0=1; //������ʱ��0�ж�
	TR0=1; //������ʱ��0
	while(de_n2);
	de_n2 = 1;
}

void T0_time() interrupt 1 //��ʱ���жϺ���
{
		 TH0=(65536-45872)/256;
		 TL0=(65536-45872)%256;
		 de_n1++;
		 if(de_n1>=de_t1)
		 {
			 de_n1 = 0;
			 de_n2 = 0;
		 }
}
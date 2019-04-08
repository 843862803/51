#include <reg52.h>
#include "delay.h"
#include "display.h"
#include "key.h"
#include "XPT2046.h"
#define uchar unsigned char
#define uint unsigned int
	
sbit in1 = P1^0; //�����������˿�
sbit in2 = P1^1;
sbit in3 = P1^2;
sbit in4 = P1^3;

int temp = 1,dot = 1;

void moto(char dir);
void step_0_9(char dir); //���������������
char Light_Scan();       //����������


void main()
{
	while(1)
	{
		moto(Light_Scan());
	}
}


void moto(char dir)
{
	P2 = 0xff;
	if(dir == 1)
	{
		if(dot == 0)
			P2 = 0xff;
		step_0_9(2);
		step_0_9(2);
	}
	else if(dir == 2)
	{
		if(dot == 0)
			P2 = 0xff;
		step_0_9(1);
		step_0_9(1);
	}
	else if(dir == 0)
	{
		P2 = 0x00;
		dot = 0;
	}
}

void step_0_9(char dir)
{
	switch(temp)
	{
		case 1:	//��1��
			in1 = 1; 
			in2 = 0;
			in3 = 0;
			in4 = 0;
			break;
	
		case 2:	//��2��
			in1 = 1;
			in2 = 0;
			in3 = 1;
			in4 = 0;
			break;
		
		case 3:	//��3��
			in1 = 0; 
			in2 = 0;
			in3 = 1;
			in4 = 0;
			break;
		
		case 4:	//��4��
			in1 = 0; 
			in2 = 1;
			in3 = 1;
			in4 = 0;
			break;
		
		case 5:	//��5��
			in1 = 0; 
			in2 = 1;
			in3 = 0;
			in4 = 0;
			break;
			
		case 6:	//��6��
			in1 = 0;
			in2 = 1;
			in3 = 0;
			in4 = 1;
			break;
		
		case 7:	//��7��
		in1 = 0;
		in2 = 0;
		in3 = 0;
		in4 = 1;
		break;
		
		case 8:	//��8��
			in1 = 1; 
			in2 = 0;
			in3 = 0;
			in4 = 1;
			break;
		
		default: break;
	}
	
	if(dir == 1)
	{
		if(temp >= 8)
		{
				temp = 1;
		}
		else
		{
			temp++;
		}
	}
		
	else
	{
		if(temp <= 1)
		{
			temp = 8;
		}
		else
		{
				temp--;
		}
	}
	delayms(1);
	P1 = 0x00;
}

char Light_Scan()
{
	uint i = 0;
	i = SPI_AD_Read(0xE4);
	display(i);
	if(i<2000)
	{
		return 1;
	}
	else if(i>2100)
	{
		return 2;
	}
	else return 0;
}


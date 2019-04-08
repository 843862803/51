#include "I2C.h"

void delay6us(void)   //��� -0.574652777778us
{
    unsigned char a;
    for(a=1;a>0;a--);
}

void I2C_Start() //��ʼ�ź�
{
	SDA = 1;
	delay6us();
	SCL = 1;
	delay6us();
	SDA = 0;
	delay6us();
	SCL = 0;
	delay6us();
}

void I2C_Stop() //ֹͣ�ź�
{
	SDA = 0;
	delay6us();
	SCL = 1;
	delay6us();
	SDA = 1;
	delay6us();
}

unsigned char I2C_SendByte(unsigned char dat) //����һ�ֽ�
{
	unsigned char a = 0,b = 0;
	for(a=0;a<8;a++)
	{
		SDA = dat>>7;
		dat = dat<<1;
		delay6us();
		SCL = 1;
		delay6us();
		SCL = 0;
		delay6us();
	}
	SDA = 1;
	delay6us();
	SCL = 1;
	while(SDA);
	{
		b++;
		if(b>100)
		{
			SCL = 0;
			delay6us();
			return 1;
		}
	}
	SCL = 0;
	delay6us();
	return 0;
}

unsigned char I2C_ReadByte() //��һ�ֽ�
{
	unsigned char a = 0,dat = 0;
	SDA = 1;
	for(a=0;a<8;a++)
	{
		SCL = 1;
		delay6us();
		dat<<=1;
		dat |= SDA;
		delay6us();
		SCL = 0;
		delay6us();
	}
	return dat;
}

void At24c02_Write(unsigned char addr,unsigned char dat) //д������
{
	I2C_Start();
	I2C_SendByte(0xa0);
	I2C_SendByte(addr);
	I2C_SendByte(dat);
	I2C_Stop();
}

unsigned char At24c02_Read(unsigned char addr) //��ȡ����
{
	unsigned char num;
	I2C_Start();
	I2C_SendByte(0xa0);
	I2C_SendByte(addr);
	I2C_Start();
	I2C_SendByte(0xa1);
	num = I2C_ReadByte();
	I2C_Stop();
	return num;
}


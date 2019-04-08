#ifndef _I2C_H
#define _I2C_H

#include <reg52.h>

sbit SCL = P2^1;
sbit SDA = P2^0;

void I2C_Start(); //��ʼ�ź�
void I2C_Stop();  //ֹͣ�ź�
unsigned char I2C_SendByte(unsigned char dat); //����һ�ֽ�
unsigned char I2C_ReadByte();                  //��һ�ֽ�
void At24c02_Write(unsigned char addr,unsigned char dat); //д������
unsigned char At24c02_Read(unsigned char addr);          //��ȡ����


#endif
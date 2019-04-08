#ifndef _I2C_H
#define _I2C_H

#include <reg52.h>

sbit SCL = P2^1;
sbit SDA = P2^0;

void I2C_Start(); //开始信号
void I2C_Stop();  //停止信号
unsigned char I2C_SendByte(unsigned char dat); //发送一字节
unsigned char I2C_ReadByte();                  //读一字节
void At24c02_Write(unsigned char addr,unsigned char dat); //写入数据
unsigned char At24c02_Read(unsigned char addr);          //读取数据


#endif
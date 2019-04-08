#ifndef _XPT2046_h_
#define _XPT2046_h_

#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

//---定义使用的IO口---//
sbit DOUT = P3^7;	  //输出
sbit CLK  = P3^6;	  //时钟
sbit DIN  = P3^4;	  //输入
sbit CS   = P3^5;	  //片选

void SPI_Write(uchar dat); //写入数据
uint SPI_Read();             //读取数据
uint SPI_AD_Read(uchar cmd); //AD转换函数

#endif


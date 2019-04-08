#ifndef _XPT2046_h_
#define _XPT2046_h_

#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

//---����ʹ�õ�IO��---//
sbit DOUT = P3^7;	  //���
sbit CLK  = P3^6;	  //ʱ��
sbit DIN  = P3^4;	  //����
sbit CS   = P3^5;	  //Ƭѡ

void SPI_Write(uchar dat); //д������
uint SPI_Read();             //��ȡ����
uint SPI_AD_Read(uchar cmd); //ADת������

#endif


//延时函数
#ifndef _delay_h_
#define _delay_h_

#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

void delay(uint t);     //延时t秒
void delayms(uint t);   //延时t毫秒
void delay10us(uint t); //延时t10us

#endif
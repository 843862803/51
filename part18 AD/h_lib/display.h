#ifndef _display_h
#define _display_h

#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

void display(uint dis_num);//动态显示，4位
													//延时1毫秒

//void display8(uint num);//动态显示，8位

#endif
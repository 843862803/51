#ifndef _key_h_
#define _key_h_

#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;


char key1(); //  1	2		3		4
/************************************
*        矩阵键盘扫描模块            *
*                                   *
*     使用x = key();获取按键值       *
*************************************
* 矩阵键盘对应数值：                 *
*	    	1		2		3		13	            *
*	    	4		5		6		14              *
*	    	7		8		9		15              *
*	    	11	0		12	16              *
*************************************/
uchar key2();           //获取按键函数，直到检测到值
void martrixkeyscan(); //矩阵键盘扫描


#endif
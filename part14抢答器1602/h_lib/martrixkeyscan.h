/***************************************
*        矩阵键盘扫描模块               *
*                                      *
*  主函数添加#include<martrixkeyscan>   *
*            使用x = key();获取按键值   *
****************************************
*	    	1		2		3		13	               *
*	    	4		5		6		14                 *
*	    	7		8		9		15                 *
*	    	11	0		12	16                 *
****************************************/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar key();           //获取按键函数，直到检测到值
void martrixkeyscan(); //矩阵键盘扫描

/*********************************
*    倒计时设置模块（LCD1602）   *
*                                *
*     使用x = number();获取      *
* 在主函数添加uchar code txt1[]= *
*             "0123456789"; //10 *
**********************************/

#include <delay.h>
#include <lcd1602.h>
#include <martrixkeyscan.h>
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
	
char number(); //返回值即为倒计时数据
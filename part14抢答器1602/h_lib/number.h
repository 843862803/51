/*********************************
*    ����ʱ����ģ�飨LCD1602��   *
*                                *
*     ʹ��x = number();��ȡ      *
* �����������uchar code txt1[]= *
*             "0123456789"; //10 *
**********************************/

#include <delay.h>
#include <lcd1602.h>
#include <martrixkeyscan.h>
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
	
char number(); //����ֵ��Ϊ����ʱ����
/***************************
*     LCD1602��ʾģ��      *
****************************/

#include <reg52.h>
#include <delay.h>
#define uchar unsigned char
#define uint unsigned int
	
/*LCD1602ͷ�ļ�*/

void init_1602();	//��ʼ��
void write_com(uchar com);	 //дָ��
void write_data(uchar date); //д����
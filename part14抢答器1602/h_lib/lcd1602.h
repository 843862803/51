/***************************
*     LCD1602显示模块      *
****************************/

#include <reg52.h>
#include <delay.h>
#define uchar unsigned char
#define uint unsigned int
	
/*LCD1602头文件*/

void init_1602();	//初始化
void write_com(uchar com);	 //写指令
void write_data(uchar date); //写数据
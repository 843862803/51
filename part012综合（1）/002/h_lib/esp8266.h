#include <reg52.h>
#include <string.h>
#include <delay.h>
#define uchar unsigned char
#define uint unsigned int


void Set_AP();		//设置多连
void Init_Uart();	//串口初始化
void Send_Uart(uchar value);	//发送数据
void ESP8266_Set(uchar *puf);	//发送设置

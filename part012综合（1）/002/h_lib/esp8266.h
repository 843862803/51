#include <reg52.h>
#include <string.h>
#include <delay.h>
#define uchar unsigned char
#define uint unsigned int


void Set_AP();		//���ö���
void Init_Uart();	//���ڳ�ʼ��
void Send_Uart(uchar value);	//��������
void ESP8266_Set(uchar *puf);	//��������

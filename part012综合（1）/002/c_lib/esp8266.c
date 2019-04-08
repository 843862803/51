#include <esp8266.h>

sbit led1 = P2^0;

extern bit Usart_AT_flage;
extern uchar receive[];

uchar code RST[]="AT+RST\r\n"; 
uchar code CWMODE2[]="AT+CWMODE=2\r\n";
uchar code CIPMUX[]="AT+CIPMUX=1\r\n";
uchar code CIFSR[]="AT+CIFSR\r\n";
uchar code CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";

/******************************************
****ESP8266初始固件初始化函数**************
******************************************/

void Set_AP()		//设置多连
{
	led1 = 1;
	ESP8266_Set(RST);
	delayms(1500);
	ESP8266_Set(CWMODE2);
	delayms(600);
	ESP8266_Set(CIPMUX);
	delayms(600);
	ESP8266_Set(CIPSERVER);
	delayms(600);
	led1 = 0;
	/*led1 = 0;
	ESP8266_Set(RST);		//从新启动
	delayms(1500);
	led1 = ~led1;
	while(1)		//设置为AP模式，不成功重复发送
	{
		ESP8266_Set(CWMODE2);
		delayms(600);
		if(Usart_AT_flage==1)		//数据接收完成标志位
		{
			if(strstr(receive,"OK"))		//接收返回数据
			{
				Usart_AT_flage = 0;
				led1 = ~led1;		//指示灯变换
				break;
			}
		}
	}
	while(1)		//设置多连
	{
		ESP8266_Set(CIPMUX);
		delayms(600);
		if(Usart_AT_flage==1)
		{
			if(strstr(receive,"OK"))
			{
				Usart_AT_flage = 0;
				led1 = ~led1;
				break;
			}
		}
	}
	while(1)		//设置服务器，端口8080
	{
		ESP8266_Set(CIPSERVER);
		delayms(600);
		if(Usart_AT_flage==1)
		{
			if(strstr(receive,"OK"))
			{
				Usart_AT_flage = 0;
				led1 = ~led1;
				break;
			}
		}
	}
	led1 = 1;*/
}

void Init_Uart()		//串口初始化
{
	TMOD = 0x20;		//定时器1方式2
	SCON = 0x50;		//串口工作方式1，启动串行接收 01010000
	
	TH1 = 0xfd;		//晶振11.0592 波特率9600
	TL1 = TH1;		//启动定时器1
	TR1 = 1;			//以定时器1作为波特率发生器
	PCON = 0x00;		//不倍频
	EA = 1;		//开总中断
	ES = 1;		//开串口中断
}

void Send_Uart(uchar value)		//发送数据
{
	ES = 0;		//关串口中断
	TI = 0;		/*TI ：串行口发送中断请求标志。
	当CPU 发送完一串行数据后，此时SBUF 寄存器为空，
	硬件使TI 置1，请求中断。CPU 响应中断后，由软件对TI 清零。*/
	SBUF = value;
	while(TI==0);		//等待发送完成
	TI = 0;		//清除发送完成标识
	ES = 1;		//开串口中断
}

void ESP8266_Set(uchar *puf)		//发送设置
{
	while(*puf != '\0')
	{
		Send_Uart(*puf);		//一次发送一字节，依次发送
		puf++;
	}
}


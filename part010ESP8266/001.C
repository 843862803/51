#include<reg52.h>
#include<string.h>
#define uchar unsigned char
#define uint unsigned int

sbit led1 = P2^0;
sbit led2 = P2^1;
sbit led4 = P2^3;

uchar receive[30] = {0};
uchar count = 0;
bit Usart_AT_flage;

uchar code RST[]="AT+RST\r\n"; 
uchar code CWMODE2[]="AT+CWMODE=2\r\n";
uchar code CIPMUX[]="AT+CIPMUX=1\r\n";
uchar code CIFSR[]="AT+CIFSR\r\n";
uchar code CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";

void delayms(uint t);		//延时函数ms
void Init_Uart();		//串口初始化
void Send_Uart(uchar value);		//发送数据
void ESP8266_Set(uchar *puf);		//发送设置
void Set_AP();		//设置多连


void delayms(uint t)		//延时函数ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110;x>0;x--)		//延时一毫秒
		{
		}
	}
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


/******************************************
****ESP8266初始固件初始化函数**************
******************************************/

void Set_AP()		//设置多连
{
	led4 = 1;
	ESP8266_Set(RST);		//从新启动
	delayms(1500);
	led4 = ~led4;
	while(1)		//设置为AP模式，不成功重复发送
	{
		ESP8266_Set(CWMODE2);
		delayms(600);
		if(Usart_AT_flage==1)		//数据接收完成标志位
		{
			if(strstr(receive,"OK"))		//接收返回数据
			{
				Usart_AT_flage = 0;
				led4 = ~led4;		//指示灯变换
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
				led4 = ~led4;
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
				led4 = ~led4;
				break;
			}
		}
	}
	led4 = 0;
}


void Uart_Interrupt () interrupt 4		//中断接收数据
{
	if(RI)
	{
		RI = 0;
		receive[count] = SBUF;
		count++;
		if(receive[count-2]=='\r' && receive[count-1]=='\n' && count >= 2)
		{
			count = 0;
			Usart_AT_flage = 1;
		}
		else if(count>30)
		{
			count = 0;
		}
	}
}

void main()
{
	int i;
	Init_Uart();
	Set_AP();
	led1 = led2 = led4 = 0;
	while(1)		//指令判断
	{
		if((receive[0]=='+')&&(receive[1]=='I')&&(receive[2]=='P'))
		{
			if((receive[3]=='D')&&(receive[4]==','))
			{
				if(receive[9]=='1')
				{
					//delayms(20);
					led4 = 1;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
				if(receive[9]=='0')
				{
					//delayms(20);
					led4 = 0;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
				if(receive[9]=='4')
				{
					//delayms(20);
					led1 = 1;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
				if(receive[9]=='3')
				{
					//delayms(20);
					led1 = 0;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
				if(receive[9]=='6')
				{
					//delayms(20);
					led2 = 1;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
				if(receive[9]=='5')
				{
					//delayms(20);
					led2 = 0;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
			}
		}
	}
}
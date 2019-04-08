#include<reg52.h>
#include<string.h>
sbit L1 = P2^0;
sbit kaiguan = P3^0;
sbit L2 = P2^1;
sbit L3 = P2^2;
sbit L4 = P2^3;
sbit L5 = P2^4;
sbit L6 = P2^5;
sbit L7 = P2^6;
sbit L8 = P2^7;

sfr AUXR=0x8E;
sfr BRT=0x9C;
sfr AUXR1=0xA2;

unsigned char Usart_Receive[20]={0};
unsigned char Usart_Cnt=0;
bit Usart_AT_flage;
unsigned char code RST[]="AT+RST\r\n"; 
unsigned char code CWMODE2[]="AT+CWMODE=2\r\n";
unsigned char code CIPMUX[]="AT+CIPMUX=1\r\n";
unsigned char code CIFSR[]="AT+CIFSR\r\n";
unsigned char code CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";
/**********************************************************/
void delay_ms(unsigned long t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
	{
		for(y=110;y>0;y--)
		{
		}
	}
}
/**********************************************************/
void delays(void)
{
	unsigned char a,b,c;
	for(c=95;c>0;c--)
	{
		for (b=26;b>0;b--)
		{
			for (a=185;a>0;a--)
			{
			}
		}
	}
}

/*void InitUART(void)		//9600bps@12.000MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xD9;		//设定定时初值
	TH1 = 0xD9;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
*/

/***************中断设置***********************************/
void InitUART(void)
{
	TMOD=0x20;
	SCON=0x50;
/***************波特率设置*********************************/
	TH1=0xFD;
	TL1=TH1;
	PCON=0x00;
	EA=1;
	ES=1;
	TR1=1;
}
/*************发送数据***************************************/
void Send_Uart(unsigned char value)
{
	ES=0;
	TI=0;
	SBUF=value;
	while(TI==0);
	TI=0;
	ES=1;
}
/*************接受数据***************************************/
void UARTInterrupt(void)interrupt 4
{
	if(RI)
	{
		RI=0;
		Usart_Receive[Usart_Cnt]=SBUF;
		Usart_Cnt++;
		if(Usart_Receive[Usart_Cnt-2]=='\r'&&Usart_Receive[Usart_Cnt-1]=='\n'&&Usart_Cnt>=2)
		{
			Usart_Cnt=0;
			Usart_AT_flage=1;
		}
		else if(Usart_Cnt>20)
		{
			Usart_Cnt=0;
		}
	}
}
/*****************发送设置**********************************/
void ESP8266_Set(unsigned char *puf)
{
    while(*puf!='\0')
    {
        Send_Uart(*puf);
        puf++;
    }
}
/**************设置多连*************************************/
void ManyConnect_AP()
{
	L4=0;
	ESP8266_Set(RST);//返回一大溜，不用判断返回
  delays();
  delays();
	while(1)
	{
		ESP8266_Set(CWMODE2);//返回ok
    delays();
    if(Usart_AT_flage ==1)
		{
			if(strstr(Usart_Receive, "OK") )
			{
				Usart_AT_flage = 0;
        L4 = ~L4;
        break;
			}
		}
	}
	while (1)
	{
		ESP8266_Set(CIPMUX);//返回ok
    delays();
    if(Usart_AT_flage ==1)
		{
			if(strstr(Usart_Receive, "OK") )
			{
				Usart_AT_flage = 0;
        L4 = ~L4;
        break;
			}
		}
	}
	while (1)
	{
		ESP8266_Set(CIPSERVER);//返回ok，多了也返回ok
        delays();
        if(Usart_AT_flage ==1)
		{
			if(strstr(Usart_Receive, "OK") )
			{
				Usart_AT_flage = 0;
                L4 = ~L4;
                break;
			}
		}
	}
	
	P2 = 0x00;
}
/***************延时500ms***************************/
void delays500ms(void)
{
	unsigned char a,b,c;
    for(c=123;c>0;c--)
	{
        for(b=212;b>0;b--)
		{
            for(a=25;a>0;a--)
			{
			}
		}
	}
}
/**************主函数**********************************/
void main()
{
	int i;
	P2=0xFF;
	//kaiguan=0;
	InitUART();
	while(1)
	{
		ManyConnect_AP();
		while(1)
		{
			 //由于消息的开头是+IP  故做此判断，00000000000000000号
            if((Usart_Receive[0]=='+')&&(Usart_Receive[1]=='I')&&(Usart_Receive[2]=='P'))
            {
                if((Usart_Receive[3]=='D')&&(Usart_Receive[6]==','))
                {
                    if(Usart_Receive[9]=='1')
                    {
                        delays500ms();
                        P2=0xFF;
                        delays();
                        for(i = 0 ; i<20; i++)
                        {
                            Usart_Receive[i]=' ';
                        }
										}
										if(Usart_Receive[9]=='0')
										{
											P2=0x00;
											delays();
											for(i=0;i<20;i++)
											{
												Usart_Receive[i]=' ';
											}
										}
							}
			}
		}
	}
}
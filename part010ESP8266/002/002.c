
//��Ƭ��������������ֻ�ܸ��õ͵�ƽ����
#include<reg52.h>
#include<string.h>
#define uchar unsigned char
#define uint unsigned int


sbit led4 = P2^3;
sbit k = P3^2;
bit Usart_AT_flage;		//���ݽ�����ɱ�־λ

uchar receive[20] = {0};		//������������
uchar count = 0;
uchar x,y;

/*
uchar code RST[]="AT+RST\r\n"; 
uchar code CWMODE2[]="AT+CWMODE=2\r\n";
uchar code CIPMUX[]="AT+CIPMUX=1\r\n";
uchar code CIFSR[]="AT+CIFSR\r\n";
uchar code CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";
*/
uchar code yes[]="param button YES\r\n";
uchar code no[]="param button NO\r\n";


void delayms(uint t);		//��ʱ����ms
void Init_Uart();		//���ڳ�ʼ��
void Send_Uart(uchar value);		//��������
void ESP8266_send(uchar *puf);		//��������
//void Set_AP();		//���ö���


void delayms(uint t)		//��ʱ����ms
{
	uchar x;
	for(t;t>0;t--)
	{
		for(x=110;x>0;x--)		//��ʱһ����
		{
		}
	}
}

void Init_Uart()		//���ڳ�ʼ��
{
	TMOD = 0x20;		//��ʱ��1��ʽ2
	SCON = 0x50;		//���ڹ�����ʽ1���������н��� 01010000
  /**************************
	** ����SCON = 0x40;      **
	** REN = 1; �������ڽ��� **
	**************************/
	TH1 = 0xfd;		//����11.0592 ������9600
	TL1 = TH1;		//������ʱ��1
	TR1 = 1;			//�Զ�ʱ��1��Ϊ�����ʷ�����
	PCON = 0x00;		//����Ƶ
	EA = 1;		//�����ж�
	ES = 1;		//�������ж�
}

void Send_Uart(uchar value)		//��������
{
	ES = 0;		//�ش����ж�
	TI = 0;
	/*************************************************************
	** TI �����пڷ����ж������־��														**
	** ��CPU ������һ�������ݺ󣬴�ʱSBUF �Ĵ���Ϊ�գ�					**
	** Ӳ��ʹTI ��1�������жϡ�CPU ��Ӧ�жϺ��������TI ���㡣**
	*************************************************************/
	SBUF = value;		//�����͵����ݴ���SBUF������
	while(TI==0);		//�ȴ����ݷ������
	TI = 0;		//���������ɱ�ʶ
	ES = 1;		//�������ж�
}

void ESP8266_send(uchar *puf)		//��������&���ݻش��������ַ�����
{
	while(*puf != '\0')		//����ַ����Ƿ����
	{
		Send_Uart(*puf);		//һ�η���һ�ֽڣ����η���
		puf++;
	}
}


/******************************************
*******ESP8266��ʼ�̼���ʼ������***********
******************************************/

/*
void Set_AP()		//���ö���
{
	led4 = 1;
	ESP8266_send(RST);		//��������
	delayms(1500);
	led4 = ~led4;
	while(1)		//����ΪAPģʽ�����ɹ��ظ�����
	{
		ESP8266_send(CWMODE2);
		delayms(600);
		if(Usart_AT_flage==1)		//���ݽ�����ɱ�־λ
		{
			if(strstr(receive,"OK"))		//���շ�������
			{
				Usart_AT_flage = 0;
				led4 = ~led4;		//ָʾ�Ʊ任
				break;
			}
		}
	}
	while(1)		//���ö���
	{
		ESP8266_send(CIPMUX);
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
	while(1)		//���÷��������˿�8080
	{
		ESP8266_send(CIPSERVER);
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
*/


void Uart_Interrupt () interrupt 4		//�жϽ�������
{
	if(RI)
	{
		RI = 0;		//�ֶ����������ɱ�־
		receive[count] = SBUF;
		count++;
		if(receive[count-2]=='\r' && receive[count-1]=='\n' && count >= 2)
		{
			count = 0;
			Usart_AT_flage = 1;
		}
		else if(count>20)
		{
			count = 0;
		}
	}
}

void main()
{
	int i;
	Init_Uart();
	//Set_AP();
	//led4 = 1;
	//delayms(5000);		//���ڸ������̼���ʼ��ʱ��
	led4 = 1;
	x = y = 0;
	ESP8266_send(no);
	while(1)		//ָ���ж�
	{
		if((receive[0]=='$')&&(receive[1]=='{')&&(receive[2]=='c'))
		{
			if((receive[3]=='s')&&(receive[4]=='}'))
			{
				if(receive[5]=='1')
				{
					delayms(2);
					led4 = 0;
					ESP8266_send(yes);  //״̬�ش�
					x = 1;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
				if(receive[5]=='0')
				{
					delayms(2);
					led4 = 1;
					ESP8266_send(no);
					x = 0;
					for(i=0;i<20;i++)
					{
						receive[i] = ' ';
					}
				}
			}
		}
		delayms(50);
		if(k==0)
		{
			led4 = ~led4;
			if(led4==0)
			{
				ESP8266_send(yes);
				x = 1;
			}
			else
			{
				ESP8266_send(no);
				x = 0;
			}
			while(k==0);
		}
		delayms(50);
		y++;
		if(y>=200)
		{
			y = 0;
			if(x==1)
			{
				ESP8266_send(yes);
			}
			if(x==0)
			{
				ESP8266_send(no);
			}
		}
	}
}
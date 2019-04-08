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
****ESP8266��ʼ�̼���ʼ������**************
******************************************/

void Set_AP()		//���ö���
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
	ESP8266_Set(RST);		//��������
	delayms(1500);
	led1 = ~led1;
	while(1)		//����ΪAPģʽ�����ɹ��ظ�����
	{
		ESP8266_Set(CWMODE2);
		delayms(600);
		if(Usart_AT_flage==1)		//���ݽ�����ɱ�־λ
		{
			if(strstr(receive,"OK"))		//���շ�������
			{
				Usart_AT_flage = 0;
				led1 = ~led1;		//ָʾ�Ʊ任
				break;
			}
		}
	}
	while(1)		//���ö���
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
	while(1)		//���÷��������˿�8080
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

void Init_Uart()		//���ڳ�ʼ��
{
	TMOD = 0x20;		//��ʱ��1��ʽ2
	SCON = 0x50;		//���ڹ�����ʽ1���������н��� 01010000
	
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
	TI = 0;		/*TI �����пڷ����ж������־��
	��CPU ������һ�������ݺ󣬴�ʱSBUF �Ĵ���Ϊ�գ�
	Ӳ��ʹTI ��1�������жϡ�CPU ��Ӧ�жϺ��������TI ���㡣*/
	SBUF = value;
	while(TI==0);		//�ȴ��������
	TI = 0;		//���������ɱ�ʶ
	ES = 1;		//�������ж�
}

void ESP8266_Set(uchar *puf)		//��������
{
	while(*puf != '\0')
	{
		Send_Uart(*puf);		//һ�η���һ�ֽڣ����η���
		puf++;
	}
}


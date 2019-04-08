#include <reg52.h>
 
int count;      //0.5ms������ʶ
int jd;         //�Ƕȱ�ʶ

sbit pwm =P1^0;           //PWM�ź����
sbit jia =P3^0;           //�Ƕ����Ӱ������IO��
sbit jan =P3^1;           //�Ƕȼ��ٰ������IO��

void delay(unsigned char i); //��ʱ
void InitTimer0(void);       //��ʱ����ʼ��
void keyscan();              //����ɨ��


void main()
{
	jd=15;
	count=0;
	InitTimer0();	
	while(1)
	{
		keyscan();
	}
}


 
void delay(unsigned char i)//��ʱ
{
	unsigned char j,k;
	for(j=i;j>0;j--)
	for(k=125;k>0;k--);
}

//void InitTimer0(void) //10us 
//{
//    TMOD = 0x01;
//    TH0 = 0x0FF;
//    TL0 = 0x0F7;
//    EA = 1;
//    ET0 = 1;
//    TR0 = 1;
//}

void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x0FF;
    TL0 = 0x0A4;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

//void InitTimer0(void) //50us -0.0868055556
//{
//    TMOD = 0x01;
//    TH0 = 0x0FF;
//    TL0 = 0x0D2;
//    EA = 1;
//    ET0 = 1;
//    TR0 = 1;
//}
 
void Timer0Interrupt() interrupt 1 //�жϳ���
{
	TH0 = 0x0FF;
  TL0 = 0x0A4;
	if(count< jd)             //�ж�0.1ms�����Ƿ�С�ڽǶȱ�ʶ
		pwm=1;                  //ȷʵС�ڣ�PWM����ߵ�ƽ
	else
		pwm=0;                  //����������͵�ƽ
	count=(count+1);          //0.1ms������1
	count=count%200;         //����ʼ�ձ���Ϊ2000 ����������Ϊ20ms
}
 
void keyscan()              //����ɨ��
{ 
  if(jia==0)               //�Ƕ����Ӱ����Ƿ���
  {
   delay(10);              //������ʱ������
   if(jia==0)              //ȷʵ����
    {
     jd++;                 //�Ƕȱ�ʶ��1
     count=0;              //�������� ��20ms���ڴ��¿�ʼ
     if(jd==26)
       jd=25;               //�Ѿ���180�ȣ��򱣳�
     while(jia==0);        //�ȴ������ſ�
    }
  }
 
 if(jan==0)                //�Ƕȼ�С�����Ƿ���
  {
   delay(10);
   if(jan==0)
    {
     jd--;                 //�Ƕȱ�ʶ��1
     count=0;
     if(jd==4)
       jd=5;               //�Ѿ���0�ȣ��򱣳�
     while(jan==0);
    }
  }
}

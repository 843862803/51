#include <reg52.h>
 
int count;      //0.5ms次数标识
int jd;         //角度标识

sbit pwm =P1^0;           //PWM信号输出
sbit jia =P3^0;           //角度增加按键检测IO口
sbit jan =P3^1;           //角度减少按键检测IO口

void delay(unsigned char i); //延时
void InitTimer0(void);       //定时器初始化
void keyscan();              //按键扫描


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


 
void delay(unsigned char i)//延时
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
 
void Timer0Interrupt() interrupt 1 //中断程序
{
	TH0 = 0x0FF;
  TL0 = 0x0A4;
	if(count< jd)             //判断0.1ms次数是否小于角度标识
		pwm=1;                  //确实小于，PWM输出高电平
	else
		pwm=0;                  //大于则输出低电平
	count=(count+1);          //0.1ms次数加1
	count=count%200;         //次数始终保持为2000 即保持周期为20ms
}
 
void keyscan()              //按键扫描
{ 
  if(jia==0)               //角度增加按键是否按下
  {
   delay(10);              //按下延时，消抖
   if(jia==0)              //确实按下
    {
     jd++;                 //角度标识加1
     count=0;              //按键按下 则20ms周期从新开始
     if(jd==26)
       jd=25;               //已经是180度，则保持
     while(jia==0);        //等待按键放开
    }
  }
 
 if(jan==0)                //角度减小按键是否按下
  {
   delay(10);
   if(jan==0)
    {
     jd--;                 //角度标识减1
     count=0;
     if(jd==4)
       jd=5;               //已经是0度，则保持
     while(jan==0);
    }
  }
}

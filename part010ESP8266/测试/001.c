#include<reg52.h>
/**********类型定义**************/
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define code const
/***********IO定义***************/
//定义P5.5口 LED指示灯
sbit  LED=P2^4;         

/**********缓存变量**************/
//串口接受缓存
u8 xdata RX_buffer[tbuf];
//接收计数变量
u8 RX_num;

/**********预定义字符串**************/
//握手连接指令，返回"OK"
u8 code esp_at[]="AT\r\n";
//设置ESP8266的工作模式1 Station，返回"OK"或者"no change"
u8 code esp_cwmode[]="AT+CWMODE=1\r\n";
//连接到WiFi热点或无线路由上，NXP为无线路由名称，12345678为密码；连接成功返回“OK”             
u8 code esp_cwjap[]="AT+CWJAP=\"123\",\"66668888\"\r\n";
//本机IP地址查询指令                     
u8 code esp_cifsr[]="AT+CIFSR\r\n";
//连接到TCP服务器，返回“Linked”
//192.168.0.149为服务器IP地址 6000为服务器端口号 不同电脑不同软件可能会不一样的
u8 code esp_cipsta[]="AT+CIPSTART=\"TCP\",\"192.168.0.149\",6000\r\n"; 
// 设置发送数据长度
u8 code esp_cipsend[]="AT+CIPSEND=5\r\n";


//设置多链接
u8 code esp_DuoLianjie []="AT+CIPMUX=1\r\n";        
//设置端口号
u8 code esp_Port []="AT+CIPSERVER=1,3122\r\n";      
//查询模块自身IP，返回IP地址
u8 code esp_IP []="AT+CIFSR\r\n";                   

//服务器发送 握手数据
u8 code esp_Woshou []=":test";
//服务器发送 LED检测数据             
u8 code esp_test_LED []=":LED";
//服务器发送 打开LED              
u8 code esp_LED_ON []=":LED ON";
//服务器发送 关闭LED           
u8 code esp_LED_OFF []=":LED OFF";          

//复位重启
u8 code esp_Rst []="AT+RST\r\n";            
//发送数据长度
u8 code esp_DATA []="AT+CIPSEND=1024\r\n";





//指定字符串与缓存数组数据进行数据比较
//*p 要比较的指定字符串指针数据
//返回：1 数据一致  0 数据不一致 
u8 Data_compare(u8 *p)
{ 
    if(strstr(RX_buffer,p)!=NULL)
        return 1;
    else
        return 0;
}





//针对 IAP15W4K61S4   STC15W4K56S4 系列 IO口初始化
//io口初始化 P0 P1 P2 P3 P4 为准双向IO口   
//注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
//      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
//相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
void IO_init(void)
{
  P0M0 = 0X00;
  P0M1 = 0X00;

  P1M0 = 0X00;
  P1M1 = 0X00;

  P2M0 = 0X00;
  P2M1 = 0X00;

  P3M0 = 0X00;
  P3M1 = 0X00;

  P4M0 = 0X00;
  P4M1 = 0X00;  
}





void UartInit(void)     
{      
    S2CON = 0x50;       //8位数据，可变波特率
    AUXR |= 0x04;       //定时器2时钟1为FOSC,即1T

    T2L=(65536-(11059200/4/115200));    //设置定时初值
    T2H=(65536-(11059200/4/115200))>>8; //设置定时初值

    AUXR |= 0x10;       //启动定时器2       
}

//串口2发送串口数据(字节)
void Uart2SendByte(u8 ch)
{
    S2BUF = ch;                 //写数据到UART2数据寄存器
    while(!(S2CON&S2TI));    
    S2CON&=~S2TI;
}

//串口2发送字符串
void Uart2SendStr(u8 *s)
{
 IE2 = 0x00; 
    while (*s)                  //检测字符串结束标志
    {
       Uart2SendByte(*s++);     //发送当前字符
    }
 IE2 = 0x01;
}

//串口2中断
void Uart2() interrupt 8 using 1
{

        IE2 = 0x00;       //关闭串口2中断
    if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;         
                RX_buffer[RX_num] = S2BUF; 
                RX_num++;               
                if(RX_num>tbuf) RX_num = 0;  
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;            
    }
        IE2 = 0x01;     //开启串口2中断

}





// 1 发送AT 进行握手
    while(1)
    {
     Uart2SendStr(esp_at);     //串口2对wifi模块发送握手指令 即AT
     if(Data_compare("OK"))break;
     else  Uart1SendStr("ERROR1,some problems with ESP8266 \r\n");
     delay1ms(600);
    }
     Uart1SendStr("OK,mcu connection success with ESP8266! \r\n");
     memset(RX_buffer, 0, tbuf);//清缓存数据
     RX_num=0;                 //接收计数变量清0



    // 2 配置wifi工作模式为SA模式
    while(1)
    {
     Uart2SendStr(esp_cwmode);     //串口2对wifi模块工作模式进行设置  
     if(Data_compare("OK")||Data_compare("no change"))break;
     delay1ms(600);
    }
     memset(RX_buffer, 0, tbuf);//清缓存数据 
     RX_num=0;                 //接收计数变量清0



    // 3 连接热点wifi  wifi名 密码  如果失败 延时继续连接
    while(1)
    {
     Uart2SendStr(esp_cwjap);      //串口2发送 指点wifi名 密码 等待模块连接 
     if(Data_compare("OK"))break;
     delay1ms(3000);
    }
    memset(RX_buffer, 0, tbuf);//清缓存数据
    RX_num=0;                  //接收计数变量清0


     // 4 设置多链接
    while(1)
    {
         Uart2SendStr(esp_DuoLianjie);              //设置多链接
         if(Data_compare("OK"))break;
         delay1ms(3000);
    }
    memset(RX_buffer, 0, tbuf);//清缓存数据
    RX_num=0;                  //接收计数变量清0

    // 5 设置端口号
    while(1)
    {
         Uart2SendStr(esp_Port);                //设置端口号
         if(Data_compare("OK"))
         {
            delay1ms(3000); 
            break;
         }
         delay1ms(3000);
    }
    Uart1SendStr("OK,Succeed esp_Port\r\n");    
    memset(RX_buffer, 0, tbuf);//清缓存数据
    RX_num=0;    //接收计数变量清0
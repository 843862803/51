#include<reg52.h>
/**********���Ͷ���**************/
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define code const
/***********IO����***************/
//����P5.5�� LEDָʾ��
sbit  LED=P2^4;         

/**********�������**************/
//���ڽ��ܻ���
u8 xdata RX_buffer[tbuf];
//���ռ�������
u8 RX_num;

/**********Ԥ�����ַ���**************/
//��������ָ�����"OK"
u8 code esp_at[]="AT\r\n";
//����ESP8266�Ĺ���ģʽ1 Station������"OK"����"no change"
u8 code esp_cwmode[]="AT+CWMODE=1\r\n";
//���ӵ�WiFi�ȵ������·���ϣ�NXPΪ����·�����ƣ�12345678Ϊ���룻���ӳɹ����ء�OK��             
u8 code esp_cwjap[]="AT+CWJAP=\"123\",\"66668888\"\r\n";
//����IP��ַ��ѯָ��                     
u8 code esp_cifsr[]="AT+CIFSR\r\n";
//���ӵ�TCP�����������ء�Linked��
//192.168.0.149Ϊ������IP��ַ 6000Ϊ�������˿ں� ��ͬ���Բ�ͬ������ܻ᲻һ����
u8 code esp_cipsta[]="AT+CIPSTART=\"TCP\",\"192.168.0.149\",6000\r\n"; 
// ���÷������ݳ���
u8 code esp_cipsend[]="AT+CIPSEND=5\r\n";


//���ö�����
u8 code esp_DuoLianjie []="AT+CIPMUX=1\r\n";        
//���ö˿ں�
u8 code esp_Port []="AT+CIPSERVER=1,3122\r\n";      
//��ѯģ������IP������IP��ַ
u8 code esp_IP []="AT+CIFSR\r\n";                   

//���������� ��������
u8 code esp_Woshou []=":test";
//���������� LED�������             
u8 code esp_test_LED []=":LED";
//���������� ��LED              
u8 code esp_LED_ON []=":LED ON";
//���������� �ر�LED           
u8 code esp_LED_OFF []=":LED OFF";          

//��λ����
u8 code esp_Rst []="AT+RST\r\n";            
//�������ݳ���
u8 code esp_DATA []="AT+CIPSEND=1024\r\n";





//ָ���ַ����뻺���������ݽ������ݱȽ�
//*p Ҫ�Ƚϵ�ָ���ַ���ָ������
//���أ�1 ����һ��  0 ���ݲ�һ�� 
u8 Data_compare(u8 *p)
{ 
    if(strstr(RX_buffer,p)!=NULL)
        return 1;
    else
        return 0;
}





//��� IAP15W4K61S4   STC15W4K56S4 ϵ�� IO�ڳ�ʼ��
//io�ڳ�ʼ�� P0 P1 P2 P3 P4 Ϊ׼˫��IO��   
//ע��: STC15W4K32S4ϵ�е�оƬ,�ϵ��������PWM��ص�IO�ھ�Ϊ
//      ����̬,�轫��Щ������Ϊ׼˫��ڻ�ǿ����ģʽ��������ʹ��
//���IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
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
    S2CON = 0x50;       //8λ���ݣ��ɱ䲨����
    AUXR |= 0x04;       //��ʱ��2ʱ��1ΪFOSC,��1T

    T2L=(65536-(11059200/4/115200));    //���ö�ʱ��ֵ
    T2H=(65536-(11059200/4/115200))>>8; //���ö�ʱ��ֵ

    AUXR |= 0x10;       //������ʱ��2       
}

//����2���ʹ�������(�ֽ�)
void Uart2SendByte(u8 ch)
{
    S2BUF = ch;                 //д���ݵ�UART2���ݼĴ���
    while(!(S2CON&S2TI));    
    S2CON&=~S2TI;
}

//����2�����ַ���
void Uart2SendStr(u8 *s)
{
 IE2 = 0x00; 
    while (*s)                  //����ַ���������־
    {
       Uart2SendByte(*s++);     //���͵�ǰ�ַ�
    }
 IE2 = 0x01;
}

//����2�ж�
void Uart2() interrupt 8 using 1
{

        IE2 = 0x00;       //�رմ���2�ж�
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
        IE2 = 0x01;     //��������2�ж�

}





// 1 ����AT ��������
    while(1)
    {
     Uart2SendStr(esp_at);     //����2��wifiģ�鷢������ָ�� ��AT
     if(Data_compare("OK"))break;
     else  Uart1SendStr("ERROR1,some problems with ESP8266 \r\n");
     delay1ms(600);
    }
     Uart1SendStr("OK,mcu connection success with ESP8266! \r\n");
     memset(RX_buffer, 0, tbuf);//�建������
     RX_num=0;                 //���ռ���������0



    // 2 ����wifi����ģʽΪSAģʽ
    while(1)
    {
     Uart2SendStr(esp_cwmode);     //����2��wifiģ�鹤��ģʽ��������  
     if(Data_compare("OK")||Data_compare("no change"))break;
     delay1ms(600);
    }
     memset(RX_buffer, 0, tbuf);//�建������ 
     RX_num=0;                 //���ռ���������0



    // 3 �����ȵ�wifi  wifi�� ����  ���ʧ�� ��ʱ��������
    while(1)
    {
     Uart2SendStr(esp_cwjap);      //����2���� ָ��wifi�� ���� �ȴ�ģ������ 
     if(Data_compare("OK"))break;
     delay1ms(3000);
    }
    memset(RX_buffer, 0, tbuf);//�建������
    RX_num=0;                  //���ռ���������0


     // 4 ���ö�����
    while(1)
    {
         Uart2SendStr(esp_DuoLianjie);              //���ö�����
         if(Data_compare("OK"))break;
         delay1ms(3000);
    }
    memset(RX_buffer, 0, tbuf);//�建������
    RX_num=0;                  //���ռ���������0

    // 5 ���ö˿ں�
    while(1)
    {
         Uart2SendStr(esp_Port);                //���ö˿ں�
         if(Data_compare("OK"))
         {
            delay1ms(3000); 
            break;
         }
         delay1ms(3000);
    }
    Uart1SendStr("OK,Succeed esp_Port\r\n");    
    memset(RX_buffer, 0, tbuf);//�建������
    RX_num=0;    //���ռ���������0
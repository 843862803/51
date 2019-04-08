#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit in1 = P1^0;
sbit in2 = P1^1;
sbit in3 = P1^2;
sbit in4 = P1^3;


int temp = 1;

void delayms(int n)
{
	int i;
	for(n;n>0;n--)
	{
		for(i=110;i>0;i--);
	}
}

void step_0_9(char dir)
{
	switch(temp)
	{
		case 1:	//第1步
			in1 = 1; 
			in2 = 0;
			in3 = 0;
			in4 = 0;
			break;
	
		case 2:	//第2步
			in1 = 1;
			in2 = 0;
			in3 = 1;
			in4 = 0;
			break;
		
		case 3:	//第3步
			in1 = 0; 
			in2 = 0;
			in3 = 1;
			in4 = 0;
			break;
		
		case 4:	//第4步
			in1 = 0; 
			in2 = 1;
			in3 = 1;
			in4 = 0;
			break;
		
		case 5:	//第5步
			in1 = 0; 
			in2 = 1;
			in3 = 0;
			in4 = 0;
			break;
			
		case 6:	//第6步
			in1 = 0;
			in2 = 1;
			in3 = 0;
			in4 = 1;
			break;
		
		case 7:	//第7步
		in1 = 0;
		in2 = 0;
		in3 = 0;
		in4 = 1;
		break;
		
		case 8:	//第8步
			in1 = 1; 
			in2 = 0;
			in3 = 0;
			in4 = 1;
			break;
		
		default: break;
	}
	
	if(dir == 1)
	{
		if(temp >= 8)
		{
				temp = 1;
		}
		else
		{
			temp++;
		}
	}
		
	else
	{
		if(temp <= 1)
		{
			temp = 8;
		}
		else
		{
				temp--;
		}
	}
}

void onestep_3_6(int m)
{
	while(m--)
	{
		in1 = 1;
		in2 = 0;
		in3 = 1;
		in4 = 0;
		delayms(1);
		
		in1 = 0;
		in2 = 1;
		in3 = 1;
		in4 = 0;
		delayms(1);
		
		in1 = 0;
		in2 = 1;
		in3 = 0;
		in4 = 1;
		delayms(1);
		
		in1 = 1;
		in2 = 0;
		in3 = 0;
		in4 = 1;
		delayms(1);
		
		P1 = 0x00;
	
	}
}

void main()
{
	char i;
	while(1)
	{
	
		for(i=100;i>0;i--)
		{
			step_0_9(0);
			delayms();
		}
		P1 = 0x00;
		delayms(1000);
	}
}
#include <number.h>

char number();

//uchar code txt1[]="0123456789";   //10
uchar code txt2[]="Duration:(s)"; //12

uchar number_1,number_2,number_3,number_s;
extern uchar num,code txt1[];

char number()
{
	number_dot1:
	init_1602();
	write_com(0x80);
	for(num=0;num<12;num++) //显示设置时间界面
	{
		write_data(txt2[num]);
		delay(1);
	}
	number_1 = number_2 = number_3 = number_s = 0;
	number_dot2:
	write_com(0x80+0x40);
	number_1 = key();
	if(number_1 < 10) //判断第一个是否为数
	{
		write_data(txt1[number_1]);
		number_dot3:
		number_2 = key();
		if(number_2 < 10) //判断第二个是否为数
		{
			write_data(txt1[number_2]);
			number_s = number_1*10+number_2;
			number_dot4:
			number_3 = key();
			if(number_3 == 11) //判断第三个是否为数
			{
				goto number_dot1;
			}
			if(number_3 == 12)
			{
				return number_s;
				
			}
			else
			{
				goto number_dot4;
			}
		}
		if(number_2 == 11)
		{
			goto number_dot1;
		}
		if(number_2 == 12)
		{
			number_s = number_1;
			return number_s;
		}
		if(number_2 > 12)
		{
			goto number_dot3;
		}
	}
	if(number_1 == 11)
	{
		goto number_dot1;
	}
	if(number_1 == 12)
	{
		return 0;
	}
	if(number_1 > 12)
	{
		goto number_dot2;
	}
}
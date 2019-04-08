#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define led P2	

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit led0 = P2^0;

void delay(uint t)
{
	uchar x1;
	for(t;t>0;t--)
	{
		for(x1=124;x1>0;x1--)
		{
		}
	}
}

char k()
{
	if(k1==0)
		return 1;
	else if(k2==0)
		return 2;
	else return 0;
}

void main()
{
	uchar x3;
	led = 0xfe;
	if(k()==1)
	{
		while(k()==1)
		{
		}
		while(1)
		{
			for(x3=0;x3<7;x3++)	 //½«led×óÒÆÒ»Î»
			{
				led = _crol_(led,1);
				delay(50);
				if(k()==1)
				{
					delay(10);
					if(k()==1)
					{
						while(k()==1)
						{
						}
						while(1)
						{
							if(k()==1)
							{
								delay(10);
								if(k()==1)
								{
									while(k()==1)
									{
									}
									break;
								}
							}
						}
					}
				}
				delay(50);
				if(k()==1)
				{
					delay(10);
					if(k()==1)
					{
						while(k()==1)
						{
						}
						while(1)
						{
							if(k()==1)
							{
								delay(10);
								if(k()==1)
								{
									while(k()==1)
									{
									}
									break;
								}
							}
						}
					}
				}
			}
			for(x3=0;x3<7;x3++)
			{
				led = _cror_(led,1);
				delay(50);
				if(k()==1)
				{
					delay(10);
					if(k()==1)
					{
						while(k()==1)
						{
						}
						while(1)
						{
							if(k()==1)
							{
								delay(10);
								if(k()==1)
								{
									while(k()==1)
									{
									}
									break;
								}
							}
						}
					}
				}
				delay(50);
				if(k()==1)
				{
					delay(10);
					if(k()==1)
					{
						while(k()==1)
						{
						}
						while(1)
						{
							if(k()==1)
							{
								delay(10);
								if(k()==1)
								{
									while(k()==1)
									{
									}
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}
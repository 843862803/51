#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit lcden = P2^7;
sbit lcdrs = P2^6;
sbit lcdrw = P2^5;
sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;


uchar code table1[]="0123456789-";
uchar code table2[]=" Timer";
uchar code table3[]="ASDFGHJKLQWERTYUIOPZXCVBNM";
uchar code table4[]="asdfghjklzxcvbnmqwertyuiop";
uchar num;
uchar x,y,z,a,b,c;

void delay(uint z)
{
	uint x;
	for(z;z>0;z--)
		for(x=123;x>0;x--);
}

void write_com(uchar com)
{
	lcdrs = 0;
	P0 = com;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
	
}

void write_data(uchar date)
{
	lcdrs = 1;
	P0 = date;
	delay(5);
	lcden = 1;
	delay(5);
	lcden = 0;
}

void init()
{
	lcden = 0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

/*void main()
{
	lcdrw=0;
	init();
	write_com(0x80);
	for(num=0;num<27;num++)
	{
		write_data(table4[num]);
		delay(5);
	}
	write_com(0x80+0x40);
	for(num=0;num<27;num++)
	{
		write_data(table3[num]);
		delay(5);
	}
	for(num=0;num<10;num++)
	{
		write_com(0x18);
		delay(1000);
	}
}*/

/*void main()
{
	lcdrw = 0;
	init();
	dot1:
	write_com(0x01);
	delay(5);
	write_com(0x80);
	for(num=0;num<28;num++)
	{
		write_data(table1[num]);
		delay(5);
	}
	write_com(0x80+0x40);
	for(num=0;num<28;num++)
	{
		write_data(table2[num]);
		delay(5);
	}
	for(num=0;num<12;num++)
	{
		write_com(0x18);
		delay(600);
	}
	goto dot1;
}*/

void main()
{
dot1:
	lcdrw = 0;
	init();
	write_data(table2[0]);
	write_data(table2[0]);
	write_data(table2[0]);
	write_data(table2[0]);
	write_data(table2[0]);
	write_data(table2[1]);
	write_data(table2[2]);
	write_data(table2[3]);
	write_data(table2[4]);
	write_data(table2[5]);
	while(k1);
	if(k1==0)
	{
		write_com(0x01);
		for(x=0;x<10;x++)
		{
			for(y=0;y<10;y++)
			{
				for(z=0;z<6;z++)
				{
					for(a=0;a<10;a++)
					{
						for(b=0;b<6;b++)
						{
							for(c=0;c<10;c++)
							{
								write_data(table1[x]);
								write_data(table1[y]);
								write_data(table1[10]);
								write_data(table1[z]);
								write_data(table1[a]);
								write_data(table1[10]);
								write_data(table1[b]);
								write_data(table1[c]);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(112);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								delay(100);
								if(k2==0)
								{
									while(k1)
									{
										if(k3==0)
										{
											goto dot1;
										}
									}
								}
								if(k3==0)
								{
									goto dot1;
								}
								write_com(0x01);
							}
						}
					}
				}
			}
		}
	}
}

//124*1000=124000
//123*1005=123615
//123*1004=123492
//123*1003=123369(001)

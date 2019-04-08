#include <martrixkeyscan.h>

uchar martrixkeyscan_out_1=0,martrixkeyscan_x_1=0,martrixkeyscan_out_2,martrixkeyscan_out_3;

void martrixkeyscan();
uchar key();

uchar key()
{
	while(1)
	{
		martrixkeyscan();
		if(martrixkeyscan_x_1  == 1)
		{
			martrixkeyscan_x_1 = 0;
			martrixkeyscan_out_3 = martrixkeyscan_out_2;
			martrixkeyscan_out_2 = 88;
			return martrixkeyscan_out_3;
			break;
		}
	}
}

void martrixkeyscan()
{
	uchar x1,x2;
	P1 = 0x7f;
	x1 = P1;
	x2 = x1&0x7f;
	if(x2 != 0x7f)
	{
		switch(x1)
		{
			case 0x77:
				martrixkeyscan_out_1 = 1;
				break;
			case 0x7b:
				martrixkeyscan_out_1 = 2;
					break;
			case 0x7d:
				martrixkeyscan_out_1 = 3;
				break;
			case 0x7e:
				martrixkeyscan_out_1 = 13;
				break;
		}
		while(x1 != 0x7f)
		{
			P1 = 0x7f;
			x1 = P1;
		}
	}
	
	P1 = 0xbf;
	x1 = P1;
	x2 = x1&0xbf;
	if(x2 != 0xbf)
	{
		switch(x1)
		{
			case 0xb7:
				martrixkeyscan_out_1 = 4;
				break;
			case 0xbb:
				martrixkeyscan_out_1 = 5;
					break;
			case 0xbd:
				martrixkeyscan_out_1 = 6;
				break;
			case 0xbe:
				martrixkeyscan_out_1 = 14;
				break;
		}
		while(x1 != 0xbf)
		{
			P1 = 0xbf;
			x1 = P1;
		}
	}
	
	P1 = 0xdf;
	x1 = P1;
	x2 = x1&0xdf;
	if(x2 != 0xdf)
	{
		switch(x1)
		{
			case 0xd7:
				martrixkeyscan_out_1 = 7;
				break;
			case 0xdb:
				martrixkeyscan_out_1 = 8;
					break;
			case 0xdd:
				martrixkeyscan_out_1 = 9;
				break;
			case 0xde:
				martrixkeyscan_out_1 = 15;
				break;
		}
		while(x1 != 0xdf)
		{
			P1 = 0xdf;
			x1 = P1;
		}
	}
	
	P1 = 0xef;
	x1 = P1;
	x2 = x1&0xef;
	if(x2 != 0xef)
	{
		switch(x1)
		{
			case 0xe7:
				martrixkeyscan_out_1 = 11;
				break;
			case 0xeb:
				martrixkeyscan_out_1 = 0;
					break;
			case 0xed:
				martrixkeyscan_out_1 = 12;
				break;
			case 0xee:
				martrixkeyscan_out_1 = 16;
				break;
		}
		while(x1 != 0xef)
		{
			P1 = 0xef;
			x1 = P1;
		}
	}
	if(martrixkeyscan_out_2 != martrixkeyscan_out_1)
	{
		martrixkeyscan_out_2 = martrixkeyscan_out_1;
		martrixkeyscan_out_1 = 88;
		martrixkeyscan_x_1 = 1;
	}
	
}
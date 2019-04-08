#define uchar unsigned char
#define uint unsigned int

uchar key = 0;	//按下按键的编号
uchar key_1 = 0;
/*完成一次扫描后为1，置0后开始下一次扫描*/

void keyscan();	//独立键盘扫描
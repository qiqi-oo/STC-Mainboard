#include	"delay.h"
#include	"GPIO.h"
#include  <string.h>
#include <stdio.h>
#include "intrins.h"
#include <ctype.h>
//========================================================================
// 函数: void  delay_ms(unsigned char ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void  delay_ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 13000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}
//========================================================================
//void Delay50ms()		//@11.0592MHz
//void Delay100ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;

//	_nop_();
//	_nop_();
//	i = 3;
//	j = 26;
//	k = 223;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//========================================================================
//void Delay500us()		//@11.0592MHz
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 7;
	j = 113;
	do
	{
		while ((--j)&&(jiaosha_ztbh()==0));
	} while ((--i)&&(jiaosha_ztbh()==0));
}
//========================================================================
void delay(unsigned int k)
{
while(k--);
}
//========================================================================

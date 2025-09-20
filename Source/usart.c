#include "./User/includes.h"
#include <stdio.h>
#include <string.h>

#ifdef  STC12C5A60S2	
xdata MessageQueue  Msg_RX[2];
xdata u8 Msg_Rx1Buffer[Q_BUF_LENTH];			//缓存区
xdata u8 Msg_Rx2Buffer[Q_BUF_LENTH];			//缓存区
#endif

#ifdef  STC15W4K48S4	
xdata volatile MessageQueue  Msg_RX[4];
//为节约内存，做预编译处理，仅将GPS的串口缓存分配512字节，其他为128个字节
xdata u8 Msg_Rx1Buffer[Q_GPS_BUF_LENTH];	//缓存区
xdata u8 Msg_Rx2Buffer[Q_BUF_LENTH];			//缓存区
xdata u8 Msg_Rx3Buffer[Q_BUF_LENTH];			//缓存区
xdata u8 Msg_Rx4Buffer[Q_BUF_LENTH];			//缓存区	
#endif

//========================================================================
// 函数: u8	USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx)
// 描述: 初始化MCU的UART口.
// 参数: COMx_InitDefine: 结构参数,请参考uart.h里的定义.
// 返回: 无
// 版本: V1.0, 2022-10-17
//========================================================================
void USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx)
{
	unsigned char	i=0;
	if(UARTx == USART1)
	{
		Msg_RX[UARTx-1].pStart 	= 	Msg_Rx1Buffer;																//缓存区开始地址
		Msg_RX[UARTx-1].pEnd		= 	Msg_Rx1Buffer + sizeof(Msg_Rx1Buffer) - 1;		//缓存区结束地址
		Msg_RX[UARTx-1].pOut		= 	Msg_RX[UARTx-1].pStart;												//数据出口指针
		Msg_RX[UARTx-1].pIn			= 	Msg_RX[UARTx-1].pStart;	//数据入口指针	
		Msg_RX[UARTx-1].overflow_flag = 0;//缓存溢出标志
		memset(Msg_Rx1Buffer,0,sizeof(Msg_Rx1Buffer));
		if(COMx->UART_BRT_Use == BRT_Timer1)
			{
					PCON &= 0x7F;		//波特率不倍速
					SCON = 0x50;		//8位数据,可变波特率
					AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
					AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
					TMOD &= 0x0F;		//清除定时器1模式位
					TMOD |= 0x20;		//设定定时器1为8位自动重装方式
					TL1 = 256-(MAIN_Fosc / 32) / COMx->UART_BaudRate;		//设定定时初值
					TH1 = 256-(MAIN_Fosc / 32) / COMx->UART_BaudRate;		//设定定时器重装值
					ET1 = 0;		//禁止定时器1中断
					TR1 = 1;		//启动定时器1
				  ES=COMx->UART_Interrupt;//中断允许
			}
		else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				#ifdef  STC15W4K48S4	
					SCON = 0x50;		//8位数据,可变波特率
					AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
					AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
					T2L = (u8)(65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate));
					T2H = (u8)((65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate))>>8);		//设定定时初值
					AUXR |= 0x10;		//启动定时器2
					ES=COMx->UART_Interrupt;//中断允许
				#endif
				
				#ifdef  STC12C5A60S2		
					PCON &= 0x7F;		//波特率不倍速
					SCON = 0x50;		//8位数据,可变波特率
					AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
					BRT = 256-(MAIN_Fosc / 32) / COMx->UART_BaudRate;		//设定独立波特率发生器重装值
					AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
					AUXR |= 0x10;		//启动独立波特率发生器
				  ES=COMx->UART_Interrupt;//中断允许
				#endif
			}

  }
	if(UARTx == USART2)
	{
		Msg_RX[UARTx-1].pStart 	= 	Msg_Rx2Buffer;																//缓存区开始地址
		Msg_RX[UARTx-1].pEnd		= 	Msg_Rx2Buffer + sizeof(Msg_Rx2Buffer) - 1;	//缓存区结束地址
		Msg_RX[UARTx-1].pOut		= 	Msg_RX[UARTx-1].pStart;																//数据出口指针
		Msg_RX[UARTx-1].pIn			= 	Msg_RX[UARTx-1].pStart;	//数据入口指针	
		Msg_RX[UARTx-1].overflow_flag = 0;//缓存溢出标志
		memset(Msg_Rx2Buffer,0,sizeof(Msg_Rx2Buffer));														//数据入口指针		

		#ifdef  STC15W4K48S4	
			S2CON = 0x50;		//8位数据,可变波特率
			AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
			T2L = (u8)(65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate));
			T2H = (u8)((65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate))>>8);		//设定定时初值
			AUXR |= 0x10;		//启动定时器2	
			IE2 |=COMx->UART_Interrupt;	//开串口2中断  ES2=1=COMx->UART_Interrupt;//中断允许
		#endif
		
		#ifdef  STC12C5A60S2		
			AUXR &= 0xF7;		//波特率不倍速
			S2CON = 0x50;		//8位数据,可变波特率
			AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
			BRT = 256-(MAIN_Fosc / 32) / COMx->UART_BaudRate;	//设定独立波特率发生器重装值
			AUXR |= 0x10;		//启动独立波特率发生器
			IE2 |=COMx->UART_Interrupt;	//开串口2中断  ES2=1=COMx->UART_Interrupt;//中断允许
		#endif
	}
	#ifdef  STC15W4K48S4	
	if(UARTx == USART3)
	{
		Msg_RX[UARTx-1].pStart 	= 	Msg_Rx3Buffer;																//缓存区开始地址
		Msg_RX[UARTx-1].pEnd		= 	Msg_Rx3Buffer + sizeof(Msg_Rx3Buffer) - 1;	//缓存区结束地址
		Msg_RX[UARTx-1].pOut		= 	Msg_RX[UARTx-1].pStart;																//数据出口指针
		Msg_RX[UARTx-1].pIn			= 	Msg_RX[UARTx-1].pStart;	//数据入口指针	
		Msg_RX[UARTx-1].overflow_flag = 0;//缓存溢出标志
		memset(Msg_Rx3Buffer,0,sizeof(Msg_Rx3Buffer));														//数据入口指针	
		if(COMx->UART_BRT_Use == BRT_Timer2)
		{
			S3CON = 0x10;		//8位数据,可变波特率
			S3CON &= 0xBF;		//串口3选择定时器2为波特率发生器
			AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
			T2L = (u8)(65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate));
			T2H = (u8)((65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate))>>8);		//设定定时初值
			AUXR |= 0x10;		//启动定时器2
			IE2 |= (COMx->UART_Interrupt << 3);//中断允许
		}
		else if(COMx->UART_BRT_Use == BRT_Timer3)
		{
			S3CON = 0x10;		//8位数据,可变波特率
			S3CON |= 0x40;		//串口3选择定时器3为波特率发生器
			T4T3M |= 0x02;		//定时器3时钟为Fosc,即1T
			T3L = (u8)(65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate));
			T3H = (u8)((65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate))>>8);		//设定定时初值
			T4T3M |= 0x08;		//启动定时器3	
			IE2 |= (COMx->UART_Interrupt << 3);//中断允许			
		}
	
	}
	if(UARTx == USART4)
	{
		Msg_RX[UARTx-1].pStart 	= 	Msg_Rx4Buffer;																//缓存区开始地址
		Msg_RX[UARTx-1].pEnd		= 	Msg_Rx4Buffer + sizeof(Msg_Rx4Buffer) - 1;		//缓存区结束地址
		Msg_RX[UARTx-1].pOut		= 	Msg_RX[UARTx-1].pStart;												//数据出口指针
		Msg_RX[UARTx-1].pIn			= 	Msg_RX[UARTx-1].pStart;												//数据入口指针	
		Msg_RX[UARTx-1].overflow_flag = 0;																				//缓存溢出标志
		memset(Msg_Rx4Buffer,0,sizeof(Msg_Rx4Buffer));														//数据入口指针	
		if(COMx->UART_BRT_Use == BRT_Timer2)
		{
			S4CON = 0x10;		//8位数据,可变波特率
			S4CON &= 0xBF;		//串口4选择定时器2为波特率发生器
			AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
			T2L = (u8)(65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate));
			T2H = (u8)((65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate))>>8);		//设定定时初值
			AUXR |= 0x10;		//启动定时器2
			IE2 |= (COMx->UART_Interrupt << 4);//中断允许	
		}
		else if(COMx->UART_BRT_Use == BRT_Timer4)
		{
			S4CON = 0x10;		//8位数据,可变波特率
			S4CON |= 0x40;		//串口4选择定时器4为波特率发生器
			T4T3M |= 0x20;		//定时器4时钟为Fosc,即1T
			T4L = (u8)(65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate));
			T4H = (u8)((65535UL - ((MAIN_Fosc / 4) / COMx->UART_BaudRate))>>8);		//设定定时初值	
			T4T3M |= 0x80;		//启动定时器4	
			IE2 |= (COMx->UART_Interrupt << 4);//中断允许		
		}	
	}
	#endif
	
}
/*******************************************************************************/
void int_4(void) interrupt 4 //串口1中断
{
	if(RI==1)
	{ 
		RI=0;
	  if((Msg_RX[0].pIn >= Msg_RX[0].pOut) && (Msg_RX[0].overflow_flag == 1))
		{

			Msg_RX[0].pIn = Msg_RX[0].pStart;
			Msg_RX[0].pOut = Msg_RX[0].pStart;
			Msg_RX[0].overflow_flag = 0;	
		}
		if(Msg_RX[0].pIn == Msg_RX[0].pEnd)		//处理边界
		{
			*Msg_RX[0].pIn 	= SBUF;						//数据入队	
			Msg_RX[0].pIn 	= Msg_RX[0].pStart;	//循环到初始位置
			Msg_RX[0].overflow_flag = 1;			//已经经过边界
		}
		else 
		{
			*Msg_RX[0].pIn++ = SBUF;
		}

	}
}
/*****************************************************************************/
void int_8(void) interrupt 8 //串口2中断
{
	if(S2CON&0x01)  //S2RI=1
	{
		S2CON&=0xfe; 
	  if((Msg_RX[1].pIn == Msg_RX[1].pOut) && (Msg_RX[1].overflow_flag == 1))//队列溢出
		{
			Msg_RX[1].pIn = Msg_RX[1].pStart;
			Msg_RX[1].pOut = Msg_RX[1].pStart;
			Msg_RX[1].overflow_flag = 0;	
		}
    if(Msg_RX[1].pIn == Msg_RX[1].pEnd)		//处理边界
		{
			*Msg_RX[1].pIn 	= S2BUF;						//数据入队	
			Msg_RX[1].pIn 	= Msg_RX[1].pStart;	//循环到初始位置
			Msg_RX[1].overflow_flag = 1;			//已经经过边界
		}
		else 
		{
			*Msg_RX[1].pIn++ = S2BUF;	
		}
	}
	
}

#ifdef  STC15W4K48S4	
//========================================================================
//描述: 串口3中断
//========================================================================
void UART3_int (void) interrupt UART3_VECTOR //串口中断3
{
	if(RI3) 
	{
		CLR_RI3(); 
	  if((Msg_RX[2].pIn == Msg_RX[2].pOut) && (Msg_RX[2].overflow_flag == 1))//队列溢出
		{
			Msg_RX[2].pIn = Msg_RX[2].pStart;
			Msg_RX[2].pOut = Msg_RX[2].pStart;
			Msg_RX[2].overflow_flag = 0;	
		}
    if(Msg_RX[2].pIn == Msg_RX[2].pEnd)		//处理边界
		{
			*Msg_RX[2].pIn 	= S3BUF;						//数据入队	
			Msg_RX[2].pIn 	= Msg_RX[2].pStart;	//循环到初始位置
			Msg_RX[2].overflow_flag = 1;			//已经经过边界
		}
		else 
		{
			*Msg_RX[2].pIn++ = S3BUF;	
		}
	}
	
}
#endif
#ifdef  STC15W4K48S4	
//========================================================================
//描述: 串口4中断
//========================================================================
void UART4_int (void) interrupt UART4_VECTOR //串口中断4
{
	if(RI4) 
	{		
		CLR_RI4();
	  if((Msg_RX[3].pIn == Msg_RX[3].pOut) && (Msg_RX[3].overflow_flag == 1))//队列溢出
		{
			Msg_RX[3].pIn = Msg_RX[3].pStart;
			Msg_RX[3].pOut = Msg_RX[3].pStart;
			Msg_RX[3].overflow_flag = 0;	
		}
    if(Msg_RX[3].pIn == Msg_RX[3].pEnd)		//处理边界
		{
			*Msg_RX[3].pIn 	= S4BUF;						//数据入队	
			Msg_RX[3].pIn 	= Msg_RX[3].pStart;	//循环到初始位置
			Msg_RX[3].overflow_flag = 1;			//已经经过边界
		}
		else 
		{
			*Msg_RX[3].pIn++ = S4BUF;	
		}
	}
	
}
#endif
//========================================================================
// 函数: u8	USART_ReadRxBuffer(u8 UARTx，u8 *pbuffer,u16 *lenth)
// 描述: 读取串口的缓存数据到指定的内存块
// 参数: u8 UARTx需要读的端口号，u8 *pbuffer内存块的地址，u16 Buflenth为缓存区的大小.
// 返回: 返回读取数据的长度
// 版本: V1.0, 2022-10-17
//========================================================================
u16 USART_ReadRxBuffer(u8 UARTx, u8 *pbuffer, u16 Buflenth)
{
	u8 *pIn 	= 	Msg_RX[UARTx-1].pIn;
	u8 *pOut 	= 	Msg_RX[UARTx-1].pOut;
	xdata u16 lenth = 0;
	xdata u8 *ptemp = pbuffer;

	while(pOut != pIn)        	//1次读取所有的缓存
	{
		lenth++;	//记录读出的数据长度	
		if (lenth < Buflenth)						//判断数组是否越界
		{	   
				if(pOut == Msg_RX[UARTx-1].pEnd)	//处理边界
				{
						*pbuffer++ = *pOut;		//数据出队				
							pOut		 = Msg_RX[UARTx-1].pStart;//循环到初始位置
						Msg_RX[UARTx-1].overflow_flag = 0;		//溢出标志清0
				}
				else 
				{			  
						*pbuffer++ = *pOut++;	//数据出队 
				}
			#ifdef DEBUG
				printf("RxBuffer[%bd] = %b02x",(u8)(lenth-1),*(pbuffer-1));	
				printf("\r\n");
			#endif
		}
		else					//缓存数组越界
		{
			#ifdef DEBUG
			printf("USART_ReadRxBuffer:Index overflow!!!\r\n");	
			#endif		
			break;//退出，不再拷贝
		}
	}
	Msg_RX[UARTx-1].pOut = pIn; //将数据出口位置移到入口位置，准备进行下一轮读取
	return lenth;
		
}


//========================================================================
// 函数: void USART_CloseInterrupt(u8 UARTx)
// 描述: 关闭串口中断
// 参数: u8 UARTx需要关闭的串口号
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
void USART_CloseInterrupt(u8 UARTx)
{
			switch(UARTx)
			{
				case USART1:
										ES = 0;//关闭中断
										break;
				case USART2:
										IE2 &= ~(1<< 0);//关闭中断
										break;
#ifdef  STC15W4K48S4	
				case USART3:
										IE2 &= ~(1<< 3);//关闭中断
										break;
				case USART4:
										IE2 &= ~(1<< 4);//关闭中断
										break;
#endif
				default:
										return;
			}	
}

//========================================================================
// 函数: void USART_OpenInterrupt(u8 UARTx)
// 描述: 开启串口中断
// 参数: u8 UARTx需要开启的串口号
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
void USART_OpenInterrupt(u8 UARTx)
{
			switch(UARTx)
			{
				case USART1:
										ES = 1;//开启中断
										break;
				case USART2:
										IE2 |=(1<< 0);//开启中断
										break;
#ifdef  STC15W4K48S4
				case USART3:
										IE2 |= (1<< 3);//开启中断
										break;
				case USART4:
										IE2 |= (1<< 4);//开启中断
										break;
				default:
										return;
#endif
			}
}
//========================================================================
// 函数: void USART_ClearMsgQueueRxBuffer(u8 UARTx)
// 描述: 清理串口缓存数据
// 参数: u8 UARTx需要清理的串口号
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
void USART_ClearMsgQueueRxBuffer(u8 UARTx)
{
			u16 Bufferlenth = 0;
	
	    if(UARTx != DISABLE)
			{
	
				USART_CloseInterrupt(UARTx);//关闭中断

				Bufferlenth = Msg_RX[UARTx-1].pEnd - Msg_RX[UARTx-1].pStart +1;//计算缓存区的长度
		
				memset(Msg_RX[UARTx-1].pStart,0,Bufferlenth);//清理缓存
		
				Msg_RX[UARTx-1].pIn = Msg_RX[UARTx-1].pStart;//复位数据入口指针
		
				Msg_RX[UARTx-1].pOut = Msg_RX[UARTx-1].pStart;//复位数据出口指针
		
				Msg_RX[UARTx-1].overflow_flag = 0;//溢出标志清零
		
				USART_OpenInterrupt(UARTx);//开启中断
			}
	
		
}

#ifndef __USART_H
#define __USART_H	 


#ifdef  STC15W4K48S4
	#define	Q_BUF_LENTH					150 //消息队列的缓存空间大小
	#define	Q_GPS_BUF_LENTH			500
#endif

#ifdef  STC12C5A60S2
	#define	Q_BUF_LENTH	32 //消息队列的缓存空间大小
	#define	USARTMAX	3
#endif

	


#define	USART1	1
#define	USART2	2

#ifdef  STC15W4K48S4
	#define	USART3	3
	#define	USART4	4
	#define	USARTMAX	5
#endif



#define	UART_ShiftRight	0				//同步移位输出
#define	UART_8bit_BRTx	(1<<6)	//8位数据,可变波特率
#define	UART_9bit				(2<<6)	//9位数据,固定波特率
#define	UART_9bit_BRTx	(3<<6)	//9位数据,可变波特率

#define	BRT_Timer1	1
#define	BRT_Timer2	2

#ifdef  STC15W4K48S4
	#define	BRT_Timer3	3
	#define	BRT_Timer4	4
#endif


	
typedef struct
{ 	
	unsigned char	*pStart;								//缓存区开始地址
	unsigned char	*pEnd;									//缓存区结束地址
	unsigned char *pOut;									//数据出口指针
	unsigned char	*pIn;										//数据入口指针
	unsigned char	overflow_flag;  				//溢出标志
	//unsigned char	buffer[Q_BUFFER_LENTH];	//缓存区
}MessageQueue; 


typedef struct
{ 
	unsigned char	UART_Mode;			//模式,            UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	unsigned char	UART_BRT_Use;		//使用波特率发生器 BRT_Timer1,BRT_Timer2
	unsigned long UART_BaudRate;		//波特率,        ENABLE,DISABLE
	unsigned char	UART_RxEnable;		//允许接收,      ENABLE,DISABLE
	unsigned char	BaudRateDouble;		//波特率加倍,    ENABLE,DISABLE
	unsigned char	UART_Interrupt;		//中断控制,      ENABLE,DISABLE
	unsigned char	UART_Polity;		  //优先级,        PolityLow,PolityHigh
}COMx_InitDefine; 


	

	
void USART_Configuration(unsigned char UARTx, COMx_InitDefine *COMx);
u16 USART_ReadRxBuffer(u8 UARTx, u8 *pbuffer, u16 Buflenth);
void USART_ClearMsgQueueRxBuffer(u8 UARTx);
void USART_CloseInterrupt(u8 UARTx);
void USART_OpenInterrupt(u8 UARTx);
	
	
#endif


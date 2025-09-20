#ifndef	__BSP_USART_H
#define	__BSP_USART_H





#ifdef  STC12C5A60S2	
	#define	COM_Rx_LENTH	32
#endif

#ifdef  STC15W4K48S4	
	#define	COM_Rx_LENTH	160
	#define	GPS_Rx_LENTH	512
#endif


typedef struct
{ 	
	u8	*pStart;								//缓存区开始地址
	u8	*pEnd;									//缓存区结束地址
	u8	*pIn;										//数据入口指针
	u8	overflow_flag;  				//溢出标志
	
}UsartRxTypeDef;
//#ifdef  STC15W4K48S4	
//typedef struct
//{ 	
//	u8  USART;								//缓存区端口号
//	u8 *pRxBuffer;						//数据读入缓存区的内存地址
//	u16 Rxlenth;							//数据读入缓存区的内存地址长度
//	u8 *cutstr;								//切割目标字符串，如“$”,55,aa等
//	u8 cutlenth;							//切割目标字符串的长度
//  u8 checksum;            	//是否计算校验和
//}FormatRxBufferTypeDef;
//#endif


typedef struct 
{ 
	u8 com;  		//串口号
	u8 bote;  	//波特率
	u8 remap;    //映射模式

}UsartConfTypeDef;  //震动传感器

void USART_SendData(u8 USARTx,u8 ch);
void USART_Sendbuffer(u8 USARTx,const u8 *ch, u16 lenth);
void BSP_Usart_Init(unsigned char USARTx,unsigned long bote); //串口初始化函数
u16 BSP_GetUsartRxBuffer(u8 USARTx,u8 *RxBuffer,u16 Rxlenth);
void BSP_ClearUsartRxBuffer(u8 USARTx);
void printf_buffer(const char *name,const u8 *pbuffer,u16 lenth);
u16 BSP_GetFormatRxBuffer(u8 USARTx,u8 *pRxBuffer,u16 Rxlenth,u8 *cutstr,u8 cutlenth);

#ifdef  STC15W4K48S4	
void HextoStr(const u8 *pbuffer,u8 *pStr,u16 lenth);
#endif


#endif
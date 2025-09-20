#include "./User/includes.h"
#include <stdio.h>
#include <string.h>


	
#ifdef  STC12C5A60S2	
	xdata UsartRxTypeDef Rx[2];	
	xdata u8 Rx1_Buffer[COM_Rx_LENTH];
	xdata u8 Rx2_Buffer[COM_Rx_LENTH];
#endif


#ifdef  STC15W4K48S4	
	xdata UsartRxTypeDef Rx[4];	
	xdata u8 Rx1_Buffer[GPS_Rx_LENTH];
	xdata u8 Rx2_Buffer[COM_Rx_LENTH];
	xdata u8 Rx3_Buffer[COM_Rx_LENTH];
	xdata u8 Rx4_Buffer[COM_Rx_LENTH];
		
#endif
//========================================================================
// 函数:char putchar(char ch) printf重定向函数
// 描述:printf重定向到usart1
// 参数：
// 版本: 
//========================================================================
char putchar(char ch)  //函数默认的，在使用printf函数时自动调用
{
	#ifdef  STC15W4K48S4
		USART_SendData(NETWORK_USART,(char)ch);
	#endif
	
	#ifdef  STC12C5A60S2	
	  USART_SendData(CONSOLE_USART,(char)ch);
	#endif
	return ch;
}
//========================================================================
// 函数:BSP_Usart_Init(unsigned char USARTx,unsigned long bote)
// 描述: 初始化串口
// 参数：USARTx端口号，bote波特率
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_Usart_Init(unsigned char USARTx,unsigned long bote)
{
	COMx_InitDefine		COMx_InitStructure;					        //结构定义
	
	if(USARTx == USART1)
	{	
		Rx[USARTx-1].pStart = Rx1_Buffer;
		Rx[USARTx-1].pEnd	 = (u8 *)(Rx1_Buffer + sizeof(Rx1_Buffer) -1);
		Rx[USARTx-1].pIn 	 = Rx[USARTx-1].pStart;
		Rx[USARTx-1].overflow_flag = 0;
		memset(Rx1_Buffer,0,sizeof(Rx1_Buffer));
		
		COMx_InitStructure.UART_BRT_Use   = BRT_Timer1;			  //使用波特率发生器,   BRT_Timer1, BRT_Timer2 
	}
	else if(USARTx == USART2)
	{
		Rx[USARTx-1].pStart = Rx2_Buffer;
		Rx[USARTx-1].pEnd	 = Rx2_Buffer + sizeof(Rx2_Buffer) -1;
		Rx[USARTx-1].pIn 	 = Rx[USARTx-1].pStart;
		Rx[USARTx-1].overflow_flag = 0;
		memset(Rx2_Buffer,0,sizeof(Rx2_Buffer));
		
		COMx_InitStructure.UART_BRT_Use   = BRT_Timer2;			  //使用波特率发生器,   BRT_Timer2 (注意: 串口2固定使用BRT_Timer2)
	}
#ifdef  STC15W4K48S4	
	else if(USARTx == USART3)
	{
		Rx[USARTx-1].pStart = Rx3_Buffer;
		Rx[USARTx-1].pEnd	 = Rx3_Buffer + sizeof(Rx3_Buffer) -1;
		Rx[USARTx-1].pIn 	 = Rx[USARTx-1].pStart;
		Rx[USARTx-1].overflow_flag = 0;
		memset(Rx3_Buffer,0,sizeof(Rx3_Buffer));
		
		COMx_InitStructure.UART_BRT_Use   = BRT_Timer3;			  //使用波特率发生器,   BRT_Timer2, BRT_Timer3 
	}
	else if(USARTx == USART4)
	{
		Rx[USARTx-1].pStart = Rx4_Buffer;
		Rx[USARTx-1].pEnd	 = Rx4_Buffer + sizeof(Rx4_Buffer) -1;
		Rx[USARTx-1].pIn 	 = Rx[USARTx-1].pStart;
		Rx[USARTx-1].overflow_flag = 0;
		memset(Rx4_Buffer,0,sizeof(Rx4_Buffer));
		
		COMx_InitStructure.UART_BRT_Use   = BRT_Timer4;			  //使用波特率发生器,   BRT_Timer2, BRT_Timer4 
	}
#endif
	else 
	{
		return;
	}
	if(bote == DISABLE)  return;													//检查波特率，为DISABLE时，不初始化该串口
	COMx_InitStructure.UART_BaudRate  = bote;		   	      //波特率, 一般 110 ~ 115200
	COMx_InitStructure.UART_Interrupt = ENABLE;				    //中断允许,   ENABLE或DISABLE
	USART_Configuration(USARTx, &COMx_InitStructure);		  //初始化串口1 USART1,USART2
}
//========================================================================
// 函数:u16 BSP_GetUsartRxBuffer(u8 USARTx,u8 *RxBuffer,u16 *lenth)
// 描述: 读取串口缓存中的数据，续写，如协议匹配成功，lenth需软件清零
// 参数：u8 USARTx为端口号，RxBuffer缓存区指针,缓存区的长度
// 返回：读取的数据长度
// 版本: V1.0, 2022-10-17
//========================================================================
u16 BSP_GetUsartRxBuffer(u8 USARTx,u8 *pRxBuffer,u16 Rxlenth)
{
	xdata u16 remaindlen = 0;		//数组剩余空间大小，检验溢出时使用
	xdata u16 lenth = 0;				//缓存去数据长度
	xdata u16 i = 0;
	
	
	if((USARTx == DISABLE) || (USARTx >= USARTMAX)) //硬件串口未初始化
	{	
		return 0;//返回0
	}
	//printf("BSP_GetUsartRxBuffer:USARTx = %b02d\r\n",USARTx);
	
	remaindlen = (u16)(Rx[USARTx-1].pEnd - Rx[USARTx-1].pIn) + 1;//计算剩余空间大小
	
	lenth = USART_ReadRxBuffer(USARTx,Rx[USARTx-1].pIn,remaindlen);//读取串口接收的缓存数据
	
	Rx[USARTx-1].pIn = (u8 *)(Rx[USARTx-1].pIn + lenth);//将指针移动到下一次需要写入数据的位置
	
	lenth = (u16)(Rx[USARTx-1].pIn - Rx[USARTx-1].pStart); //数据长度接续
	
	if(Rx[USARTx-1].pIn >= Rx[USARTx-1].pEnd) //检查数组是否越界
	{
	
		BSP_ClearUsartRxBuffer(USARTx);//软件自动清空缓存区域

		printf("BSP_GetUsartRxBuffer:Index overflow!!!  USARTx = %b02d\r\n",USARTx);
		
		#ifdef DEBUG
		printf("BSP_GetUsartRxBuffer:Index overflow!!!  USARTx = %b02d\r\n",USARTx);	
		#endif	
		
		lenth = 0;//软件自动清空缓存区域
	}

	if(lenth >= Rxlenth)//数据内容超过了需要写的缓存空间了
	{
		lenth = Rxlenth;	//截断数据
		
		printf("Rxlenth:Index overflow!!!  USARTx = %b02d\r\n",USARTx);
		
		for (i = 0;i < Rxlenth; i++) //数据拷贝
		{
			*pRxBuffer++ = *(Rx[USARTx-1].pStart+i);	
		}
		BSP_ClearUsartRxBuffer(USARTx);//软件自动清空缓存区域
	}
	else
	{
		for (i = 0;i < lenth; i++) //数据拷贝
		{
			*pRxBuffer++ = *(Rx[USARTx-1].pStart+i);	
		}
		
	}
	
	*pRxBuffer = '\0';				 //仅用于后续字符串处理时作为结束符号使用
	
	return lenth;
	
}
#ifdef  STC15W4K48S4
//========================================================================
// 函数:u16 BSP_GetFormatRxBuffer(u8 USARTx,u8 *RxBuffer,u16 *lenth,u8 *cutstr)
// 描述: 获取串口缓存中的数据，按照cutstr进行切割读取.
// 参数：u8 USARTx为端口号，RxBuffer缓存区指针,Rxlenth缓存区的长度,u8 以*cutstr作为切割字符串 cutlenth,是切割字符的长度
// 返回：读取的数据长度
// 版本: V1.0, 2022-10-17
//========================================================================
u16 BSP_GetFormatRxBuffer(u8 USARTx,u8 *pRxBuffer,u16 Rxlenth,u8 *cutstr,u8 cutlenth)
{
	xdata u16 lenth = 0;					//缓存数据长度
	xdata u8  *pTemp     = NULL;
	xdata u8  *pStart    = NULL;
	xdata u8  *pcutstr    = NULL;
	xdata u8  i  = 0;

	
	if((USARTx == DISABLE) || (USARTx >= USARTMAX)) //硬件串口未初始化
	{	
		return 0;//返回0
	}
	
	lenth = BSP_GetUsartRxBuffer(USARTx,pRxBuffer,Rxlenth);//读取缓存数据
	
	pcutstr = ByteArrayCompar_r(pRxBuffer,lenth,cutstr,cutlenth);//找到切割字符串的位置，从后往前找。
	
	if(pcutstr == NULL)//未查询到切割字符
	{
		memset(pRxBuffer,0,Rxlenth);//清空缓存数据
		
		//printf("BSP_GetFormatRxBuffer lenth = %h04d\r\n",lenth);
		
		lenth = 0;//读取长度为0
		
		
		return lenth;//返回0
	}
	//处理缓存区pRxBuffer的数据
	if(*(cutstr+cutlenth-1) == '\n')//如果有换行符并且是末尾切分
	{
		//printf("BSP_GetFormatRxBuffer lenth = %h04d\r\n",lenth);
		
		pcutstr = (u8 *)(pcutstr +1);//跳过切割字符
		
	}
  lenth = (u16)(pcutstr - pRxBuffer);//数据长度，返回给调用者
	
	memset(pcutstr,0,(u16)(Rxlenth - lenth));//清除多余的数据，返回给调用者
	
	//处理缓存区Rx的数据
	pStart = Rx[USARTx-1].pStart;
	
	pTemp = (u8 *)(pStart + lenth);
	
	while (pTemp  < Rx[USARTx-1].pIn)
	{
			*pStart++ = *pTemp++;    //将剩下的数据移到缓存区的首地址	
	}
	memset(pStart,0,(u16)(Rx[USARTx-1].pEnd - pStart +1));//清除后续缓存
	
	Rx[USARTx-1].pIn = pStart;
	
	return lenth;
}
#endif
//========================================================================
// 函数:void BSP_ClearUsartRxBuffer(u8 USARTx)
// 描述: 清理串口缓存数据
// 参数：u8 USARTx为端口号
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_ClearUsartRxBuffer(u8 USARTx)
{
	xdata u16 lenth = 0;

	if((USARTx == DISABLE) || (USARTx >= USARTMAX))  return;//硬件串口未开启
	
	lenth = (u16)(Rx[USARTx-1].pEnd - Rx[USARTx-1].pStart + 1);//计算缓存区的总长度
	
  memset(Rx[USARTx-1].pStart, 0,lenth);//缓存区清零
	
	Rx[USARTx-1].pIn = Rx[USARTx-1].pStart;		//指向缓存区首地址
	
	 #ifdef DEBUG
		printf("Rx[%b02d]Clear,OK!\r\n",(USARTx-1));
	 #endif
}
//========================================================================
// 函数:WaitForTISignal(u8 USARTx)
// 描述: 等待串口数据发送完成，阻塞模式
// 参数：u8 USARTx串口号
// 版本: V1.0, 2022-10-17
//========================================================================
static void WaitForTISignal(u8 USARTx)
{
	if(USARTx == USART1)
	{
		while(TI == 0); 
		TI = 0;
	}
	else if(USARTx == USART2)
	{
		while((S2CON & 2) == 0); 
		S2CON &= ~2;
	}
	#ifdef  STC15W4K48S4
	else if(USARTx == USART3)
	{
		while(TI3 ==0);
		CLR_TI3();
	}
	else if(USARTx == USART4)
	{
		while(TI4==0);
		CLR_TI4();   
	}
	#endif
	else 
	{
		return;
	}
}
//========================================================================
// 函数:void USART_SendData(u8 USARTx,u8 ch)
// 描述: 串口数据发送模式，查询方式
// 参数：u8 USARTx串口号,u8 ch需要发送的数据
// 版本: V1.0, 2022-10-17
//========================================================================
void USART_SendData(u8 USARTx,u8 ch)
{
	#ifdef  STC12C5A60S2
		P483 =1;//483发送状态
	  delay50us();
	#endif
	if((USARTx == DISABLE) || (USARTx >= USARTMAX)) //硬件串口未初始化
	{	
		return ;//直接返回
	}
	switch(USARTx)
	{
		case USART1:
								SBUF = ch;
								break;
		case USART2:
								S2BUF = ch;
								break;
#ifdef  STC15W4K48S4
		case USART3:
								S3BUF = ch;
								break;		
		case USART4:
								S4BUF = ch;
								break;	
#endif
		default:
								break;
		
	}
	WaitForTISignal(USARTx);//等待数据传输完成
	#ifdef  STC12C5A60S2
		P483 =0;//483接收状态
	  delay50us();
	#endif	
}
//========================================================================
// 函数:void USART_Sendbuffer(u8 USARTx,const u8 *ch, u16 lenth)
// 描述: 串口数据发送模式，查询方式
// 参数：u8 USARTx串口号,u8 ch需要发送的数据,lenth缓存区的长度
// 版本: V1.0, 2022-10-17
//========================================================================
void USART_Sendbuffer(u8 USARTx,const u8 *ch, u16 lenth)
{
	u16 i = 0;
	//printf("USART_Sendbuffer\r\n");
	for (i=0;i<lenth;i++)
	{
		USART_SendData(USARTx,*ch++);
	}
	
}

//========================================================================
// 函数:printf_buffer(const char *name,const u8 *pbuffer,u16 lenth)
// 描述: 格式化答应数组内容
// 参数：name为打印出来的数组名称,pbuffer为数组名称，lenth为打印数组前多少个元素
// 版本: V1.0, 2022-10-17
//========================================================================
#ifdef DEBUG1
void printf_buffer(const char *name,const u8 *pbuffer,u16 lenth)
{
	int i = 0;
	printf("%s:",name);
	for (i = 0; i < lenth; i++)
	{
		printf("%b02X",*pbuffer++);	
		printf(" ");			
	}
	printf("\r\n");
}
#endif
//========================================================================
// 函数:HextoStr(const u8 *pbuffer,char *pStr,u16 lenth)
// 描述: 将字符数组转换成字符串，
// 参数：pbuffer为字节数组名称，pStr需要保存字符串的地址，lenth为字节数组的长度
// 版本: V1.0, 2022-10-17
//========================================================================
#ifdef  STC15W4K48S4	
void HextoStr(const u8 *pbuffer,u8 *pStr,u16 lenth)
{
	u16 i = 0;
	char temp[3] = "";
	
	xdata u8 num=0x2D;	//字头“ZBSJ,”的ASCII异或值
	
	for (i = 0; i < lenth-1; i++)	//格式化到校验和前一位
	{
		sprintf(temp,"%b02X",*pbuffer++);
		strcat(pStr,temp);
		num^=temp[0];			//异或校验
		num^=temp[1];

	}
	
	strcat(pStr,"*");						//校验和定界符。为数据内容和校验和字段的分隔符。
	sprintf(temp,"%b02X",num);	//格式化异或校验和
	strcat(pStr,temp);					//追加校验和数据
	strcat(pStr,"\r\n");				//终止符（ASCII 码字符 HEX0D0A）。标志一个语句的结束。
	
/*
	校验和为语句中“$”和“*”之间(不含符号“$”和“*”)全部字符按字节异或的结果，
*/
}
#endif

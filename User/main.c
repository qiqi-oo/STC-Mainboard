#include	"./User/includes.h"
#include	"./User/config.h"
#include	<stdio.h>
#include	<string.h>

void main(void)
{
	
	GetFlashConfig();  //默认配置初始化
	
	BSP_Init();//板载硬件初始化,	
	
	Check_Serial_Id();	//校验单片机序列号
	
  while(1)	
	{ 
		
		#ifdef  STC15W4K48S4	
		SerialHandle(NETWORK_USART); //网口通讯处理程序
		#endif
		SerialHandle(DEBUG_USART);		//串口通讯处理程序	
		
		SerialHandle(UPLOAD_USART);		//串口通讯处理程序	
		
		SerialDataUpload(UPLOAD_USART);//给上位机上传数据
		
		#ifdef  STC12C5A60S2	
			delay_ms(200);
		#endif
		
		
		
		
	}	
}





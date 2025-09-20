/*#include <stdio.h>
#include <string.h>
#include	"./User/config.h"
#include 	"./User/includes.h"




#ifdef  STC15W4K48S4

xdata	u8 GpsRxBuffer[128]="";	//接收缓冲

u8 code CMD_GpsConfFail[]	=	{0x53,0x5A,0x43,0x47};//Gps配置失败指令
u8 code CMD_GpsConfSucc[]	=	{0x44,0x51,0x43,0x47,0x00};//Gps配置成功指令


char code  CMD_GpsAckSucc[]	=	"OK";//Gps配置成功指令

char code  CMD_BY_BaseAuto[] =	"fix auto\r\n";//自动获取基准站坐标
char code  CMD_BY_GetBasePos[] =	"log refstationa\r\n";//获取基准站坐标

char code  CMD_HX_BaseAuto[] =	"fix auto\r\n";//自动获取基准站坐标
char code  CMD_HX_GetBasePos[] =	"log bestposa\r\n";//获取基准站坐标


char code  CMD_ConfigEnd[] = "Configuration complete\r\n";//配置结束指令，用于程序的循环是否结束，与GPS配置无关，必须有！！
char code  CMD_BY_BaseStation[][CMD_GPS_LENTH] =         //北云GPS基准站指令
{
	"interfacemode com3 bynav bynav\r\n",//（配置端口的输入类型为bynav）
	"interfacemode com2 rtcm rtcm\r\n",//（配置端口输出类型为rtcm）
	"rtktype base\r\n",// //设置为基准站
	"fix auto\r\n",////自动获取基准站坐标
	"serialconfig com1 38400\r\n",//
	"serialconfig com2 38400\r\n",//
	"serialconfig com3 38400\r\n",//
	"log com2 rtcm1074 ontime 1\r\n",//
	"log com2 rtcm1084 ontime 1\r\n",//
	"log com2 rtcm1114 ontime 1\r\n",//
	"log com2 rtcm1124 ontime 1\r\n",//
	"log com2 rtcm1006 ontime 5\r\n",//
	"log com2 rtcm1033 ontime 10\r\n",//
	"unlogall com3\r\n",//
	"log com3 gpgga ontime 1\r\n",//
	"saveconfig\r\n",							//
	"reboot\r\n",									// //重启		
	"Configuration complete\r\n"	//配置结束指令，用于程序的循环是否结束，与GPS配置无关，必须有！！	
};

char code  CMD_BY_MobileStation[][CMD_GPS_LENTH] =         //北云GPS移动站配置指令
{
	"interfacemode com3 bynav bynav\r\n",//
	"unlogall\r\n",
	"interfacemode com2 rtcm rtcm\r\n",
	"rtktypertk rover\r\n",
	"interfacemode com3 bynav bynav\r\n",
	"serialconfig com2 38400\r\n",
	"serialconfig com3 38400\r\n",
	"serialconfig com1 38400\r\n",
	"log com3 ptnlpjk ontime 0.1\r\n",
	"log com3 gpvtg ontime 0.1\r\n",
	"log com3 ptnlavr ontime 0.1\r\n",
	"saveconfig\r\n",		
	"Configuration complete\r\n",	//配置结束指令，用于程序的循环是否结束，与GPS配置无关，必须有！！
};

char code  CMD_HX_BaseStation[][CMD_GPS_LENTH] =         //合芯GPS基准站指令
{
	"lmode base time 60 1.5 2.5\r\n",				//将GPS设置为基准站
	"fix auto\r\n",											//自动获取基准站坐标
	"unlog com3\r\n",								
	"log com2 rtcm1033 ontime 10\r\n",									
	"log com2 rtcm1006 ontime 10\r\n",//
	"log com2 rtcm1074 ontime 1\r\n",//
	"log com2 rtcm1084 ontime 1\r\n",//
	"log com2 rtcm1124 ontime 1\r\n",//
	"log com2 rtcm1094 ontime 1\r\n",//
	"config com2 38400\r\n",//
	"config com3 38400\r\n",//
	"saveconfig\r\n",//		
	"Configuration complete\r\n"	//配置结束指令，用于程序的循环是否结束，与GPS配置无关，必须有！！
};


char code  CMD_HX10Hz_MobileStation[][CMD_GPS_LENTH] =         //合芯GPS移动站指令
{
	"log headinga ontime 1\r\n",				//将GPS设置为基准站
	"com com2 38400\r\n",											//自动获取基准站坐标
	"com com3 38400\r\n",								
	"Unlogall com2\r\n",									
	"Unlogall com3\r\n",//
	"log com3 gpntr ontime 0.1\r\n",//
	"log com3 gptra onchanged\r\n",//
	"log com3 gpvtg ontime 0.1\r\n",//
	"log com3 gprmc ontime 0.1\r\n",//
	"Headingmode variablelength \r\n",//
	"mode rover\r\n",//
	"saveconfig\r\n",//		
	"Configuration complete\r\n"	//配置结束指令，用于程序的循环是否结束，与GPS配置无关，必须有！！	
};

char code  CMD_HX5Hz_MobileStation[][CMD_GPS_LENTH] =         //合芯GPS移动站指令
{
	"log headinga ontime 1\r\n",				//将GPS设置为基准站
	"com com2 38400\r\n",											//自动获取基准站坐标
	"com com3 38400\r\n",								
	"Unlogall com2\r\n",									
	"Unlogall com3\r\n",//
	"log com3 gpntr ontime 0.2\r\n",//
	"log com3 gptra onchanged\r\n",//
	"log com3 gpvtg ontime 0.2\r\n",//
	"log com3 gprmc ontime 0.2\r\n",//
	"Headingmode variablelength \r\n",//
	"mode rover\r\n",//
	"saveconfig\r\n",//		
	"Configuration complete\r\n"	//配置结束指令，用于程序的循环是否结束，与GPS配置无关，必须有！！	
};
//========================================================================
// 函数: u8 GPS_Configuration(u8 USARTx,char *dat)
// 描述: 配置gps，给gps发送指令，同时可根据指令返回差分站坐标
 //      连续尝试3次，不成功即配置失败
// 参数：u8 USARTx,配置串口，char *cmd 指向指令的地址
// 返回: 无
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 Configuration(u8 USARTx,char *cmd)	//配置GPS板卡
{
	xdata u8 i=0;
	xdata u8 times=3;
	
	//printf("GPS_Configuration\r\n");
	
	while (times--)
	{
		
		if (strcmp(cmd,CMD_HX_BaseAuto) == 0)  //fix auto\r\n与北云通用
		{
			delay_ms(3000); //延时3秒后，获取差分站的定位坐标
		}
		
		BSP_ClearUsartRxBuffer(USARTx);//清串口缓存
		
		USART_Sendbuffer(USARTx,cmd,strlen(cmd));//发送配置指令
		
		delay_ms(300);//延时350读取板卡回复
		
		memset(GpsRxBuffer, 0, sizeof(GpsRxBuffer));//清缓存数据
		
		BSP_GetUsartRxBuffer(USARTx,GpsRxBuffer,sizeof(GpsRxBuffer));//读取串口数据
					
		if(strstr((char *)GpsRxBuffer,CMD_GpsAckSucc) != NULL)  //Gps配置成功指令应答成功OK
		{
			if (strstr(cmd,"com3 38400") != NULL)	//改变串口波特率指令serialconfig com3 38400\r\n
			{
				BSP_Usart_Init(USARTx,38400); //波特率和GPS串口波特率同步
				S1_USE_P16P17();//STC切换串口1到GPS串口
			}
			return(1);//收到GPS正确的回复
		}
	}
	return(0);//未收到GPS正确的回复
}
//========================================================================
// 函数: void GPS_EnterConfig(u8 USARTx, char **pcmd)	//配置GPS
// 描述: 按照指令集合pcmd的指令配置GPS移动站，指令集合中最后一条指令必须是CMD_ConfigEnd
// 参数：u8 USARTx,配置串口,char (*pcmd)[CMD_GPS_LENTH]指向指令集合的指针
// 返回: 无
// 版本: V1.0, 2022-10-17
//========================================================================
static void EnterConfig(u8 USARTx, char (*pcmd)[CMD_GPS_LENTH])	
{
	xdata u8 Index = 0;//指令序号
	xdata u8 temp = 0;//
		
	S1_Int_on();//开串口1中断
	
	BSP_Usart_Init(USARTx,115200);//测试波特率
  S1_USE_P16P17();//STC切换串口1到GPS串口
	
	if(Configuration(USARTx,pcmd[Index]) == 0)//配置失败
	{
		 BSP_Usart_Init(USARTx,38400);//测试波特率
		 S1_USE_P16P17();//STC切换串口1到GPS串口
	}
	if(Configuration(USARTx,pcmd[Index]) == 0)//配置失败
	{
		 BSP_Usart_Init(USARTx,19200);//测试波特率
			S1_USE_P16P17();//STC切换串口1到GPS串口
	}
	if(Configuration(USARTx,pcmd[Index]) == 1)//波特率适配成功 
	{
		while(strstr(pcmd[Index],CMD_ConfigEnd) == NULL)//查询到配置完成指令，跳出循环，配置结束
		{
			
			//printf("Index = %b02d\r\n",Index);
			
			temp = Configuration(USARTx,pcmd[Index]);//发送配置指令
				
			if (temp == 0)//配置失败
			{
				USART_Sendbuffer(UPLOAD_USART,CMD_GpsConfFail,sizeof(CMD_GpsConfFail));//发送配置失败指令
				
				USART_SendData(UPLOAD_USART,Index);//发送错指令索引
				
				//printf("GpsConfFail :Index = %b02d\r\n",Index);
				
				return;//配置失败
			}
			
			Index ++;//移到下一个指令
						
		}
	}
  USART_Sendbuffer(USARTx,CMD_GpsConfSucc,sizeof(CMD_GpsConfSucc));//应答配置成功
	
	//printf("GpsConfSucc\r\n",Index);			
}	
//========================================================================
// 函数: void GetBaseStationPos(void)	
// 描述: 得到GPS基准站坐标，上传给上位机
// 参数：无
// 返回: 无
// 版本: V1.0, 2022-10-17
//========================================================================
void GetBaseStationPos(void)	
{
	xdata u8 i = 0 ;	//
	xdata u8 type = 0 ;//获取配置文件，得到gps类型
	BSP_ClearUsartRxBuffer(GPS_USART);//清串口缓存
	switch(type)
	{
		case BY_BASESTATION:
							USART_Sendbuffer(GPS_USART,CMD_BY_GetBasePos,strlen(CMD_BY_GetBasePos));//发送获取北云gps基准站坐标的指令	
		case HX_BASESTATION:
							USART_Sendbuffer(GPS_USART,CMD_BY_GetBasePos,strlen(CMD_BY_GetBasePos));//发送获取合芯gps基准站坐标的指令			
    default:
						break;
										
	}	
	delay_ms(300);
	
	memset(GpsRxBuffer, 0, sizeof(GpsRxBuffer));//清缓存数据
		
	BSP_GetUsartRxBuffer(GPS_USART,GpsRxBuffer,sizeof(GpsRxBuffer));//读取串口数据
		
	for(i=0;i<strlen((char *)GpsRxBuffer);i++)
	{		
		USART_SendData(UPLOAD_USART,GpsRxBuffer[i]);//回复基准站坐标
	}	 
	BSP_ClearUsartRxBuffer(GPS_USART);//清串口缓存											
}



//========================================================================
// 函数: void GPS_EnterConfiguration(void)	
// 描述: 进入GPS配置模式
// 参数：mode是指定差分站还是移动站，由上位机决定
// 返回: 无
// 版本: V1.0, 2022-10-17
//========================================================================
void GPS_EnterConfiguration(u8 mode)	
{
	
	if	(mode ==BASESTATION )
	{
			switch(GNSS_MODEL)
			{
				case BY_BASESTATION:
														EnterConfig(GPS_USART,CMD_BY_BaseStation);//进入北云GPS基准站配置
														break;
				case HX_BASESTATION:
														EnterConfig(GPS_USART,CMD_HX_BaseStation);//进入合芯GPS基准站配置
														break;		
				default:
								break;
			}
										
	}	
	if	(mode == MOBILESTATION)
	{
			switch(GNSS_MODEL)
			{
				case BY_MOBILESTATION:
														EnterConfig(GPS_USART,CMD_BY_MobileStation);			//进入北云GPS移动站配置
														break;
				case HX10HZ_MOBILESTATION:
														EnterConfig(GPS_USART,CMD_HX10Hz_MobileStation);	//进入合芯10HzGPS移动站配置
														break;		
				case HX5HZ_MOBILESTATION:
														EnterConfig(GPS_USART,CMD_HX5Hz_MobileStation);		//进入合芯5HzGPS移动站配置
														break;	
				default:
								break;
			}		
	}
		
									
}
#endif
*/

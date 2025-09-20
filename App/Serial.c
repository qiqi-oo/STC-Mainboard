#include <stdio.h>
#include <string.h>
#include	"./User/config.h"
#include 	"./User/includes.h"

#ifdef  STC12C5A60S2	
	#define	BUF_LENTH	32
#endif

#ifdef  STC15W4K48S4	
	
	#define	BUF_LENTH	520
	
	//#define	BUF_LENTH	512
	
	#define OBD_LENTH  (BASEBOARD_SIZE * 2 + 4)  //末尾增加* num /r/n共5个字符
		
	code  u8 OBDHandbuffer[]="$ZBSJ,";
	
  xdata u8 OBDstrbuffer[OBD_LENTH];
	
	
#endif

code  u8 Handbuffer[]={0x55,0xaa,0xfe,0x7c};

xdata u8 BaseBoardBuffer[BASEBOARD_SIZE];//保存主板传输给上位机的数据

xdata volatile u8 start = FALSE;//开始指令




xdata	u8 Buffer[BUF_LENTH];	//接收缓冲
//xdata	u8 CMD_Buffer[64];	//接收缓冲

u8 code CMD_RESET[]	=	"reset";					//单片机软复位指令

u8 code CMD_start[]	=	{0x55,0xaa,0x00,0x00,0x11,0x11};//开始采集指令
u8 code CMD_stop[]	=	{0x55,0xaa,0x00,0x00,0x00,0x00};//停止采集指令
u8 code CMD_writeflash[]	=	{0x55,0xaa,0x49,0x4f,0x58,0x47};//写flash
u8 code CMD_readflash[]		=	{0x55,0xaa,0x49,0x4f,0x44,0x51};//读flash
u8 code CMD_wflash_Ack[]	=	{0x58,0x47,0x43,0x47};					//写flash应答
u8 code CMD_rflash_Ack[]	=	{0x44,0x51,0x43,0x47};					//读flash应答

#ifdef  STC15W4K48S4
u8 code CMD_conf_gpssmobile[]	=	{0x55,0xAA,0x49,0x4F,0xff,0xff};	//配置gps移动站
u8 code CMD_conf_gpsbase[]		=	{0x55,0xAA,0x49,0x4F,0xff,0xfe};	//配置GPS基准站
u8 code CMD_get_gpsbasepos[]	=	{0x55,0xAA,0x49,0x4F,0xff,0xfc};	//获取GPS基准站坐标
#endif

#ifdef  STC15W4K48S4
//========================================================================
// 函数:void InsertBaseboardDstaUpload(u8 gps_usart,u8 upload_usart)
// 描述: 插入主板数据(vtg语句之前)并上传，如获取不到GPS数据，自动上传单主板数据
// 参数：u8 gps_usart为gps与主板的串口,u8 upload_usart上位机与主板的串号
// 版本: V1.0, 2022-10-17
//========================================================================
static void InsertBaseboardData(u8 gps_usart,u8 upload_usart)
{
	 static u8 timeout = 0;//连续5次读取不到VTG数据，自动上传单主板数据
	 xdata u8 *pvtg = NULL;
	 xdata u8 *pOut = (u8 *)Buffer;//指向数据的出口
	 xdata u16 lenth = 0;
	 xdata u8 cutstr[] ="\n";
	 xdata u8 i = 0;
   xdata u8 sum=0;	//OBD主板异或校验和
	 static u8 vtg_flag = 0;//连续5次读取不到VTG数据，自动上传单主板数据
	


	if(vtg_flag == 0)//出现vtg一次做采样1次
	{
			  vtg_flag = 1;
			
				memset(BaseBoardBuffer,0,sizeof(BaseBoardBuffer));	//清空主板数据缓存
			  GetBaseBoardDataPack(BaseBoardBuffer,sizeof(BaseBoardBuffer));//获取主板数据
	
				memset(OBDstrbuffer,0,sizeof(OBDstrbuffer));	//清空主板数据缓存
				HextoStr(BaseBoardBuffer,OBDstrbuffer,sizeof(BaseBoardBuffer));//数据转换	

	}	
	if(gps_usart != DISABLE)
	{		
				memset(Buffer,0,sizeof(Buffer));	//清空串口接收缓存
		 
				lenth = BSP_GetFormatRxBuffer(gps_usart,Buffer,sizeof(Buffer)-2,cutstr,strlen(cutstr));//读取的缓存数据

				
				if (lenth > 0)  //缓存不为空
				{ 
					timeout = 0;//OBD模式
						
					pvtg = strstr((char *)pOut,"VTG,");//查找字符串
					
					while(pvtg != NULL)
					{
						if(vtg_flag == 0)//出现vtg一次做采样1次
						{
									vtg_flag = 1;
								
									memset(BaseBoardBuffer,0,sizeof(BaseBoardBuffer));	//清空主板数据缓存
									GetBaseBoardDataPack(BaseBoardBuffer,sizeof(BaseBoardBuffer));//获取主板数据
						
									memset(OBDstrbuffer,0,sizeof(OBDstrbuffer));	//清空主板数据缓存
									HextoStr(BaseBoardBuffer,OBDstrbuffer,sizeof(BaseBoardBuffer));//数据转换	
						}	
						
						pvtg = (u8 *)((u8 *)pvtg - 3);//$GPVTG查找到VTG后往前移动3分字符，指向$符号
				
						USART_Sendbuffer(upload_usart,(u8 *)pOut,(u16)(pvtg - pOut));//将VTG前面的数据先发送完

						vtg_flag = 0;//打开主板采样

						USART_Sendbuffer(upload_usart,OBDHandbuffer,sizeof(OBDHandbuffer)-1);//插入主板字头数据

						USART_Sendbuffer(upload_usart,OBDstrbuffer,OBD_LENTH-1);//插入主板数据

						pOut = pvtg;

						pvtg = pvtg + 6;//跳过vtg查找下一个

						pvtg = strstr((char *)pvtg,"VTG,");//查找字符串//查找下一条数据
						
						//
						if(pvtg >= (Buffer + lenth)) break; //数组越界
					}

					USART_Sendbuffer(upload_usart,(u8 *)pOut,(u16)(lenth-(u16)(pOut-Buffer)));		//上传剩余数据
					
				}
				else
				{

					if(timeout >= 200)
					{	
						 vtg_flag = 0;//打开主板采样
						
						//printf("InsertBaseboardData\r\n");
						
						//USART_Sendbuffer(upload_usart,Handbuffer,sizeof(Handbuffer));//单主板数据二进制格式
						
						//USART_Sendbuffer(upload_usart,BaseBoardBuffer,sizeof(BaseBoardBuffer));//单主板数据二进制格式
						
						USART_Sendbuffer(upload_usart,OBDHandbuffer,sizeof(OBDHandbuffer)-1);//插入主板字头数据
						
						USART_Sendbuffer(upload_usart,OBDstrbuffer,OBD_LENTH-1);//插入主板数据

						
						delay_ms(80);//间隔100毫秒

					}
					else
					{
						timeout++;
//						printf("InsertBaseboardData:timeout!!!  timeout = %b02d\r\n",timeout);
						delay_ms(5);//间隔100毫秒
					}
					
				}
	}
	else 
	{	
		    vtg_flag = 0;//打开主板采样
				
				USART_Sendbuffer(upload_usart,Handbuffer,sizeof(Handbuffer));//单主板数据二进制格式
				
				USART_Sendbuffer(upload_usart,BaseBoardBuffer,sizeof(BaseBoardBuffer));//单主板数据二进制格式
				
			  //USART_Sendbuffer(upload_usart,OBDHandbuffer,sizeof(OBDHandbuffer)-1);//单主板数据字符串格式
				
				//USART_Sendbuffer(upload_usart,OBDstrbuffer,OBD_LENTH-1);//单主板数据字符串格式	
				
				delay_ms(100);//间隔100毫秒	
	 }		 

		
}
#endif
//========================================================================
// 函数:void SerialDataUpload(u8 upload_usart)
// 描述: 上传主板数据
// 参数：u8 upload_usart为主板与上位机的串口
// 版本: V1.0, 2022-10-17
//========================================================================
void SerialDataUpload(u8 upload_usart)
{

	if(start == TURE)
	{
		  
			#ifdef  STC12C5A60S2		
			memset(BaseBoardBuffer,0,sizeof(BaseBoardBuffer));	//清空主板数据缓存
			
			GetBaseBoardDataPack(BaseBoardBuffer,sizeof(BaseBoardBuffer));//获取主板数据	
				
			USART_Sendbuffer(upload_usart,Handbuffer,sizeof(Handbuffer));//上传单主板数据
						
			USART_Sendbuffer(upload_usart,BaseBoardBuffer,sizeof(BaseBoardBuffer));//上传单主板数据
			#endif

			#ifdef  STC15W4K48S4
		  
			InsertBaseboardData(GPS_USART,upload_usart);//插入主板数据上传		

			#endif
		 
	}
}
#ifdef  STC15W4K48S4	


//========================================================================
// 函数:void Serial_TiltSensor_Analy(u8 Tilt_usart,TiltSensorTypeDef *Tilt)
// 描述: 解析倾角传感器数据
// 参数：u8 Tilt_usart为倾角传感器与主板之间的接口 TiltSensorTypeDef *Tilt传感器数据保存的内存地址
// 返回：解析到数据返回TURE，否则返回FALSE
// 版本: V1.0, 2022-10-17
//========================================================================
u8 Serial_TiltSensor_Analy(u8 Tilt_usart,TiltSensorTypeDef *Tilt)
{
   
	 xdata u8 *pOut =  NULL;//指向数据的出口
	 xdata u16 lenth = 0;
	 xdata u8 cutstr[] ={0x55,0x53};
	 xdata u8 ret = FALSE;
	 xdata u8 i = 0;
	 xdata u8 j = 0;
	 xdata u8 sum = 0;
		
	 memset(Buffer,0,sizeof(Buffer));	//清空串口接收缓存
	 
	 BSP_ClearUsartRxBuffer(Tilt_usart);//清除二级缓存	
	 
	 lenth = BSP_GetFormatRxBuffer(Tilt_usart,Buffer,sizeof(Buffer),cutstr,sizeof(cutstr));//读取的缓存数据	 

	 if(lenth > 0)
	 {
		pOut = ByteArrayCompar(Buffer,lenth,cutstr,sizeof(cutstr));//获取字头的位置		
	 
		while(pOut != NULL)
		{
				//55 53 00 00 01 01 00 00 02 02 00 00 03 03 00 00 00 00 00 00 00 
				if (TILT_ALL_USART != DISABLE)//所有的传感器汇总后统一输出到主板  
				{
					i= 0;
					j = 0;
					while(j<20)
					{
							Tilt->RollL = *(pOut + (i+2));			//X轴角度低字节
							Tilt->RollH = *(pOut + (i+3));			//X轴角度高字节
							Tilt->PitchL = *(pOut + (i+4));			//Y轴角度低字节
							Tilt->PitchH = *(pOut + (i+5));			//Y轴角度高字节
							Tilt->YawL = *(pOut + (j+14));				//Z轴角度低字节
							Tilt->YawH = *(pOut + (j+15));				//Z轴角度高字节					
							Tilt->Roll	= (int)((Tilt->RollH << 8) 	| Tilt->RollL	)	/32768.0*1800;			//X轴角度
							Tilt->Pitch = (int)((Tilt->PitchH << 8) | Tilt->PitchL)	/32768.0*1800;			//Y轴角度
							Tilt->Yaw		= (int)((Tilt->YawH << 8) 	| Tilt->YawL)		/32768.0*1800;			//Z轴角度

							if(Tilt->Roll>127) //边界处理
							{
								Tilt->Roll = 127;
							}
							else if(Tilt->Roll < -127) 
							{
								Tilt->Roll = -127;
							}
							if(Tilt->Pitch>127) //边界处理
							{
								Tilt->Pitch = 127;
							}
							else if(Tilt->Pitch < -127) 
							{
								Tilt->Pitch = -127;
							}		
							if(Tilt->Yaw>127) //边界处理
							{
								Tilt->Yaw = 127;
							}
							else if(Tilt->Yaw < -127) 
							{
							Tilt->Yaw = -127;
							}
						
							i = i+4;//按协议移动
							j = j+2;
							Tilt++;//移到下一组数据
							
					}	
					ret = TURE;
				}
				else   //55 53 01 02 02 02 01 01 00 00 00  
				{
										  sum = 0;
					  //k++;
					  for(i = 0;i<10;i++) //求校验和
						{
							sum += *(pOut + i);
							//printf("%b02X ",*(pOut+i));
						}
						//printf("%b02X \r\n",*(pOut+i));
						//printf("sum = %b02X  k = %b02d \r\n",sum,k);
						if(sum == *(pOut + 10))//校验和成立
						{	
						Tilt->RollL = *(pOut + 2);			//X轴角度低字节
						Tilt->RollH = *(pOut + 3);			//X轴角度高字节
						Tilt->PitchL = *(pOut + 4);			//Y轴角度低字节
						Tilt->PitchH = *(pOut + 5);			//Y轴角度高字节	
						Tilt->YawL = *(pOut + 6);				//Z轴角度低字节
						Tilt->YawH = *(pOut + 7);				//Z轴角度高字节
					
//					  printf("------------------------------------\r\n");
//						printf("Tilt->RollL = %b02d\r\n",	Tilt->RollL);
//						printf("Tilt->RollH = %b02d\r\n",	Tilt->RollH);
//						printf("Tilt->PitchL = %b02d\r\n",Tilt->PitchL);
//						printf("Tilt->PitchH = %b02d\r\n",Tilt->PitchH);
//						printf("Tilt->YawL = %b02d\r\n",	Tilt->YawL);
//						printf("Tilt->YawH = %b02d\r\n",	Tilt->YawH);
//					  printf("------------------------------------\r\n");
								
						Tilt->Roll	= (int)((Tilt->RollH << 8) 	| Tilt->RollL	)	/32768.0*1800;			//X轴角度
						Tilt->Pitch = (int)((Tilt->PitchH << 8) | Tilt->PitchL)	/32768.0*1800;			//Y轴角度
						Tilt->Yaw		= (int)((Tilt->YawH << 8) 	| Tilt->YawL)		/32768.0*1800;			//Z轴角度
					
//						printf("Tilt->Roll = %h04d\r\n",	Tilt->Roll);
//						printf("Tilt->Pitch = %h04d\r\n",	Tilt->Pitch);
//						printf("Tilt->Yaw = %h04d\r\n",		Tilt->Yaw);
							
						if(Tilt->Roll > 127) //边界处理
						{
							Tilt->Roll = 127;
						}
						else if(Tilt->Roll < -127) 
						{
							Tilt->Roll = -127;
						}

						if(Tilt->Pitch > 127) //边界处理
						{
							Tilt->Pitch = 127;
						}
						else if(Tilt->Pitch < -127) 
						{
							Tilt->Pitch = -127;
						}		
						if(Tilt->Yaw > 127) //边界处理
						{
							Tilt->Yaw = 127;
						}
						else if(Tilt->Yaw < -127) 
						{
							Tilt->Yaw = -127;
						}	
						
						 ret = TURE;
						 return ret; 	
					}						
				
				}
			 pOut = pOut +1;//指针后移，取下一组数据
						 
			 pOut = ByteArrayCompar(pOut,lenth,cutstr,sizeof(cutstr));//获取字头的位置
						 
		}	
	} 
	 
	return ret; 
}

//========================================================================
// 函数:HighSensorShock_Analy(u8 bump_usart,FlashParameterTypeDef *pole)
// 描述: 按照通讯协议解析碰杆传感器传感器的数据,将解析好的数据保存到pole指向的内存中
// 参数：USRATx数据通讯的端口号，FlashParameterTypeDef *pole碰杆的数据类型指针
// 返回：获取到串口数据返回TURE，否者返回FALSE
// 版本: V1.0, 2022-10-17
//========================================================================
u8 Serial_HighSensorShock_Analy(u8 bump_usart) //高森震动传感器数据解析
{
	 //$HS-MOTION,15,0000000000.0000100000*03
	 xdata u8 *phand = NULL;//指向数据的出口
	 xdata u8 *pOut = NULL;//指向数据的出口
	 xdata u8 *pEnd = NULL;
	 xdata u16 lenth = 0;
	 xdata u8 group_i = 0;//
	 xdata u16 temp = 0;//
	 xdata u8 ret = FALSE;
	 xdata u8 i = 0;
	 xdata u8 cutstr[] ="\n";

   if(bump_usart == DISABLE) return 0;
	
	 memset(Buffer,0,sizeof(Buffer));	//清空串口接收缓存

	 lenth = BSP_GetFormatRxBuffer(bump_usart,Buffer,sizeof(Buffer),cutstr,strlen(cutstr));//读取的缓存数据	
	
	  if (lenth > 0)  //缓存不为空
		{ 	
			//printf("lenth = %h04d\r\n",lenth);
			//USART_Sendbuffer(USART1,Buffer,lenth);
			
			phand = strstr((char *)Buffer,"$HS-MOTION");//查找字符串
			
			//printf("phand = %p\r\n",phand);
			
			pEnd = strstr((char *)Buffer,cutstr);//查找结束符号
			
			//printf("pEnd = %p\r\n",pEnd);
			
			while((phand != NULL) && (pEnd != NULL))
			{
				ret =TURE;//已经解析到数据
				
				//printf("BSP_GetFormatRxBuffer lenth = %h04d\r\n",lenth);
				
				phand = strstr((char *)phand,",");//查找逗号
				phand ++ ;
				phand = strstr((char *)phand,",");//查找第二个逗号
				
				pOut = (u8 *)(phand +1);	//指向数据
				
				//printf("pOut = %p\r\n",pOut);
				
				for (group_i = 0; group_i < sizeof(pFlash->bump)/sizeof(pFlash->bump[0]);group_i++)
				{
					  //printf("group_i = %b02d\r\n",group_i);
					
						if(pFlash->bump[group_i].name != 0)					//碰杆项目已经配置
						{
							
							if( (pOut + pFlash->bump[group_i].count) > pEnd)					//数据长度不合法，退出
							{

								//printf("pOut + pFlash->bump[group_i].count) > pEnd\r\n");
								break;
							}		
							
							pFlash->bump[group_i].value = 0;//清零，用于赋值
							
							for (i = 0; i< pFlash->bump[group_i].count; i++)//取该组的碰杆状态
							{
				
								temp = (*pOut - '0');					//取碰杆状态
								
								if (*pOut == '.')							
								{
									pOut++;			  							//跳过小数点
									temp = (*pOut - '0');				//取碰杆状态	
								}	
								pOut++;		
										
								temp = temp << i;
											
								pFlash->bump[group_i].value |= temp;//将传感器的状态按顺序写入返回值
								
							}
							//printf("value = %h04d\r\n",pFlash->bump[group_i].value);
						}
						else
							{
								  //printf("pole->bump[group_i].name == 0\r\n");
									break;//主板参数未配置或没有按顺序配置该参数，返回，不在解析该条数据
							}		
				 }
				
				
				 
				phand = strstr((char *)pOut,"$HS-MOTION");//查找字符串
				 
				//printf("phand = %p\r\n",phand);
				 
				pEnd = pEnd + 1;	//跳过切割的结束符
				pEnd = strstr((char *)pEnd,cutstr);//再次查找结束符号	
				 
				//printf("pEnd = %p\r\n",pEnd); 		 
	     
		  }
		}
		return ret;
		
}

//========================================================================
// 函数:Serial_Sensor24GShock_Analy(u8 bump_usart,PengganTypeDef *pole)
// 描述: 按照通讯协议解析碰杆传感器传感器的数据,将解析好的数据保存到pole指向的内存中
// 参数：USRATx数据通讯的端口号，PengganTypeDef *pole碰杆的数据类型指针
// 返回：获取到串口数据返回TURE，否者返回FALSE
// 版本: V1.0, 2022-10-17
//========================================================================
void Serial_Sensor24GShock_Analy(u8 bump24g_usart,PengganTypeDef *pole) //2.4G震动传感器数据解析
{
	 xdata u8 *pOut =  NULL;//指向数据的出口
	 xdata u16 lenth = 0;
	 xdata u8 cutstr[] ={0x53};

	 if(bump24g_usart == DISABLE) return;
	 
	 memset(Buffer,0,sizeof(Buffer));	//清空串口接收缓存

	 lenth = BSP_GetFormatRxBuffer(bump24g_usart,Buffer,sizeof(Buffer),cutstr,sizeof(cutstr));//读取的缓存数据	

	  if (lenth > 0)  //缓存不为空
		{ 	
			pOut = ByteArrayCompar(Buffer,lenth,cutstr,sizeof(cutstr));//获取字头的位置	
			
			while(pOut != NULL)
		  {
			 pole->name = *(pOut +2);		//项目名称
			 pole->number = *(pOut +3);	//项目编号
			 pole->value = *(pOut +4);	//杆号
				
			 pOut = pOut +1;//指针后移，取下一组数据
				
			 pOut = ByteArrayCompar(pOut,lenth,cutstr,sizeof(cutstr));//获取字头的位置
			}	
		}
		
}


//========================================================================
// 函数:Serial_csb_dbq_Analy(u8 csb_dbq_usart,PengganTypeDef *pole)
// 描述: 按照通讯协议解析超声波（单边桥）传感器传感器的数据,将解析好的数据保存到pole指向的内存中
// 参数：USRATx数据通讯的端口号，PengganTypeDef *pole碰杆的数据类型指针
// 返回：无
// 版本: V1.0, 2023-5-24
//========================================================================
void Serial_csb_dbq_Analy(u8 csb_dbq_usart,CsbTypeDef *csb) //超声波（单边桥传感器解析）
{
	 xdata u8 *pOut =  NULL;//指向数据的出口
	 xdata u16 lenth = 0;
	 xdata u8 cutstr[] ={0xf0};

	 if(csb_dbq_usart == DISABLE) return;
	 
	 memset(Buffer,0,sizeof(Buffer));	//清空串口接收缓存

	 lenth = BSP_GetFormatRxBuffer(csb_dbq_usart,Buffer,sizeof(Buffer),cutstr,sizeof(cutstr));//读取的缓存数据	

	  if (lenth > 0)  //缓存不为空
		{ 	
			pOut = ByteArrayCompar(Buffer,lenth,cutstr,sizeof(cutstr));//获取字头的位置	
			
			while(pOut != NULL)
		  {
			 if((*(pOut) == 0xf0) && (*(pOut +2) == 0xf1) && (*(pOut +4) == 0xf2) && (*(pOut +6) == 0xf3))
			 {
				csb->value0 = *(pOut +1);		//项目名称
				csb->value1 = *(pOut +3);		//项目名称
				csb->value2 = *(pOut +5);		//项目名称
				csb->value3 = *(pOut +7);		//项目名称
			 }
				
			 pOut = pOut +1;//指针后移，取下一组数据
				
			 pOut = ByteArrayCompar(pOut,lenth,cutstr,sizeof(cutstr));//获取字头的位置
			}	
		}
		
}



//========================================================================
// 函数:Serial_csb_sd_Analy(u8 Serial_csb_sd_Analy,CsbTypeDef *csb)
// 描述: 按照通讯协议解析超声波（隧道）传感器传感器的数据,将解析好的数据保存到csb指向的内存中
// 参数：csb_sd_usart数据通讯的端口号，CsbTypeDef *csb碰杆的数据类型指针
// 返回：无
// 版本: V1.0, 2023-5-24
//========================================================================
void Serial_csb_sd_Analy(u8 csb_sd_usart,CsbTypeDef *csb) //超声波（隧道传感器解析）
{
	 xdata u8 *pOut =  NULL;//指向数据的出口
	 xdata u16 lenth = 0;
	 xdata u8 cutstr[] ={0xf0};

	 if(csb_sd_usart == DISABLE) return;
	 
	 memset(Buffer,0,sizeof(Buffer));	//清空串口接收缓存

	 lenth = BSP_GetFormatRxBuffer(csb_sd_usart,Buffer,sizeof(Buffer),cutstr,sizeof(cutstr));//读取的缓存数据	

	  if (lenth > 0)  //缓存不为空
		{ 	
			pOut = ByteArrayCompar(Buffer,lenth,cutstr,sizeof(cutstr));//获取字头的位置	
			
			while(pOut != NULL)
		  {
			 if((*(pOut) == 0xf0) && (*(pOut +2) == 0xf1) && (*(pOut +4) == 0xf2) && (*(pOut +6) == 0xf3))
			 {
				csb->value0 = *(pOut +1);		//项目名称
				csb->value1 = *(pOut +3);		//项目名称
				csb->value2 = *(pOut +5);		//项目名称
				csb->value3 = *(pOut +7);		//项目名称
			 }
				
			 pOut = pOut +1;//指针后移，取下一组数据
				
			 pOut = ByteArrayCompar(pOut,lenth,cutstr,sizeof(cutstr));//获取字头的位置
			}	
		}

}

#endif
//========================================================================
// 函数:u8 Serial_Analy(u8 *RxBuffer)
// 描述: 按照通讯协议解析串口数据
// 参数：USRATx数据通讯的端口号，RxBuffer数据缓存区指针,lenth为数据长度
// 返回：解析成功，返回TURE.失败返回 FALSE
// 版本: V1.0, 2022-10-17
//========================================================================
u8 Serial_CMD_Analy(u8 USRATx,u8 *RxBuffer,u16 lenth)
{
	u8 *pfirst = NULL;  
	xdata	u16 flash_addr = 0;
	xdata	u8 flash_value = 0;
	xdata	u16 validlen = 0;
	
		//处理自定义复位命令reset
	pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_RESET,strlen(CMD_RESET));//比较指令
	if (NULL != pfirst) //收到开始采集指令
	{
		printf("CMD_RESET:IAP_CONTR = 0x60\n");
		IAP_CONTR = 0x60;  //软件复位
		return	TURE;
	}
	
	//处理开始采集指令 55 AA 00 00 11 11
	pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_start,sizeof(CMD_start));//比较指令
	if (NULL != pfirst) //收到开始采集指令
	{
		
		if(start == FALSE)
		{
			FIRMWARE_VERSION();//打印固件版本号
		}
		Cmd_Start_Callback();
		start = TURE;
		return	TURE;
	}

	//处理停止采集指令 55 AA 00 00 00 00  
	pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_stop,sizeof(CMD_stop));//比较指令
	if (NULL != pfirst) //收到开始采集指令
	{
		start = FALSE;
		Cmd_Stop_Callback();
		return	TURE;
	}

	//处理写flash指令 0x55 0xaa 0x49 0x4f 0x58 0x47
	pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_writeflash,sizeof(CMD_writeflash));//比较指令
	
	if (NULL != pfirst) //收到写flash指令
	{
		start = FALSE;	//停止采集
		Cmd_Stop_Callback();
		validlen = lenth - (pfirst - RxBuffer);//字头校验成功后，计算有效数据的长度。
		if(validlen < 10) //写flash指令是10个字节，不够10个字节继续接收
		{
			return FALSE;
		}
		flash_addr = *(pfirst + 6);
		flash_addr = flash_addr<<8;
		flash_addr = flash_addr + *(pfirst + 7);

		flash_value = *(pfirst + 9);

		BSP_FlashWriteByte(flash_addr,flash_value);//写入flash

		USART_Sendbuffer(USRATx,CMD_wflash_Ack,sizeof(CMD_wflash_Ack));//应答

		return TURE;
	}
	
	//处理读flash指令 0x55,0xaa,0x49,0x4f,0x44,0x51 
	pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_readflash,sizeof(CMD_readflash));//比较指令
	
	if (NULL != pfirst) //收到读flash指令
	{
		start = FALSE;//停止采集车辆信号
		Cmd_Stop_Callback();
		validlen = lenth - (pfirst - RxBuffer);//字头校验成功后，计算有效数据的长度。		
		
		if(validlen < 10) //写flash指令是10个字节，不够10个字节继续接收
		{
			return FALSE;//继续接收串口数据
		}
			
		flash_addr = *(pfirst + 6);
		flash_addr = flash_addr<<8;
		flash_addr = flash_addr + *(pfirst + 7);
		
		flash_value = IapReadByte(flash_addr);//读出flash	
		
		USART_Sendbuffer(USRATx,CMD_rflash_Ack,sizeof(CMD_rflash_Ack));//应答
		
		USART_SendData(USRATx,flash_value);//发送读出来的值
		
		return TURE;
	}
	#ifdef  STC15W4K48S4
	if (GPS_USART != DISABLE)
	{
			//进入GPS移动站配置 0x55 0xAA 0x49 0x4F 0xff 0xff
			pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_conf_gpssmobile,sizeof(CMD_conf_gpssmobile));//比较指令
			
			if (NULL != pfirst) //收到GPS移动站配置指令
			{
				start = FALSE;//停止采集车辆信号
				
				//GPS_EnterConfiguration(MOBILESTATION);//进入GPS基准站配置
					
				return TURE;
			}
			
			//进入GPS基准站配置 0x55 0xAA 0x49 0x4F 0xff 0xfe
			pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_conf_gpsbase,sizeof(CMD_conf_gpsbase));//比较指令
			
			if (NULL != pfirst) //收到GPS移动站配置指令
			{
				start = FALSE;//停止采集车辆信号
				
				//GPS_EnterConfiguration(BASESTATION);//进入GPS基准站配置

				return TURE;
			}	
			
			//读取GPS基准站坐标指令0x55 0xAA 0x49 0x4F 0xff 0xfc
			pfirst = ByteArrayCompar(RxBuffer,lenth,CMD_get_gpsbasepos,sizeof(CMD_get_gpsbasepos));//比较指令
			
			if (NULL != pfirst) //收到GPS移动站配置指令
			{
				start = FALSE;//停止采集车辆信号
				
				//GetBaseStationPos();//获取基准站坐标
					
				return TURE;
			}		
	}
	#endif
	return FALSE;
		
}


//========================================================================
// 函数:void SerialHandle(u8 USARTx)
// 描述: 串口处理程序
// 参数：USARTx端口号
// 版本: V1.0, 2022-10-17
//========================================================================
void SerialHandle(u8 USARTx)
{

	xdata u16 lenth = 0;        
	memset(Buffer,0,sizeof(Buffer));//清理缓存区
//#ifdef  STC15W4K48S4	
//	if(NETWORK_STATE == 16) return;//网口被禁用，16为自定义防止改参数时误操作
//#endif
#ifdef  STC15W4K48S4			
	if((USARTx == GPS_USART) && (start == TURE)) return;//如调试串口被GPS占用，且收到11指令 调试功能失效，只能使用网口进行修改参数
#endif

	lenth = BSP_GetUsartRxBuffer(USARTx,Buffer,sizeof(Buffer));//读取缓存数据		
	if (lenth > 0)
	{
		if(Serial_CMD_Analy(USARTx,Buffer,lenth) == TURE)
		{
			 BSP_ClearUsartRxBuffer(USARTx);	//解析成功后清空串口缓存区域
		}
		
	}	

}



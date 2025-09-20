
#include	"./User/includes.h"
#include	<stdio.h>
#include	<string.h>

#ifdef  STC15W4K48S4	
xdata PengGanSignalTypeDef	pgxd[4];//碰杆消抖
#endif
//========================================================================
// 函数: void BSP_GPIO_Init(void)
// 描述: 初始化主板IO口.全部初始化为：上拉准双向口
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_GPIO_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;				//结构定义
	
	GPIO_InitStructure.Pin  = GPIO_Pin_All;			//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
	GPIO_InitStructure.Mode = GPIO_PullUp;			//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);	//初始化GPIO_P0
	GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);	//初始化GPIO_P1
	GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);	//初始化GPIO_P2
	GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//初始化GPIO_P3
	GPIO_Inilize(GPIO_P4,&GPIO_InitStructure);	//初始化GPIO_P4
	
}
//========================================================================
// 函数: void BSP_Zhuansu_Init(void)
// 描述: 初始化定时器0为计数模式，对转速脉冲计数
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_ZhuansuCount_Init(void)
{
	  TMOD |= 0x05;	//设置定时器0为计数器模式//对转速脉冲计数
	  TH0=0; 				//计数器清零
	  TL0=0;				//计数器清零
    TR0=1; 				//计数器0开始计数
}
//========================================================================
// 函数: void BSP_LichengCount_Init(void)
// 描述: 初始化定时器为计数模式，对转速脉冲计数
// 版本: V1.0, 2023-5-25
//========================================================================
void BSP_LichengCount_Init(void)
{

	  switch(pFlash->lc.pin)
	  {
			case	LC_T0: 	  						
										TMOD |= 0x05;	//设置定时器0为计数器模式
										TH0=0; 				//计数器清零
										TL0=0;				//计数器清零
										TR0=1; 				//计数器0开始计数
										break;
			case	LC_T1:             		
										TMOD |= 0x50;	//使用计数器T1为计数器模式
										TH1=0; 				//计数器清零
										TL1=0;				//计数器清零
										TR1=1; 				//计数器1开始计数
								    break;
		
#ifdef  STC15W4K48S4
			case	LC_T2:             		//使用计数器T2
										AUXR |= 0x08;	//使用计数器T2为计数器模式
										T2H=0; 				//计数器清零
										T2L=0;				//计数器清零
										AUXR |= 0x10;	//计数器2开始计数
								    break;
			case	LC_T3:             		//使用计数器T3
										T4T3M |=0x04;//使用计数器T3为计数器模式
										T3H=0; 				//计数器清零
										T3L=0;				//计数器清零
										AUXR |= 0x08;	//计数器3开始计数
								    break;
			case	LC_T4:                //使用计数器T4
										T4T3M |=0x40; //使用计数器T3为计数器模式
										T4H=0; 				//计数器清零
										T4L=0;				//计数器清零
										AUXR |= 0x80;	//计数器4开始计数
								    break;
#endif
			default:
			
					return;				
	 }	
	
	
	
	
	
}
//========================================================================
// 函数: u8 BSP_GetGpioStatus(u8 pin)
// 描述: 读取输入管脚电平值.此函数与硬件电路相关联
// 参数: 板载输入口编号，取值D1--D32.
// 返回: 输入口电平值.0或者1
// 版本: V1.0, 2022-10-17
//========================================================================
u8 BSP_GetGpioStatus(u8 pin)//查询对应的IO口状态
{
	switch(pin)
	{
#ifdef  STC12C5A60S2	
		case D1:		return(P00);
		case D2:   	return(P01);
		case D3:   	return(P02);
		case D4:   	return(P03);
		case D5:   	return(P04);
		case D6:   	return(P05);
		case D7:   	return(P06);
		case D8:   	return(P07);
		case D9:   	return(P27);
		case D10:  	return(P26);
		case D11:  	return(P25);
		case D12:  	return(P24);
		case D13:  	return(P23);
		case D14:  	return(P22);
		case D15:  	return(P21);
		case D16:  	return(P20);
		case D17:  	return(P10);
		case D18:  	return(P11);
		case D19:  	return(P12);
		case D20:  	return(P13);
		case D21:  	return(P14);
		case D22:  	return(P15);
		case D23:  	return(P16);
		case D24:  	return(P17);
		case D25:  	return(P32);
		case D26:  	return(P33);
		case D27:  	return(P34);
		case D28:  	return(P35);
		case D29:  	return(P36);
		case D30:  	return(P37); 
		case D31:  	return(P47);
		case D32:  	return(P46);
		case D33:  	return(P45);
		case D34:  	return(P44); 
		case D35:  	return(P44);
#endif
#ifdef  STC15W4K48S4	
		case D1:		return(P45);
		case D2:   	return(P27);
		case D3:   	return(P02);
		case D4:   	return(P26);
		case D5:   	return(P03);
		case D6:   	return(P25);
		case D7:   	return(P04);
		case D8:   	return(P24);
		case D9:   	return(P05);
		case D10:  	return(P23);
		case D11:  	return(P06);
		case D12:  	return(P22);
		case D13:  	return(P07);
		case D14:  	return(P21);
		case D15:  	return(P20);
		case D16:  	return(P44);
		case D17:  	return(P12);
		case D18:  	return(P42);
		case D19:  	return(P13);
		case D20:  	return(P41);
		case D21:  	return(P14);
		case D22:  	return(P37);
		case D23:  	return(P15);
		case D24:  	return(P36);
		case D25:  	return(P35);
		case D26:  	return(P34);
		case D27:  	return(P33);
		case D28:  	return(P32);
		case D29:  	return(P54);
		case D30:  	return(P55); 
		case D31:  	return(P55);
		case D32:  	return(P55);
#endif

		default: 
								return(1);//返回1就是没有信号
	}
}
//========================================================================
// 函数: u8 BSP_ReadInputDataBit(SignalTypeDef *pSignal)
// 描述: 读取输入管脚电平值.
// 参数: SignalTypeDef为指向信号结构体的指针.
// 返回: 返回TURE，或FALSE.
// 版本: V1.0, 2022-10-17
//========================================================================
u8 BSP_ReadInputDataBit(SignalTypeDef *pSignal)
{
  xdata u8 status = 0;
	xdata u8 signalstatus = BSP_GetGpioStatus(pSignal->pin);//获取单片机的管脚输入状态
	
	if(pSignal->pin >= 64) //如果管脚数值超过64，直接返回0
	{
			return FALSE;
	}
	if(pSignal->falling_ed == 255)  pSignal->falling_ed = 0;//此处仅为兼容老版本的程序，未增加该参数的情况

	if(pSignal->stateflag == 0)
	{
		if (signalstatus == pSignal->modle)//判断信号是否开启
		{
			pSignal->times = 0;
			status = TURE;	
		}
		else if(pSignal->times < pSignal->rising_ed) //信号抖动与延时处理
		{
			(pSignal->times)++;
			status = TURE;	
		}	
		else 
		{
			pSignal->stateflag = 1;
			status = FALSE; 
		}
  }
	else 
	{
		if (signalstatus != pSignal->modle)//获取相应的状态
		{
			pSignal->times = 0;
			status = FALSE;
		}
		else if(pSignal->times < pSignal->falling_ed) //信号抖动与延时处理
		{
			(pSignal->times)++;
			status = FALSE;
		}	
		else 
		{
			pSignal->stateflag = 0;
			status = TURE; 
		}		
	}
	#ifdef DEBUG1
	if(pSignal->pin ==12)
	{
					printf("pin = %b02u  modle  = %b02u  times = %b02u rising_ed = %b02u falling_ed = %b02u\r\n"\
								,pSignal->pin,pSignal->modle,pSignal->times,pSignal->rising_ed,pSignal->falling_ed);
					printf("gpiovalue = %b02d.  ",signalstatus);
					printf("output = %b02d.\r\n",status);
	}
	#endif	
	return(status);
}
//========================================================================
// 函数:BSP_ReadMultipleDataBit(MultSignalTypeDef *pSignal,u8 offset)
// 描述: 读取一个传感器多个信号线
// 参数: MultSignalTypeDef指向地址，pin读的是哪一根信号线.
// 返回: 返回TURE，或FALSE.
// 版本: V1.0, 2022-10-17
//========================================================================
u8 BSP_ReadMultipleDataBit(MultSignalTypeDef *pSignal,u8 offset)
{
		
	xdata u8 pin = *(u8 *)((u8 *)pSignal + offset  - 1);
  xdata u8 status = 0;
	xdata u8 signalstatus = BSP_GetGpioStatus(pin);//获取单片机的管脚输入状态
	xdata u8 flag = 0;//信号反转标志
	
	if(pin >= 64) //如果管脚数值超过64，直接返回0
	{
			return FALSE;
	}
	flag = (((pSignal->stateflag) >> (offset-1)) & (0x01));//得到标志状态
	
	pSignal->times = pSignal->counts[offset-1];//获取延时计数器的值
	
	if(pSignal->falling_ed == 255)  pSignal->falling_ed = 0;//此处仅为兼容老版本的程序，未增加该参数的情况
		
	if(flag == 0)
	{
		if (signalstatus == pSignal->modle)//判断信号是否开启
		{
			pSignal->times = 0;
			status = TURE;
		}
		else if(pSignal->times < pSignal->rising_ed) //信号抖动与延时处理
		{
			pSignal->times++;
			status = TURE;
		}	
		else 
		{
			flag = 1;
			status = FALSE; 
		}
  }
	else 
	{
		if (signalstatus != pSignal->modle)//获取相应的状态
		{
			pSignal->times = 0;
			status = FALSE;
		}
		else if(pSignal->times < pSignal->falling_ed) //信号抖动与延时处理
		{
			pSignal->times++;
			status = FALSE;
		}	
		else 
		{
			flag = 0;
			status = TURE; 
		}		
	}
  pSignal->counts[offset-1]=pSignal->times;//保存本次延时计数器的值
	
  pSignal->stateflag |= (flag << offset-1);
		
	return(status);
	
}


////========================================================================
//// 函数:BSP_MultipdelayOutput(MultSignalTypeDef *pSignal,u8 value)
//// 描述: 多路信号的延时输出
//// 参数: MultSignalTypeDef指向地址，value当前的值.
//// 返回: 返回TURE，或FALSE.
//// 版本: V1.0, 2023-8-31
////========================================================================
//u8 BSP_delayOutput(u8 *times, u8 *counts, u8 *value)
//{
//	static  u8 state = 0;
//	static  u8 times = 0;
//	
//	if(state != value) //值发生变化
//	{
//		
//		if(times <  counts) //使用上升沿的延时参数
//		{
//			times++;
//			
//		}
//		else 
//		{
//			times = 0;
//			
//			state = value;
//			
//		}
//					
//	}
//	else 
//	{
//		 times = 0;
//	}
//	
//		printf("times = %b02u state = %b02u\r\n",times,state);
//	
//	return state;
//	
//	
//}
#ifdef  STC15W4K48S4	
//========================================================================
// 函数:BSP_ReadBumpDataBit(SignalTypeDef *pSignal,u8 group,u8 valuebit,u8 offset)
// 描述: 碰杆传感器消抖
// 参数: MultSignalTypeDef指向地址，u8 碰杆状态的value值 offset读的是哪一根信号线（从0开始）.
// 返回: 返回TURE，或FALSE.
// 版本: V1.0, 2022-10-17
//========================================================================
u8 BSP_ReadBumpDataBit(SignalTypeDef *pSignal,u8 group,u8 valuebit,u8 offset)
{
  xdata u8 status = 0;
	xdata u8 signalstatus = valuebit;//获取输入状态
	
	xdata u8 flag = 0;//信号反转标志
	
	flag = (((pgxd[group].stateflag) >> offset) & (0x01));//得到标志状态
	
	pSignal->times = pgxd[group].times[offset];//获取延时计数器的值
	
	if(pSignal->falling_ed == 255)  pSignal->falling_ed = 0;//此处仅为兼容老版本的程序，未增加该参数的情况
		
	if(flag == 0)
	{
		if (signalstatus == TURE)//判断信号是否开启
		{
			pSignal->times = 0;
			status = TURE;
		}
		else if(pSignal->times < pSignal->rising_ed) //信号抖动与延时处理
		{
			pSignal->times++;
			status = TURE;
		}	
		else 
		{
			flag = 1;
			status = FALSE; 
		}
  }
	else 
	{
		if (signalstatus != TURE)//获取相应的状态
		{
			pSignal->times = 0;
			status = FALSE;
		}
		else if(pSignal->times < pSignal->falling_ed) //信号抖动与延时处理
		{
			pSignal->times++;
			status = FALSE;
		}	
		else 
		{
			flag = 0;
			status = TURE; 
		}		
	}
	#ifdef DEBUG1
		if(pin == 13)
		{
		printf("pin = %b02u  modle  = %b02u  times = %b02u rising_ed = %b02u falling_ed = %b02u\r\n"\
								,pin,pSignal->modle,pSignal->times,pSignal->rising_ed,pSignal->falling_ed);
		printf("gpiovalue = %b02d.  ",signalstatus);
		printf("output = %b02d.\r\n",status);
		}
	
	#endif	
		
  pgxd[group].times[offset] = pSignal->times;//保存本次延时计数器的值
	
	if( flag == 0 )
	{
		pgxd[group].stateflag &= ~(u16)(1<< offset);//更新消抖处理结果
	}
	else 
		pgxd[group].stateflag |= (u16)(1<< offset);//更新消抖处理结果
	
	return(status);
}
#endif






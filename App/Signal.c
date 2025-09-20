#include	"./User/includes.h"
#include	"./User/config.h"
#include	<stdio.h>
#include	<string.h>



#ifdef  STC15W4K48S4	

xdata PengganTypeDef 				pilepole = {0};//桩杆
xdata TiltSensorTypeDef     Tilt[4]={0};   //倾角传感器
xdata TiltAdjustTypeDef     mtc = {0};
xdata CsbTypeDef            csb_dbq = {0}; //超声波单边桥
xdata CsbTypeDef            csb_sd = {0};  //超声波隧道
#endif

xdata u16 zhuansu=0;
xdata u16 licheng=0;
static u16 T0_count = 0;//获取转速计数器的值
xdata u8 dbugGearr = 0;//挡位调试数据
//========================================================================
// 函数: u8 zuozhuanxiangdeng(FlashParameterTypeDef *pFlash)
// 描述: 获取左转向灯信号,如开启双闪，返回FLASE
// 参数：pFlash
// 返回: 开启左转返回TURE，关闭左转返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 zuozhuanxiangdeng(void)  //左转向灯 D1
{
	xdata u8 zz_pin = BSP_ReadInputDataBit(&pFlash->zz);//读取输入状态
	xdata u8 yz_pin = BSP_ReadInputDataBit(&pFlash->yz);//读取输入状态
	
	if(zz_pin == TURE && yz_pin == FALSE)
			return TURE;
	else 
			return FALSE;
}
//========================================================================
// 函数: u8 youzhuanxiangdeng(void)
// 描述: 获取右转向灯信号,如开启双闪，返回FLASE
// 参数：pFlash
// 返回: 开启右转返回TURE，关闭左转返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 youzhuanxiangdeng(void)  //右转向灯 D2
{
	
	xdata u8 zz_pin = BSP_ReadInputDataBit(&pFlash->zz);//读取输入状态
	xdata u8 yz_pin = BSP_ReadInputDataBit(&pFlash->yz);//读取输入状态
	
	if(zz_pin == FALSE && yz_pin == TURE)
			return TURE;
	else 
			return FALSE;
	
}
//========================================================================
// 函数: u8 xihuo(void)
// 描述: 获取车辆熄火状态,关联启动信号，着车之前必须出现启动信号。
//  		 可使用开关量或则发动机转速评判熄火     
// 参数：pFlash
// 返回: 车辆着车返回TURE，车辆熄火返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 xihuo(void)  //熄火 D3
{
	static u8 qidong_flag = FALSE;
	static u8 zhaoche_flag = FALSE;
	static u8 status = FALSE;
	xdata u8 qd_pin		=	BSP_ReadInputDataBit(&pFlash->qd);//读取输入状态
	xdata u8 xh_pin 	= BSP_ReadInputDataBit(&pFlash->xh);//读取输入状态
	xdata u8 xh_type	=	pFlash->xh.type;
	
	if(qd_pin == TURE)
			qidong_flag = TURE;//出现启动信号

		switch(xh_type)	
		{
			case SWITCHING_AND_START://开关量评判模式(关联启动信号)
											if((xh_pin == TURE) && (qidong_flag == TURE)) 
											{
												qidong_flag	=	FALSE;//清空启动信号标志为
												zhaoche_flag = TURE;//车辆已经着车了
												return TURE;        //
											}
											else if((xh_pin == TURE) && (zhaoche_flag == TURE))
											{	
												return TURE;
											}
											else 
											{
												zhaoche_flag = FALSE;
												return FALSE;
											}
											break;
			case SPEED_AND_START://转速评判模式(关联启动信号)
										if((T0_count > (u16)(pFlash->zs.min)) && (qidong_flag == TURE)) 
										{
											qidong_flag	=	FALSE;//清空启动信号标志为
											zhaoche_flag = TURE;//车辆已经着车了
											return TURE;        //
										}
										else if((T0_count > (u16)(pFlash->zs.min)) && (zhaoche_flag == TURE))
										{	
											return TURE;
										}
										else 
										{
											zhaoche_flag = FALSE;
											return FALSE;
										}
										break;
			case SWITCHING_AND_SPEED:				//开关量和转速评判
									  if((xh_pin == TURE) && (T0_count > (u16)(pFlash->zs.min)))
											return TURE;
										else 
											return FALSE;
											break;
			case SWITCHING_OR_SPEED:				//开关量或转速评判
										if((xh_pin == TURE) || (T0_count > (u16)(pFlash->zs.min)))
											return TURE;
										else 
											return FALSE;
											break;
			case SWITCHING:									//单开关量评判
											return xh_pin;
											break;
			case SPEED:											//单转速转速评判
											if(T0_count >= (u16)(pFlash->zs.min))
											{
												status = TURE;
											}
											else if(T0_count <= (u16)(pFlash->zs.max))
											{
												status = FALSE;
											}
											return status;
											
											break;
											
			case 6:				   //启动开关松开后采集车辆状态
										if(T0_count > (u16)(pFlash->zs.min)) 
										{
											
												if(qidong_flag == TURE) //按着马达了
												{
														
															
															if(qd_pin == FALSE) //松开马达
															{																
																	qidong_flag = FALSE;
																	zhaoche_flag = TURE;
																	return TURE;																
															}
															else
															{
																return FALSE;
															}
												 }
												 else if(zhaoche_flag == TURE) 
												 {
														 return TURE;
												 }
												else 
												 {
														 return FALSE;;
													
												 }		
									 }
									 else 
										{
											  zhaoche_flag = FALSE;
												return FALSE;
											
										}
										//break;
			default:
											return FALSE;	
		}
}
//========================================================================
// 函数: u8 shousha(void)
// 描述: 获取手刹信号
// 参数：pFlash，
// 返回: 拉手刹返回TURE，松手刹返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 shousha(void)  //手刹D4
{
	
	u8 ss_pin = BSP_ReadInputDataBit(&pFlash->ss);//读取输入状态
	
	return ss_pin;	
	
}
//========================================================================
// 函数: u8 anquandai(FlashParameterTypeDef *pFlash)
// 描述: 获取安全带信号
// 参数：pFlash，
// 返回: 系上安全带返回TURE，松开安全带返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 anquandai(void)  //安全带D5
{
	
	u8 aqd_pin = BSP_ReadInputDataBit(&pFlash->aqd);//读取输入状态
	#ifdef DEBUG1
				printf("aqd_pin = %b02d\r\n",aqd_pin);
	#endif	
	
	return aqd_pin;	
	
}
//========================================================================
// 函数: u8 chenmen_zq(void)
// 描述: 获取车门信号,左前、右前、左后、右后共四个门，
// 参数：pFlash，
// 返回: 打开车门返回FLASE，关闭车门返回0xF0,车门为高四位
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 chemen(void)  		//车门D6
{
	
	u8 cm_pin = BSP_ReadInputDataBit(&pFlash->cm);//读取输入状态
	
	if(cm_pin == TURE)
		return 0xF0;	//车门为高四位
	else 
		return FALSE;
	
}
//========================================================================
// 函数: u8 daochedeng(void)
// 描述: 获取倒车灯信号
// 参数：pFlash，
// 返回: 挂倒挡返回TURE，不在倒挡返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 daochedeng(void)  //倒车灯 D7
{
	
	u8 dcd_pin = BSP_ReadInputDataBit(&pFlash->dcd);//读取输入状态
	
	return dcd_pin;	
	
}
//========================================================================
// 函数: u8 laba(void)
// 描述: 获取喇叭信号
// 参数：pFlash，
// 返回: 按喇叭返回TURE，松开喇叭返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 laba(void)  //喇叭  D8
{
	
	u8 lb_pin = BSP_ReadInputDataBit(&pFlash->lb);//读取输入状态
	
	return lb_pin;	
	
}
//========================================================================
// 函数: u8 raoche1(void)
// 描述: 获取绕车开关1信号
// 参数：pFlash，
// 返回: 按开关返回PRESS，松开开关返回NOPRESS
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 raoche1(void)  //绕车1   D9
{

	u8 rc_pin1 = BSP_ReadMultipleDataBit(&pFlash->rc,RCPIN1);//读取输入状态
	
	(rc_pin1 == TURE)? (rc_pin1 = PRESS):(rc_pin1 = NOPRESS);//按照协议赋值
	
	return rc_pin1;	
	
}
//========================================================================
// 函数: u8 raoche1(FlashParameterTypeDef *pFlash)
// 描述: 获取绕车开关2信号
// 参数：pFlash，
// 返回: 按开关返回PRESS，松开开关返回NOPRESS
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 raoche2(void)  //绕车2   D10
{
	
	u8 rc_pin2 = BSP_ReadMultipleDataBit(&pFlash->rc,RCPIN2);//读取输入状态
	
	(rc_pin2 == TURE)? (rc_pin2 = PRESS):(rc_pin2 = NOPRESS);//按照协议赋值
	
	return rc_pin2;	
	
}
//========================================================================
// 函数: u8 wudeng(void)
// 描述: 获取雾灯开关2信号
// 参数：pFlash，
// 返回: 开雾灯返回TURE，关闭雾灯返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 wudeng(void)  //雾灯 D11
{
	
	u8 wd_pin = BSP_ReadInputDataBit(&pFlash->wd);//读取输入状态
	
	return wd_pin;	
	
}
//========================================================================
// 函数: u8 yuanguang(void)
// 描述: 获取远光开关信号
// 参数：pFlash，
// 返回: 开远光灯返回TURE，关闭远光灯返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 yuanguang(void)  //远光 D12
{
	
	u8 yg_pin = BSP_ReadInputDataBit(&pFlash->yg);//读取输入状态
	
	return yg_pin;	
	
}
//========================================================================
// 函数: u8 jinguang(void)
// 描述: 获取近光开关信号
// 参数：pFlash，
// 返回: 开近光灯返回TURE，关闭近光灯返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 jinguang(void)  //近光 D13
{
	
	u8 jg_pin = BSP_ReadInputDataBit(&pFlash->jg);//读取输入状态
	
	return jg_pin;	
	
}
//========================================================================
// 函数: u8 xiaodeng(void)
// 描述: 获取小灯开关信号
// 参数：pFlash，
// 返回: 开小灯返回TURE，关闭小灯返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 xiaodeng(void)  //小灯 D14
{
	
	u8 xd_pin = BSP_ReadInputDataBit(&pFlash->xd);//读取输入状态
	
	return xd_pin;	
	
}
//========================================================================
// 函数: u8 jiaosha(void)
// 描述: 获取脚刹信号
// 参数：pFlash，
// 返回: 踩脚刹返回TURE，松开脚刹返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 jiaosha(void)  //脚刹 D15
{
	
	u8 js_pin = BSP_ReadInputDataBit(&pFlash->js);//读取输入状态
	
	return js_pin;	
	
}
//========================================================================
// 函数: u8 yushua(void)
// 描述: 获取雨刷器信号
// 参数：pFlash，
// 返回: 开雨刷器返回TURE，关闭雨刷器返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 yushua(void)  //雨刷 D16
{
	
	u8 ys_pin = BSP_ReadInputDataBit(&pFlash->ys);//读取输入状态
	
	return ys_pin;	
	
}
//========================================================================
// 函数: u8 zuohoushi(void)
// 描述: 获取调节左后视镜信号
// 参数：pFlash，
// 返回: 调节左后视镜返回TURE，未调节返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 zuohoushi(void)  //左后视 D17
{
	
	u8 zhs_pin = BSP_ReadInputDataBit(&pFlash->zhs);//读取输入状态
	
	return zhs_pin;	
	
}
//========================================================================
// 函数: u8 qidong(void)
// 描述: 获取启动开关信号
// 参数：pFlash，
// 返回: 启动点火时返回TURE，松开启动钥匙返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 qidong(void)  //启动开关 D18
{
	static u8 mlqd_flag = 0;//模拟启动标志
	xdata u8 xh_pin 	= BSP_ReadInputDataBit(&pFlash->xh);//读取输入状态
	xdata u8 qd_pin = BSP_ReadInputDataBit(&pFlash->qd);//读取输入状态
	xdata u8 ysm_pin 	= BSP_ReadInputDataBit(&pFlash->ysm);//读取输入状态
	xdata u8 qd_type	=	pFlash->qd.type;//读取启动类型
	
	switch(qd_type)	
		{
			case 0: //要是启动有启动信号
							break;
			
			case 1: //一键启动车辆，模拟启动信号
							if((xh_pin == TURE) && (mlqd_flag == 0)) 
							{
								mlqd_flag = 1;//模拟启动信号置位
								pFlash->qd.times = 0;//启动信号模拟置位
							}
							else if(xh_pin == FALSE)//熄火后复位
							{
								mlqd_flag = 0;//模拟启动信号复位
							}
							break;	
							
			case 2:	//启动 & 钥匙门
							if((qd_pin == TURE) && (ysm_pin == TURE)) 
									return TURE;        
								else 
									return FALSE;
			default:
					return FALSE;
							break;
				
		}
		
	
	return qd_pin;	
	
}
//========================================================================
// 函数: u8 neihoushi(void)
// 描述: 获取调节内后视镜信号
// 参数：pFlash，
// 返回: 调节内后视镜返回TURE，未调节返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 neihoushi(void)  //内后视 D19
{
	
	xdata u8 nhs_pin = BSP_ReadInputDataBit(&pFlash->nhs);//读取输入状态
	
	return nhs_pin;	
	
}
//========================================================================
// 函数: u8 zuoyitiaojie(void)
// 描述: 获取调节座椅信号
// 参数：pFlash，
// 返回: 调节座椅返回TURE，未调节返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 zuoyitiaojie(void)  //座椅调节开关 D20
{
	
	u8 zytj_pin = BSP_ReadInputDataBit(&pFlash->zytj);//读取输入状态
	
	return zytj_pin;	
	
}
//========================================================================
// 函数: u8 dangwei(void)
// 描述: 获取挡位信号，传感器类型有磁感和倾角两种类型。
// 参数：pFlash，
// 返回: 	GEAR1		 1档
//				GEAR2    2档
//				GEAR3    3档
//				GEAR4    4档
//				GEAR5    5档
//				GEARR    R档
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 dangwei(void)  //挡位D21--D24
{
	u8 temp = 0;
	u8 dw_pin1 = BSP_ReadMultipleDataBit(&pFlash->dw,DWPIN1);//读取输入状态D21
	u8 dw_pin2 = BSP_ReadMultipleDataBit(&pFlash->dw,DWPIN2);//读取输入状态D22
	u8 dw_pin3 = BSP_ReadMultipleDataBit(&pFlash->dw,DWPIN3);//读取输入状态D23
	u8 dw_pin4 = BSP_ReadMultipleDataBit(&pFlash->dw,DWPIN4);//读取输入状态D24
	u8 dw_pin5 = BSP_ReadMultipleDataBit(&pFlash->dw,DWPIN5);//读取输入状态D32
	
	u8 dw_type = pFlash->dw.type;//获取传感器类型
	u8 qd_pin = BSP_ReadInputDataBit(&pFlash->qd);//读取输入状态
	u8 ysm_pin = BSP_ReadInputDataBit(&pFlash->ysm);//读取输入状态
	u8 dcd_pin = BSP_ReadInputDataBit(&pFlash->dcd);//读取倒车灯状态
	static u8 value=0;
	
	//如果倒车灯亮，不取挡位传感器的值，直接返回倒挡
	//点火时，倒挡灯会闪硕，出现启动发电机时发动机未至于空挡,需要关联启动信号
	if((dcd_pin == TURE) &&(qd_pin == FALSE)) 
	{
		return GEARR;
	}

	switch(dw_type)
	{
		case	MAGNETIC://磁传感器
										temp = (dw_pin1<<0 | dw_pin2<<1 |	dw_pin3<<2 | dw_pin4<<3);
										if(temp == 0x01) value = GEAR1;
										else if(temp == 0x02) value = GEAR2;
										else if(temp == 0x04) value = GEAR3;
										else if(temp == 0x08) value = GEAR4;
										else if(temp == 0x05) value = GEAR5;
										else if(temp == 0x0F) value = GEARR;
										else value = FALSE;
										break;
		case	ANGLE://倾角感器
										temp = (dw_pin1<<0 | dw_pin2<<1 |	dw_pin3<<2 );
										if(temp == 0x06) value = GEAR1;
										else if(temp ==  0x05) value = GEAR2;
										else if(temp ==  0x04) value = GEAR3;
										else if(temp ==  0x03) value = GEAR4;
										else if(temp ==  0x02) value = GEAR5;
										else if(temp ==  0x01) value = GEARR;
										else value = FALSE;
										break;
		case	3://张家口三轮车	 
		                if(qd_pin == TURE)  
											return	value;
										temp = (dw_pin1<<0 | dw_pin2<<1 );
										if(temp == 0x00) value = GEAR1;
										else if(temp ==  0x03) value = GEAR2;
										else value = FALSE;
										if(ysm_pin == FALSE)  value = FALSE;
										break;
		case	4://张家口二轮车
										if(qd_pin == TURE)   return	value;
										temp = ((dw_pin1<<0) | (dw_pin2<<1) );
										if(temp == 0x02) value = GEAR1;
										else if(temp ==  0x01) value = GEAR2;
										else value = FALSE;
										if(ysm_pin == FALSE)  value = FALSE;
										break;
		case	5://贵州摩托车
										temp = ( dw_pin1<<0 | dw_pin2<<1 | dw_pin3<<2 );
										dbugGearr = temp;//在软件的的“次数”位置显示采样到的挡位值
										if(temp == 0x01) value = GEAR1;
										else if(temp ==  0x02) value = GEAR2;
										else if(temp ==  0x04) value = GEAR3;
										else value = FALSE;
										break;
		case	6://重庆摩托车
										temp = (dw_pin1<<0 | dw_pin2<<1 |	dw_pin3<<2 | dw_pin4<<3);
										if(temp == 0x07) value = GEAR1;
										else if(temp == 0x02) value = GEAR2;
										else if(temp == 0x04) value = GEAR3;
										else if(temp == 0x08) value = GEAR4;
										else value = FALSE;
										break;
		case	8://自定义模式
										temp = (dw_pin1<<0 | dw_pin2<<1 |	dw_pin3<<2 | dw_pin4<<3 | dw_pin5<<4);
										dbugGearr = temp;//在软件的的“次数”位置显示采样到的挡位值
										if(temp == pFlash->dw.value[0])  value = GEAR1;//1档
										else if(temp == pFlash->dw.value[1])  value = GEAR2;//2档)
										else if(temp == pFlash->dw.value[2])  value = GEAR3;//3档)
										else if(temp == pFlash->dw.value[3])  value = GEAR4;//4档)
										else if(temp == pFlash->dw.value[4])  value = GEAR5;//5档)
										else if(temp == pFlash->dw.value[5])  value = GEARR;//R档)
										else value = 0;//空挡
										break;
		case	9://自定义模式//空挡指定标定值
										temp = (dw_pin1<<0 | dw_pin2<<1 |	dw_pin3<<2 | dw_pin4<<3 | dw_pin5<<4);
										dbugGearr = temp;//在软件的的“次数”位置显示采样到的挡位值
										if(temp == pFlash->dw.value[0])  value = GEAR1;//1档
										else if(temp == pFlash->dw.value[1])  value = GEAR2;//2档)
										else if(temp == pFlash->dw.value[2])  value = GEAR3;//3档)
										else if(temp == pFlash->dw.value[3])  value = GEAR4;//4档)
										else if(temp == pFlash->dw.value[4])  value = GEAR5;//5档)
										else if(temp == pFlash->dw.value[5])  value = GEARR;//R档)
										else if(temp == pFlash->dw.value[6])  value = 0;//空档)
										break;
//	 case	10://装甲，麦杰转接板模式
//										temp = MaijieAdapterBoard.gear;
//										if(temp == 1)  value = GEAR1;//1档
//										else if(temp == 2)  value = GEAR2;//2档)
//										else if(temp == 3)  value = GEAR3;//3档)
//										else if(temp == 4)  value = GEAR4;//4档)
//										else if(temp == 5)  value = GEAR5;//5档)
//										else if(temp == 6)  value = GEARR;//R档)
//										else if(temp == 0)  value = 0;//空档)
		case	255://调试模式
										temp = (dw_pin1<<0 | dw_pin2<<1 |	dw_pin3<<2 | dw_pin4<<3 | dw_pin5<<4);
										dbugGearr = temp;//在软件的的“次数”位置显示采样到的挡位值
										if(temp == pFlash->dw.value[0])  value = GEAR1;//1档
										else if(temp == pFlash->dw.value[1])  value = GEAR2;//2档)
										else if(temp == pFlash->dw.value[2])  value = GEAR3;//3档)
										else if(temp == pFlash->dw.value[3])  value = GEAR4;//4档)
										else if(temp == pFlash->dw.value[4])  value = GEAR5;//5档)
										else if(temp == pFlash->dw.value[5])  value = GEARR;//R档)
										else value = 0;//空挡
										break;
		default:

								value = FALSE;
								break;
			
	}
	
	return value;

	
}
//========================================================================
// 函数: u8 zuoyiyali(void)
// 描述: 获取座椅（压力）信号
// 参数：pFlash，
// 返回: 座椅有压力返回TURE，没有压力返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 zuoyiyali(void)  ///座椅（压力） D25
{
	
	xdata u8 zyyl_pin = BSP_ReadInputDataBit(&pFlash->zyyl);//读取输入状态
	
	return zyyl_pin;	
	
}
//========================================================================
// 函数: u8 lihe(FlashParameterTypeDef *pFlash)
// 描述: 获取离合器信号
// 参数：pFlash，
// 返回: 踩下离合器返回TURE，抬起离合器返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 lihe(void)   //离合 D26
{
	
	u8 lh_pin = BSP_ReadInputDataBit(&pFlash->lh);//读取输入状态
	
	return lh_pin;	
	
}
//========================================================================
// 函数: u8 yaoshimen(void)
// 描述: 获取钥匙门信号
// 参数：pFlash，
// 返回: 打开钥匙门开关返回TURE，关闭钥匙门开关返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 yaoshimen(void)   //钥匙门开关 D28
{
	
	u8 ysm_pin = BSP_ReadInputDataBit(&pFlash->ysm);//读取输入状态
	
	return ysm_pin;	
	
}
//========================================================================
// 函数: u8 fushache(void)
// 描述: 获取副刹信号
// 参数：pFlash，
// 返回: 踩下副刹车返回TURE，抬起副刹车返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 fushache(void)   //副刹车 D29
{
	
	u8 fsc_pin = BSP_ReadInputDataBit(&pFlash->fsc);//读取输入状态
	
	return fsc_pin;	
	
}
//========================================================================
// 函数: u8 chuangdong(void)
// 描述: 获取起步时闯动信号
// 参数：pFlash，
// 返回: 出线闯动返回TURE，平稳返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 chuangdong(void)   //闯动传感器 D30
{
	
	u8 cd_pin = BSP_ReadInputDataBit(&pFlash->cd);//读取输入状态
	
	return cd_pin;	
	
}
//========================================================================
// 函数: u8 raoche3(void)
// 描述: 获取绕车3信号
// 参数：pFlash，
// 返回: 按下返回TURE，未按下FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 raoche3(void)   //绕车3  D31
{
	
	u8 rc_pin3 = BSP_ReadMultipleDataBit(&pFlash->rc,RCPIN3);//读取输入状态
	
	(rc_pin3 == TURE)? (rc_pin3 = PRESS):(rc_pin3 = NOPRESS);//按照协议赋值
	
	return rc_pin3;	
	
}
//========================================================================
// 函数: u8 shijing(void)
// 描述: 获取双闪信号
// 参数：pFlash，
// 返回: 打开双闪返回TURE，关闭双闪返回FLASE
// 版本: V1.1, 2024-11-27
//========================================================================
static u8 shijing(void)   //示警开关
{
	
	u8 zz_pin = BSP_ReadInputDataBit(&pFlash->zz);//读取输入状态
	u8 yz_pin = BSP_ReadInputDataBit(&pFlash->yz);//读取输入状态
	u8 sj_pin = BSP_ReadInputDataBit(&pFlash->sj);//读取输入状态
	
	
	u8 zz_pin_gpio = BSP_GetGpioStatus(pFlash->zz.pin);//获取单片机的管脚输入状态
	u8 yz_pin_gpio = BSP_GetGpioStatus(pFlash->yz.pin);//获取单片机的管脚输入状态
	
	
	u8 sj_type =pFlash->sj.type;//获取信号接入类型
	
	static u8  openFlag = 0;
	

	if(sj_type == 1) //取示警开关的信号
	{
		return sj_pin;
	}
	else //取左右转向灯的信号
	{
		if(zz_pin_gpio == TURE && yz_pin_gpio == TURE && openFlag == 0)
	   {
				openFlag = 1;
			  return FALSE;
	   }
		 if((zz_pin == TURE) && (yz_pin == TURE)  && (openFlag == 1))
		 {
				return TURE;
		 }
     openFlag = 0;
		 return FALSE;
	}
	
}
//========================================================================
// 函数: u8 kongdang(void)
// 描述: 获取空挡信号
// 参数：pFlash，
// 返回: 空挡返回TURE，非空挡返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 kongdang(void)   //空挡
{
	
	if(dangwei() != FALSE)
			return TURE;
	else 
			return FALSE;
	
}
//========================================================================
// 函数: u8 guanchayibiao(void)
// 描述: 获取观察仪表盘信号
// 参数：pFlash，
// 返回: 观察返回TURE，没有观察返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 guanchayibiao(void)   //观察仪表盘
{
	
	u8 gcybp_pin = BSP_ReadInputDataBit(&pFlash->gcybp);//读取输入状态
	
	return gcybp_pin;	
	
}
//========================================================================
// 函数: u8 begin(void)
// 描述: 触发开始考试信号线
// 参数：pFlash，
// 返回: 刹住住返回TURE，离开返回FLASE
// 版本: V1.0, 2024-7-31
//========================================================================
static u8 begin(void)    //触发开始考试信号
{
  u8 begin_pin = BSP_ReadInputDataBit(&pFlash->begin);//读取输入状态
	
	return begin_pin;

}

//========================================================================
// 函数: u8 DBQ_LeftFront(void)
// 描述: 获取单边桥传感器左前轮信号
// 参数：pFlash，
// 返回: 在桥上返回TURE，不桥上返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 DBQ_LeftFront(void)    //单边桥左前轮状态
{
  u8 dbq_pin1 = BSP_ReadMultipleDataBit(&pFlash->dbq,LEFT_FRONT_WHEEL);//读取输入状态
	
	return dbq_pin1;

}
//========================================================================
// 函数: u8 DBQ_LeftRear(void)
// 描述: 获取单边桥传感器左后轮信号
// 参数：pFlash，
// 返回: 在桥上返回TURE，不桥上返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 DBQ_LeftRear(void)    //单边桥左后轮状态
{
  u8 dbq_pin2 = BSP_ReadMultipleDataBit(&pFlash->dbq,LEFT_REAR_WHEEL);//读取输入状态
	
	return dbq_pin2;

}
//========================================================================
// 函数: u8 DBQ_LeftRear(void)
// 描述: 获取单边桥传感器右前轮信号
// 参数：pFlash，
// 返回: 在桥上返回TURE，不桥上返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 DBQ_RightFront(void)    //单边桥右前轮状态
{
  u8 dbq_pin3 = BSP_ReadMultipleDataBit(&pFlash->dbq,RIGHT_FRONT_WHEEL);//读取输入状态
	
	return dbq_pin3;

}
//========================================================================
// 函数: u8 DBQ_RightRear(void)
// 描述: 获取单边桥传感器右后轮信号
// 参数：pFlash，
// 返回: 在桥上返回TURE，不桥上返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 DBQ_RightRear(void)    //单边桥右后轮状态
{
  u8 dbq_pin4 = BSP_ReadMultipleDataBit(&pFlash->dbq,RIGHT_REAR_WHEEL);//读取输入状态
	
	return dbq_pin4;

}
//========================================================================
// 函数: u8 DBQ_LeftMiddle(void)
// 描述: 获取单边桥传感器左挂车轮信号
// 参数：pFlash，
// 返回: 在桥上返回TURE，不桥上返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 DBQ_LeftMiddle(void)    //单边桥左挂车轮状态
{
  u8 dbq_pin5 = BSP_ReadMultipleDataBit(&pFlash->dbq,LEFT_MIDDLE_WHEEL);//读取输入状态
	
	return dbq_pin5;

}
//========================================================================
// 函数: u8 DBQ_RightMiddle(void)
// 描述: 获取单边桥传感器右挂车轮信号
// 参数：pFlash，
// 返回: 在桥上返回TURE，不桥上返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 DBQ_RightMiddle(void)    //单边桥右挂车轮状态
{
  u8 dbq_pin6 = BSP_ReadMultipleDataBit(&pFlash->dbq,RIGHT_MIDDLE_WHEEL);//读取输入状态
	
	return dbq_pin6;

}
//========================================================================
// 函数: u8 zhuansucount(void)
// 描述: 获取转速的脉冲计数值
// 参数：pFlash，
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
static u16 zhuansucount(void)    //脉冲计数
{
	static u8 times = 0;//采样等待次数（时间）
	static u16 count = 0;//获取转速计数器的值
	if(pFlash->zs.sampling_time == 0) return 0;//关闭转速采样
	if(times == pFlash->zs.sampling_time)//到达采样时间
	{
		times = 0;
		count = TH0;
		count = count<<8;	
		count = count + TL0;
		T0_count	=	count;//用于转速熄火评判
		if(pFlash->zs.bs == 0)
		{
		count = count* (pFlash->zs.bs + 1);
		}
		else
		{
			count = count* pFlash->zs.bs;
		}			
		if(count>=5000) count=800;//转速出现异常		
		TH0 = 0;//清零
		TL0 = 0;//清零	
		if ((count == 0) && (pFlash->zs.init_value >0) && (xihuo() == TURE))
		{
			count = ((pFlash->zs.init_value) *10);	//贵州特殊要求
		}
	}
	else
	{
		times++;
	}
	return count;

}
//========================================================================
// 函数: u8 lichengcount(void)
// 描述: 获取里程的脉冲计数值
// 参数：pFlash，
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
static u16 lichengcount(void)    //脉冲计数
{
	u16 count = 0;//里程初值
	u8 LC_TH =0;
	u8 LC_TL =0;
	switch(pFlash->lc.pin)
	{
		case	LC_T0: 
								 LC_TH = TH0;//使用计数器TO
								 LC_TL = TL0;
								 break;
		case	LC_T1:             //使用计数器T1
								 LC_TH = TH1;
								 LC_TL = TL1;
								 break;
#ifdef  STC15W4K48S4

		case	LC_T2:             //使用计数器T2
								 LC_TH = T2H;
								 LC_TL = T2L;
								 break;
		

		case	LC_T3:             //使用计数器T3
								 LC_TH = T3H;
								 LC_TL = T3L;
								 break;
		
		case	LC_T4:             //使用计数器T4
								 LC_TH = T4H;
								 LC_TL = T4L;
								 break;
#endif

		default:
			
					return	0;				
	}
	count = LC_TH;
	count = count<<8;	
	count = count + LC_TL;
  if(pFlash->lc.falling_ed) //查看跳变优化是否配置	
	{
		if(count >= licheng) //没有发生65536翻转
		{
			 if((count - licheng) <= pFlash->lc.falling_ed) //未发生跳变
			 {
				 	return count;
			 }
		}
		else  //发生65536翻转
		{
				if((65536  - licheng + count) <= pFlash->lc.falling_ed) //发生跳变
				{
					return count;
				}
		}
		//如果出现跳变，默认增加二个脉冲
		licheng++;
		licheng++;
		//跳变后还原计数
		LC_TH = (u8)((licheng >>8) & 0xFF);
		LC_TL = (u8)(licheng & 0xFF);
		switch(pFlash->lc.pin)
		{
							case	LC_T0: 
													 TR0=0; 				//停止
													 TH0 = LC_TH;   //使用计数器TO
													 TL0 = LC_TL;
													 TR0=1; 				//计数器0开始计数
													 break;
							case	LC_T1:             //使用计数器T1
													 TR1=0; 				//计数器1开始计数
													 TH1 = LC_TH;
													 TL1 = LC_TL;
							             TR1=1; 				//计数器1开始计数
													 break;
					#ifdef  STC15W4K48S4

							case	LC_T2:             //使用计数器T2
													 T2H = LC_TH;
													 T2L = LC_TL;
													 //AUXR |= 0x10;	//计数器2开始计数
													 break;
							

							case	LC_T3:             //使用计数器T3
													 T3H = LC_TH;
													 T3L = LC_TL;
													 //AUXR |= 0x08;	//计数器3开始计数
													 break;
							
							case	LC_T4:             //使用计数器T4
													 T4H = LC_TH;
													 T4L = LC_TL;
													 //AUXR |= 0x80;	//计数器4开始计数
													 break;
					#endif

							default:
								
										return	0;				
		}
		return licheng; //里程值保持不变
	}
	return count;

}




#ifdef  STC15W4K48S4

//========================================================================
// 函数: u8 toukui(void)
// 描述: 获取摩托车头盔状态
// 参数：pFlash，
// 返回: 戴上返回TURE，取下返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 toukui(void)    //摩托车头盔
{
  u8 tk_pin = BSP_ReadInputDataBit(&pFlash->tk);//读取输入状态
	
	return tk_pin;

}
//========================================================================
// 函数: u8 zuobashou(void)
// 描述: 获取摩托车左把手状态
// 参数：pFlash，
// 返回: 握住返回TURE，离开返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 zuobashou(void)    //摩托车左把手
{
  u8 zbs_pin = BSP_ReadInputDataBit(&pFlash->zbs);//读取输入状态
	
	return zbs_pin;

}
//========================================================================
// 函数: u8 youbashou(void)
// 描述: 获取摩托车右把手状态
// 参数：pFlash，
// 返回: 握住返回TURE，离开返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 youbashou(void)    //摩托车右把手
{
  u8 ybs_pin = BSP_ReadInputDataBit(&pFlash->ybs);//读取输入状态
	
	return ybs_pin;

}
//========================================================================
// 函数: u8 zuojiaotaban(void)
// 描述: 获取摩托车右把手状态
// 参数：pFlash，
// 返回: 踩住返回TURE，离开返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 zuojiaotaban(void)    //摩托车左脚踏板
{
  u8 zjtb_pin = BSP_ReadInputDataBit(&pFlash->zjtb);//读取输入状态
	
	return zjtb_pin;

}
//========================================================================
// 函数: u8 youtaban(void)
// 描述: 获取摩托车右把手状态
// 参数：pFlash，
// 返回: 踩住返回TURE，离开返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 youjiaotaban(void)    //摩托车右脚踏板
{
  u8 yjtb_pin = BSP_ReadInputDataBit(&pFlash->yjtb);//读取输入状态
	
	return yjtb_pin;

}
//========================================================================
// 函数: u8 youtaban(void)
// 描述: 获取摩托车前手刹状态
// 参数：pFlash，
// 返回: 刹住住返回TURE，离开返回FLASE
// 版本: V1.0, 2022-10-17
//========================================================================
static u8 qianshousha(void)    //摩托车前手刹
{
  u8 qss_pin = BSP_ReadInputDataBit(&pFlash->qss);//读取输入状态
	
	return qss_pin;

}

//========================================================================
// 函数: u8 GetHSShockSensor_value(u8 bump_usart)
// 描述: 采集高森碰杆传感器的数据
// 参数：bump_usart传感器与主板之间的串口号，FlashParameterTypeDef数据结构
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
static void GetHSShockSensor_value(u8 bump_usart)    //得到高森碰杆传感器的值
{
  xdata u8 group_i = 0;//
	xdata u8 temp = 0;//
	xdata u16 value = 0;//
	xdata u8 valuebit = 0;//
	xdata u8 reset_valuebit = 0;//
	xdata u8 i = 0;
	static u8 gor_i = 0;
	static u8 pos_i = 0;
	
	if(bump_usart == DISABLE) //硬件串口未初始化
	{
		return;
	}

	if(gor_i == 0)//轮询一轮之后，将状态全部清零，进入下一轮轮询检查
	{	
		pilepole.name   = 0;	//上传碰杆状态	清零
		pilepole.number = 0;	//上传碰杆状态	清零		
		pilepole.value  = 0;	//上传碰杆位置	清零
	}
	
	if (Serial_HighSensorShock_Analy(bump_usart) == TURE)//读取到串口数据
	{
	
				for (group_i = 0; group_i < sizeof(pFlash->bump)/sizeof(pFlash->bump[0]);group_i++)
				{
					
					if((pFlash->bump[group_i].name == 0)||(pFlash->bump[group_i].name == 0xff)) //如果没有配置项目碰杆
					{
							break;//flash里面未配置碰杆接收项目
					}
					value  =	 pFlash->bump[group_i].value;//取碰杆状态
					
					//printf("value = %h04X\r\n",value);
					
					for (i = 0 ; i< pFlash->bump[group_i].count;i++)
					{		
						valuebit  = (u16)(value >> i) & (0x0001);//取出碰杆位
						
						temp = BSP_ReadBumpDataBit(&pFlash->pgjs,group_i,valuebit,i);//消抖处理
						
						if( temp == 0 )
						{
						  pFlash->bump[group_i].value &= ~(1<< i);//更新消抖处理结果
						}
						else 
						  pFlash->bump[group_i].value |= (1<< i);//更新消抖处理结果
					}
					//printf("pole->bump[group_i].value = %h04X\r\n",pole->bump[group_i].value);
					
					
				}
				//由于需要轮询碰杆状态，所以需要第二次遍历，并且需要记录遍历的位置
				for ( ;gor_i < sizeof(pFlash->bump)/sizeof(pFlash->bump[0]);gor_i++)
				{
					
					if((pFlash->bump[gor_i].name == 0)||(pFlash->bump[gor_i].name == 0xff)) //如果没有配置项目碰杆
					{
						gor_i = 0;
						break;//flash里面未配置碰杆接收项目
					}
					
					value  =	pFlash->bump[gor_i].value;//取碰杆状态
					
					//printf("penggan.value = %h04X\r\n",value);
					
					for (;pos_i< pFlash->bump[gor_i].count;pos_i++)
					{
						
						valuebit = (u8)(value >> pos_i) & (0x0001);//取出碰杆位
						
						reset_valuebit = (u8)((pFlash->bump[gor_i].reset_value >> pos_i) & (u8)0x01);//取出桩杆状态，判断是否出现复位信号
						
						//printf("reset_valuebit = %b02d   pos_i = %b02d\r\n", reset_valuebit,pos_i);
						
						if(valuebit == 1)//出现碰杆信号
						{
								pilepole.name   = pFlash->bump[gor_i].name;			//上传碰杆状态	
							
								pilepole.number = pFlash->bump[gor_i].number;	  //上传碰杆状态		
							
								pilepole.value  = pos_i+1;	//上传碰杆位置
							
							  pFlash->bump[gor_i].reset_value |=  (1 << pos_i);//记录复位值，用于桩杆复位时，发送复位状态
							
							 // printf("pos_i = %b02d\r\n", pos_i);
							
							//	printf("pFlash->bump[%b02d].reset_value = %h04X\r\n", gor_i,pFlash->bump[gor_i].reset_value);
							
								pos_i++;//本次循环结束
							 
//							 printf("penggan.value = %h04X\r\n",value);
//							 printf("pilepole.name = %b02d\r\n",pilepole.name);
//							 printf("pilepole.number = %b02d\r\n",pilepole.number);
//							 printf("pilepole.value = %h04d\r\n",pilepole.value);
//							 printf("\r\n");
							
								return;
						}
						else if(reset_valuebit == 1)//复位信号
						{
								pilepole.name   = pFlash->bump[gor_i].name;			//清复位杆状态	
							
								pilepole.number = pFlash->bump[gor_i].number;	  //清复位杆状态		
							
								pilepole.value  = (pos_i+1)|(0x80);	//上传复位杆位置,最高位置1，代表复位
							
							  pFlash->bump[gor_i].reset_value &=  ~(1 << pos_i);//清复位状态
							
								pos_i++;//本次循环结束	
							
							
								return;							
						}

					}
					pos_i = 0;
					
				}
				gor_i = 0;
	}	
}

//========================================================================
// 函数: u8 Get24GShockSensor_value(u8 Tilt_usart)
// 描述: 获取2.4碰杆传感器的值
// 参数：u8 bump_usart，2.4G模块与主板之间连接的串口号
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
static void Get24GShockSensor_value(u8 bump_usart)    //得到2.4G碰杆碰杆传感器的值
{

	if(bump_usart != DISABLE)
	{
				//memset(&Tilt,0,sizeof(Tilt));//清空数据
				pilepole.name   = 0;	//上传碰杆状态	清零
				pilepole.number = 0;	//上传碰杆状态	清零		
				pilepole.value  = 0;	//上传碰杆位置	清零
				Serial_Sensor24GShock_Analy(bump_usart,&pilepole);
	}
}

//========================================================================
// 函数: u8 GetTiltSensor_value(u8 Tilt_usart,TiltSensorTypeDef *pTilt)
// 描述: 获取倾角传感器的值
// 参数：u8 Tilt_usart，传感器与主板之间连接的串口号， pTilt指向数据保存的指针
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
static void GetTiltSensor_value(u8 Tilt_usart,TiltSensorTypeDef *pTilt)    //倾角传感器的值
{

	if (TILT_ALL_USART != DISABLE)//全部读取
	{
			Serial_TiltSensor_Analy(Tilt_usart,pTilt);
	
//		 printf("------------------------------------------\r\n");
//		 printf("Tilt[PLACE_Q_AXLE].Roll = %h04d\r\n",	  Tilt[PLACE_Q_AXLE].Roll);
//		 printf("Tilt[PLACE_Q_AXLE].Pitch = %h04d\r\n",		Tilt[PLACE_Q_AXLE].Pitch);
//		 printf("Tilt[PLACE_Q_AXLE].Yaw = %h04d\r\n",			Tilt[PLACE_Q_AXLE].Yaw);
//		 printf("------------------------------------------\r\n");
	}
	else
	{
			if(Tilt_usart != DISABLE)//单个读取
			{
				 //memset(pTilt,0,sizeof(Tilt[0]));//清零
				 if (Serial_TiltSensor_Analy(Tilt_usart,pTilt) == TURE)//单个读取
				 {
					 if(Tilt_usart == TILT_MTC_USART) //如果是二轮摩托车
					 {
			 
							(char)pTilt->RollL -= mtc.Adjust_XL;  	//得到X轴差值低字节	
							(char)pTilt->RollH -= mtc.Adjust_XH;  	//得到X轴差值高字节	
							(char)pTilt->PitchL -= mtc.Adjust_YL;  //得到Y轴差值低字节		
							(char)pTilt->PitchH -= mtc.Adjust_YH;  //得到Y轴差值高字节	
						 
		//					printf("pTilt->RollL = %b02d\r\n",	pTilt->RollL);
		//					printf("pTilt->RollH = %b02d\r\n",	pTilt->RollH);
		//					printf("pTilt->PitchL = %b02d\r\n",	pTilt->PitchL);
		//					printf("pTilt->PitchH = %b02d\r\n",	pTilt->PitchH);	
		//					printf("\r\n");				 
					 }
				 }		 
			}
	}
}



//========================================================================
// 函数: u8 Get_csb_dbq_value(u8 csb_dbq_usart,CsbTypeDef *pcsb)
// 描述: 获取超声波（单边桥）传感器的值
// 参数：u8 csb_dbq_usart，传感器与主板之间连接的串口号， pcsb指向数据保存的指针
// 返回: 
// 版本: V1.0, 2023-5-25
//========================================================================
static void Get_csb_dbq_value(u8 csb_dbq_usart,CsbTypeDef *pcsb)    //超声波（单边桥）传感器的值
{

	if (csb_dbq_usart != DISABLE)//
	{
			Serial_csb_dbq_Analy(csb_dbq_usart,pcsb);
	}
	else
	{
		  pcsb->value0 = 0;//数据清零
		  pcsb->value1 = 0;
		  pcsb->value2 = 0;
		  pcsb->value3 = 0;
	}
}

//========================================================================
// 函数: u8 Get_csb_sd_value(u8 csb_sd_usart,CsbTypeDef *pcsb)
// 描述: 获取超声波（隧道）传感器的值
// 参数：u8 csb_sd_usart，传感器与主板之间连接的串口号， pcsb指向数据保存的指针
// 返回: 
// 版本: V1.0, 2023-5-25
//========================================================================
static void Get_csb_sd_value(u8 csb_sd_usart,CsbTypeDef *pcsb)    //超声波（隧道）传感器的值
{

	if (csb_sd_usart != DISABLE)//
	{
			Serial_csb_sd_Analy(csb_sd_usart,pcsb);
	}
	else
	{
		  pcsb->value0 = 0;//数据清零
		  pcsb->value1 = 0;
		  pcsb->value2 = 0;
		  pcsb->value3 = 0;
	}
}

//========================================================================
// 函数: void GetTilt_Adjust_vaule(void) //获取摩托车倾角传感器校准值
// 描述: 获取二轮摩托车倾角传感器校准基准值
// 参数：
// 返回: 
// 版本: V1.0, 2022-10-17
//========================================================================
void GetTilt_Adjust_vaule(void) //获取二轮摩托车倾角传感器校准值
{
	if(TILT_MTC_USART != DISABLE)
	{
		USART_ClearMsgQueueRxBuffer(TILT_MTC_USART);//清理串口缓存
	
	  BSP_ClearUsartRxBuffer(TILT_MTC_USART);//
	
	  delay_ms(200);//延时300毫秒读取基准值
		
		GetTiltSensor_value(TILT_MTC_USART,&Tilt[PLACE_MTC_AXLE]);//获取基准值
		mtc.Adjust_XL = Tilt[PLACE_MTC_AXLE].RollL;					//X轴角度低字节	
		mtc.Adjust_XH = Tilt[PLACE_MTC_AXLE].RollH;  				//X轴角度高字节
		mtc.Adjust_YL = Tilt[PLACE_MTC_AXLE].PitchL;					//Y轴角度低字节
		mtc.Adjust_YH = Tilt[PLACE_MTC_AXLE].PitchH;  				//Y轴角度高字节	
		
//		printf("mtc.Adjust_XL = %b02d\r\n",	mtc.Adjust_XL);
//		printf("mtc.Adjust_XH = %b02d\r\n",	mtc.Adjust_XH);
//		printf("mtc.Adjust_YL = %b02d\r\n",mtc.Adjust_YL);
//		printf("mtc.Adjust_YH = %b02d\r\n",mtc.Adjust_YH);	
	}
}
#endif
//========================================================================
// 函数: void DefaultConfig_Init(void)
// 描述: 初始化默认配置
// 参数：无
// 版本: V1.0, 2022-10-17
//========================================================================
void GetFlashConfig(void)
{
	
	  BSP_GetFlashConfig();	//获取配置参数
	
	  if(pFlash->zz.pin == 0)				pFlash->zz.pin 		= D1;		//左转,默认端口为D1
		if(pFlash->yz.pin == 0)				pFlash->yz.pin 		= D2;		//右转,默认端口为D2
		if(pFlash->xh.pin == 0)				pFlash->xh.pin 		= D3;		//发电机,默认端口为D3
		if(pFlash->ss.pin == 0)				pFlash->ss.pin 		= D4;		//手刹,默认端口为D4
		if(pFlash->aqd.pin == 0)			pFlash->aqd.pin 	= D5;	  //安全带,默认端口为D5	
		if(pFlash->cm.pin == 0)				pFlash->cm.pin 		= D6;		//车门,默认端口为D6
		if(pFlash->dcd.pin == 0)			pFlash->dcd.pin 	= D7;	  //倒车灯,默认端口为D7
		if(pFlash->lb.pin == 0)				pFlash->lb.pin 		= D8;		//喇叭,默认端口为D8
	
		if(pFlash->rc.pin1 == 0)			pFlash->rc.pin1 	= D9;	  //绕车1,默认端口为D9
		if(pFlash->rc.pin2 == 0)			pFlash->rc.pin2 	= D10;  //绕车2,默认端口为D10
		if(pFlash->wd.pin == 0)				pFlash->wd.pin 		= D11;	//雾灯,默认端口为D11
		if(pFlash->yg.pin == 0)				pFlash->yg.pin 		= D12;	//远光,默认端口为D12
		if(pFlash->jg.pin == 0)				pFlash->jg.pin 		= D13;	//近光,默认端口为D13	
		if(pFlash->xd.pin == 0)				pFlash->xd.pin 		= D14;	//小灯,默认端口为D14
		if(pFlash->js.pin == 0)				pFlash->js.pin 		= D15;	//脚刹,默认端口为D15
		if(pFlash->ys.pin == 0)				pFlash->ys.pin 		= D16;	//雨刷,默认端口为D16
	
		if(pFlash->zhs.pin == 0)			pFlash->zhs.pin 	= D17;  //左后视镜,默认端口为D17
		if(pFlash->qd.pin == 0)				pFlash->qd.pin 		= D18;	//启动,默认端口为D18
		if(pFlash->nhs.pin == 0)			pFlash->nhs.pin 	= D19;  //内后视镜,默认端口为D19
		if(pFlash->zytj.pin == 0)			pFlash->zytj.pin 	= D20;	//远座椅(压力,默认端口为D20
		if(pFlash->dw.pin1 == 0)			pFlash->dw.pin1 	= D21;  //挡位1,默认端口为D21	
		if(pFlash->dw.pin2 == 0)			pFlash->dw.pin2		= D22;	//挡位2,默认端口为D22
		if(pFlash->dw.pin3 == 0)			pFlash->dw.pin3 	= D23;  //挡位3,默认端口为D23
		if(pFlash->dw.pin4 == 0)			pFlash->dw.pin4 	= D24;  //挡位4,默认端口为D24
		if(pFlash->dw.pin5 == 0)			pFlash->dw.pin5 	= D0;   //挡位5,默认端口为D0，待分配
		if(pFlash->sj.pin == 0)			  pFlash->sj.pin  	= D0;   //示警开关,默认端口为D0，待分配
		
		if(pFlash->zyyl.pin == 0)			pFlash->zyyl.pin 	= D25;	//调座椅,默认端口为D25
		
#ifdef  STC15W4K48S4
		//一体板转速和离合信号端口调换
		if(pFlash->lh.pin == 0)				pFlash->lh.pin 		= D27;	//离合,默认端口为D26
		if(pFlash->zs.pin == 0)				pFlash->zs.pin 		= D26;	//转速,默认端口为D27
#endif
		
#ifdef  STC12C5A60S2
		if(pFlash->lh.pin == 0)				pFlash->lh.pin 		= D26;	//离合,默认端口为D26
		if(pFlash->zs.pin == 0)				pFlash->zs.pin 		= D27;	//转速,默认端口为D27
#endif

		if(pFlash->ysm.pin == 0)			pFlash->ysm.pin 	= D28;//钥匙开关,默认端口为D28
		if(pFlash->fsc.pin == 0)			pFlash->fsc.pin 	= D29;//副刹车,默认端口为D29	
		if(pFlash->cd.pin == 0)				pFlash->cd.pin		= D30;//闯动传感器,默认端口为D30
		//if(pFlash->dw3.pin == 0)		pFlash->dw3.pin 	= D31;//备用,默认端口为D31
		if(pFlash->rc.pin3 == 0)			pFlash->rc.pin3 	= D32;//绕车3,默认端口为D32
		if(pFlash->begin.pin == 0)		pFlash->begin.pin = D0;//开始考试信号线，默认端口为D0，待分配
		
#ifdef  STC15W4K48S4			
	
		if(pFlash->tk.pin == 0)				pFlash->tk.pin 	= D5;		//安全带,默认端口为D5			//摩托车头盔
		if(pFlash->zbs.pin == 0)			pFlash->zbs.pin 	= D17;//左后视镜,默认端口为D17		//摩托车左把手
		if(pFlash->ybs.pin == 0)			pFlash->ybs.pin	= D19;	//内后视镜,默认端口为D19		//摩托车右把手
		if(pFlash->zjtb.pin == 0)			pFlash->zjtb.pin = D6;	//车门,默认端口为D6				//摩托车左脚踏板
		if(pFlash->yjtb.pin == 0)			pFlash->yjtb.pin = D16;	//雨刷,默认端口为D16				//摩托车右脚踏板
		if(pFlash->qss.pin == 0)			pFlash->qss.pin = D29;	//副刹车,默认端口为D29			//摩托车前手刹
		
		if(pFlash-> upload.com > 4)		pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> gps.com > 4)			pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> bump_hs.com > 4)	pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> bump_24g.com > 4)	pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> titl_all.com > 4)	pFlash-> upload.com 	= DISABLE;//串口号超出范围
		
		if(pFlash-> titl_q.com > 4)		pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> titl_h.com > 4)		pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> titl_g.com > 4)		pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> titl_mtc.com > 4)	pFlash-> upload.com 	= DISABLE;//串口号超出范围
		
		if(pFlash-> csb_dbq.com > 4)	pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> csb_sd.com > 4)		pFlash-> upload.com 	= DISABLE;//串口号超出范围
		
		if(pFlash-> upload.bote > 10)		pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> gps.bote > 10)			pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> bump_hs.bote > 10)	pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> bump_24g.bote > 10)	pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> titl_all.bote > 10)	pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		
		if(pFlash-> titl_q.bote > 10)		pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> titl_h.bote > 10)		pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> titl_g.bote > 10)		pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> titl_mtc.bote > 10)	pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		
		if(pFlash-> csb_dbq.bote > 10)	pFlash-> upload.bote 	= DISABLE;//波特率超出范围
		if(pFlash-> csb_sd.bote > 10)		pFlash-> upload.bote 	= DISABLE;//波特率超出范围
#endif

#ifdef  STC12C5A60S2
		if(pFlash-> upload.com > 2)		pFlash-> upload.com 	= DISABLE;//串口号超出范围
		if(pFlash-> upload.bote > 10)		pFlash-> upload.bote 	= DISABLE;//波特率超出范围
#endif
		

		
}
//========================================================================
// 函数: void GetDataPack(u8 *pData，u16 lenth)
// 描述: 获取按照通讯协议的打包数据.
// 参数: pData指向发给串口的数据数组,lenth需要获取的数据长度.
// 返回: 无.
// 版本: V1.0, 2022-10-17
//========================================================================
void GetBaseBoardDataPack(u8 pDatabuf[], u16 lenth)
{
			
			static xdata u8 count=0;
			dbugGearr = 0;
	
#ifdef  STC15W4K48S4		
	
	    GetHSShockSensor_value(BUMP_HS_USART);//更新碰杆数据
	    Get24GShockSensor_value(BUMP_24G_USART);//更新碰杆数据
			GetTiltSensor_value(TILT_Q_USART,&Tilt[PLACE_Q_AXLE]);//采集前轴数据
			GetTiltSensor_value(TILT_H_USART,&Tilt[PLACE_H_AXLE]);//采集后轴数据
			GetTiltSensor_value(TILT_G_USART,&Tilt[PLACE_G_AXLE]);//采集挂轴数据
		  GetTiltSensor_value(TILT_MTC_USART,&Tilt[PLACE_MTC_AXLE]);	//采集二轮摩托车倾角数据
		  GetTiltSensor_value(TILT_ALL_USART,Tilt);	//采集汇总后的倾角数据
			Get_csb_dbq_value(CSB_DBQ_USART,&csb_dbq);//采集超声波（单边桥）数据
			Get_csb_sd_value(CSB_SD_USART,&csb_sd);//采集超声波（单边桥）数据

#endif
	
			zhuansu=zhuansucount();
	    licheng=lichengcount();
	
			pDatabuf[0] |= (jiaosha() << 0);		 					//脚杀
			pDatabuf[0]	|=	(lihe() << 1); 							//离合器				
			pDatabuf[0]	|=	(jinguang() << 2);						//近光灯
			pDatabuf[0]	|=	(yuanguang() << 3);					//远光灯	
			pDatabuf[0]	|=	(youzhuanxiangdeng() << 4);	//右转向			
			pDatabuf[0]	|=	(zuozhuanxiangdeng() << 5);	//左转向
    	pDatabuf[0]	|=	(shousha()<<6);							//手刹
      pDatabuf[0]	|=	(zuoyitiaojie()<<7);					//座椅
			
			pDatabuf[1]	|=	(laba() << 0);				//喇叭
			pDatabuf[1]	|=	(daochedeng() << 2);	//倒车灯开关		
			pDatabuf[1]	|=	(xiaodeng() << 3);		//小灯
			pDatabuf[1]	|=	(shijing() << 4);		//双闪
			pDatabuf[1]	|=	(anquandai() << 5);	//安全带开关    
			pDatabuf[1]	|=	(qidong() << 6);			//启动开关
			pDatabuf[1]	|=	(xihuo() << 7);			//发动机转速
	
			pDatabuf[2]	|=	chemen();		//车门
			pDatabuf[2]	|=	dangwei();		//挡位

			pDatabuf[3]	=	0;			//车速
			pDatabuf[4]	|=	(u8)zhuansu;			//发动机转速低八位   
			pDatabuf[5]	|=	(u8)(zhuansu>>8);		//发动机转速高八位
			
			pDatabuf[6] |=	(kongdang() << 0);		//空挡
			pDatabuf[6]	|=	(zuoyiyali() << 3);	//座椅开关
			
			pDatabuf[7]	|=	(yushua() << 0);			//雨刷
			pDatabuf[7]	|=	(wudeng() << 1);			//雾灯
			pDatabuf[7]	|=	(neihoushi() << 2);	//内后视
			pDatabuf[7]	|=	(zuohoushi() << 3);	//后视左
			pDatabuf[7]	|=	(jinguang() << 4);		//大灯
			pDatabuf[7]	|=	(yuanguang() << 4);	//大灯
			pDatabuf[7]	|=	(fushache() << 5);	//副刹
			pDatabuf[7]	|=	(qidong() << 6);		//启动
			//pDatabuf[8]=0;			//红绿灯状态
			//pDatabuf[9]=0;			//异常状态
			
			pDatabuf[9]	|=	(begin() << 7);			//开启上位软件自由训练（1=开启，0=结束）
			
      if(pFlash->rc.type == 0) //按钮
		  {
				pDatabuf[10]	=	raoche1();	//左前绕车
				pDatabuf[11]	=	raoche2();	//左后绕车
				pDatabuf[12]	=	raoche1();	//右前绕车
				pDatabuf[13]	=	raoche3();	//右后绕车
		  }
			else if(pFlash->rc.type == 6) 
		  {
				pDatabuf[10]	=	raoche2();	
				pDatabuf[11]	=	raoche1();	
				pDatabuf[12]	=	raoche2();	
				pDatabuf[13]	=	raoche3();	
		  }
#ifdef  STC15W4K48S4	
			else if(pFlash->rc.type == 1)//超声波传感器
			{
				pDatabuf[10]	=	csb_sd.value0;	//
				pDatabuf[11]	=	csb_sd.value1;	//
				pDatabuf[12]	=	csb_sd.value2;	//
				pDatabuf[13]	=	csb_sd.value3;	//			
			}
#endif	
			
		if(pFlash->dw.type == 255 )				//挡位自定义模式
			{
				pDatabuf[10]	=	0xff;					//
				pDatabuf[11]	=	0xff;					//
				pDatabuf[12]	=	0xff;					//
				pDatabuf[13]	=	dbugGearr;		//在软件上显示采样到的挡位值
			}
			
			pDatabuf[14]	=	(u8)(licheng>>8);			//里程计数高位//计数器0
			pDatabuf[15]	=	(u8)licheng;	        //里程计数低位//计数器0
			
			//*pDatabuf[16]	=	0;			//备用
			pDatabuf[17]	=	(pFlash->board.number_H);	//板号高位
			pDatabuf[18]	=	(pFlash->board.number_L);	//板号低位
			
#ifdef  STC15W4K48S4				
			pDatabuf[19]	=	csb_dbq.value0;			//汽车前轴左侧超声波传感器对地面的距离（单位厘米）
			pDatabuf[20]	=	csb_dbq.value1;			//汽车前轴右侧超声波传感器对地面的距离（单位厘米）
			pDatabuf[21]	=	csb_dbq.value2;			//汽车后轴左侧超声波传感器对地面的距离（单位厘米）
			pDatabuf[22]	=	csb_dbq.value3;			//汽车后轴右侧超声波传感器对地面的距离（单位厘米）
#endif
			
			pDatabuf[23]	=	0;			//牵引车中轴左侧超声波传感器对地面的距离（单位厘米）
			pDatabuf[24]	=	0;			//牵引车中轴右侧超声波传感器对地面的距离（单位厘米）
			
			pDatabuf[25]	=	0;							//训练圈数计数高位
			pDatabuf[26]	=	0;							//训练圈数计数低位
			
			if(pFlash->dw.type == 8 || pFlash->dw.type == 9)	//挡位自定义模式
				pDatabuf[26]	=	dbugGearr;		//在软件上显示采样到的挡位值


			
			pDatabuf[27]	=	0;				//车速高位
			pDatabuf[28]	=	0;				//车速低位

			pDatabuf[29]	=	0;				//离合AD值
			pDatabuf[30]	=	0;				//油门AD值
			
			pDatabuf[31]		|=	(yaoshimen() << 0); 			//钥匙开关
			pDatabuf[31]		|=	(chuangdong() << 1);			//闯动开关
			
#ifdef  STC15W4K48S4	
			pDatabuf[31]		|=	(toukui() << 2); 			//头盔（1=戴上）//摩托车
			pDatabuf[31]		|=	(zuobashou() << 3);		//左把手（1=握上）//摩托车
			pDatabuf[31]		|=	(youbashou() << 4);		//右把手（1=握上）//摩托车
			pDatabuf[31]		|=	(zuojiaotaban() << 5);			//左踏板（1=踩上）//摩托车
			pDatabuf[31]		|=	(youjiaotaban() << 6);			//右踏板（1=踩上）//摩托车
#endif
			//*pDatabuf[31]		|=	(youmentaban() << 7);	//1=油门踏板 
			
			
			pDatabuf[32]		=	FIRMWARE_NUM;			//车载单片机固件号
			pDatabuf[33]		=	0xff;			//方向盘转角,软件未使用，作为日志数据标记使用
			//*pDatabuf[33]		=	0;							//方向盘转角

			pDatabuf[34]		|=	(DBQ_LeftFront()<<7);    //单边桥左前轮信号    （1=不在桥上，0=在桥上）
			pDatabuf[34]		|=	(DBQ_LeftRear()<<6);     //单边桥左后轮信号    （1=不在桥上，0=在桥上）
			pDatabuf[34]		|=	(DBQ_RightFront()<<5);   //单边桥右前轮信号    （1=不在桥上，0=在桥上）
			pDatabuf[34]		|=	(DBQ_RightRear()<<4);    //单边桥右后轮信号    （1=不在桥上，0=在桥上）
			pDatabuf[34]		|=	(DBQ_LeftMiddle()<<3);   //单边桥左挂车轮信号  （1=不在桥上，0=在桥上）
			pDatabuf[34]		|=	(DBQ_RightMiddle()<<2);  //单边桥右挂车轮信号  （1=不在桥上，0=在桥上）
			//*pDatabuf[34]		|=	((gaosujingshi()&0x01)<<1);  		//1=高速警示标志
			//*pDatabuf[34]		|=	((gaosuanquan()&0x01)<<0);  		//1=高速安全区域//无锡检测使用
#ifdef  STC15W4K48S4	
			
			pDatabuf[35]			=		pilepole.name;				//项目类型--01桩考，02限宽门，03牵引车桩考，04连续障碍，05单边桥
			pDatabuf[36]			=		pilepole.number;			//项目编号01，02，03....
			pDatabuf[37]			=		(u8)pilepole.value;		//碰杆位置01，02，03，04，05，06...（00=无碰杆）
	
			//*pDatabuf[38]		=	0;		//接近开关
			//*pDatabuf[39]		=	0;		//科大讯飞语音状态，41正在合成，4F合成完毕，00空闲状态	
			pDatabuf[40]			=	(char)Tilt[PLACE_Q_AXLE].Pitch;	//单边桥车前Y轴数据（[有符号char]，取小数点后一位，*10倍上传）
			pDatabuf[41]			=	(char)Tilt[PLACE_H_AXLE].Pitch;	//单边桥车后Y轴数据（[有符号char]，取小数点后一位，*10倍上传）
			pDatabuf[42]			=	(char)Tilt[PLACE_G_AXLE].Pitch;	//单边桥车挂Y轴数据（[有符号char]，取小数点后一位，*10倍上传）
			pDatabuf[43]			=	(char)Tilt[PLACE_MTC_AXLE].RollL;		//（二轮摩托）车身Y轴原始数据-低位 （横滚角，右倾为正：右低左高，正。）
			pDatabuf[44]			=	(char)Tilt[PLACE_MTC_AXLE].RollH;		//（二轮摩托）车身Y轴原始数据-高位
			pDatabuf[45]			=	(char)Tilt[PLACE_MTC_AXLE].PitchL;		// (二轮摩托）车身X轴原始数据-低位 （俯仰角，仰为正）
			pDatabuf[46]			=	(char)Tilt[PLACE_MTC_AXLE].PitchH;		//（二轮摩托）车身X轴原始数据-高位
#endif		
			if(pFlash->board.device_type == 1)  //手持设备
			{
				pDatabuf[47]			|= (1<<7);
			}
			pDatabuf[47]			|=		ID_LENTH;	//主板序列号字节数（便于以后其他系列升级）
			

			
			pDatabuf[48]			=		localid[0];
			pDatabuf[49]			=		localid[1];
			pDatabuf[50]			=		localid[2];
			pDatabuf[51]			=		localid[3];
			pDatabuf[52]			=		localid[4];
			pDatabuf[53]			=		localid[5];
			pDatabuf[54]			=		localid[6];


			pDatabuf[55]		|=	(guanchayibiao() << 0);//观察仪表盘
			
#ifdef  STC15W4K48S4

			pDatabuf[55]		|=	(qianshousha() << 1);//摩托车前手刹信号
			
#endif
			
			pDatabuf[lenth-2]		=	count++;    //数据标签为数据长度的倒数第二位,每次增加1	
			
			Checksum(pDatabuf,lenth);//计算校验和		

}	

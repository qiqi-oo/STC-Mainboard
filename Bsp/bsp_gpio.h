#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H	 
#include	"./User/config.h"
#include "./Bsp/bsp_usart.h"




//定义主板信号输入口编号
#define D0 0   //待分配
#define D1 1   //左转
#define D2 2   //右转
#define D3 3   //发电机
#define D4 4   //手刹
#define D5 5   //安全带
#define D6 6   //车门
#define D7 7   //倒车灯
#define D8 8   //喇叭
#define D9 9   //绕车1
#define D10 10  //绕车2
#define D11 11  //雾灯
#define D12 12  //远光
#define D13 13  //近光
#define D14 14  //示阔
#define D15 15  //刹车
#define D16 16  //雨刷
#define D17 17  //左后视镜
#define D18 18  //点火
#define D19 19  //内后视镜
#define D20 20  //调座椅
#define D21 21  //挡位_1
#define D22 22  //挡位_2
#define D23 23  //挡位_3
#define D24 24  //挡位_4
#define D25 25  //座椅(压力)2022年11月18与调座椅互换
#define D26 26  //离合
#define D27 27  //转速
#define D28 28  //钥匙开关
#define D29 29  //副刹车
#define D30 30  //震动传感器
#define D31 31  //备用//烧写程序时设置“复位口用作IO口”
#define D32 32  //绕车3单片机复位口
#define D33 33  //左转向灯硬件开关信号
#define D34 34  //右转向灯硬件开关信号
#define D35 35  //观察仪表盘


typedef struct
{ 
	u8 pin;								//输入管脚位置 
	u8 modle; 						//输入模式
	u8 rising_ed; 				//上升沿消抖时间
	u8 falling_ed; 				//下降沿消抖时间
	u8 type;              //传感器或评判类型
	u8 times;      				//消抖计数次数,不保存在flash中
	u8 stateflag;      		//用于保存信号跳变标志,不保存在flash中
}SignalTypeDef;



typedef struct 
{ 
	u8 pin;								//输入管脚位置 
	u8 min;               //启动发动机时最小脉冲计数（大于该计数会判定为着车）
	u8 max;               //熄火后发动机的最大脉冲计数（小于该计数会判定为熄火）
	u8 bs;                //脉冲计数放大倍数
  u8 sampling_time;     //脉冲采样时间
	u8 init_value;        //初始转速 0=默认0，1=默认800
}PulseTypeDef;//脉冲

typedef struct 
{ 
	u8 pin1;            	  //信号输入管脚位置
	u8 pin2;             		//信号输入管脚位置
	u8 pin3;             		//信号输入管脚位置
	u8 pin4;             		//信号输入管脚位置
	u8 pin5;             		//信号输入管脚位置
	u8 pin6;             		//信号输入管脚位置
	u8 modle; 							//输入模式
	u8 rising_ed; 					//上升沿消抖时间
	u8 falling_ed; 					//下降沿消抖时间
	u8 type;              	//传感器类型
	u8 counts[7];      			//消抖计数次数,不保存在flash中
	u8 times;      					//消抖计数次数,不保存在flash中
	u8 stateflag;      			//用于保存信号跳变标志,不保存在flash中,用bit
	u8 value[7];      			//保存挡位的标定值
}MultSignalTypeDef;   		//同类信号，多个输入//如：单边桥开关

typedef struct 
{ 
	u8 number_L;  	//板号低位
	u8 number_H;    //板号高位
	u8 device_type;  //设备类型
	u8 trigger_mode; //主板数据触发条件

}BoradInfo;   //板卡信息


#ifdef  STC15W4K48S4

typedef struct
{ 
	u8 times[16];      		  //消抖计数次数,不保存在flash中
	u16 stateflag;      		//用于保存信号跳变标志,不保存在flash中
	
}PengGanSignalTypeDef;

typedef struct
{ 
//	u8 type;      		  //类型（差分站还是移动站）
	u8 model;      		    //型号，北云，合芯等
	
}GpsConifgTypeDef;

typedef struct 
{ 
	u8 name;  				//名称
	u8 number;  			//编号
	u8 count;  				//该项目对应的杆数量
	u8 type;  				//该项目对应的杆数量
	u16 value;  			//状态,按（位置）编码
	u16 reset_value;  //记录碰杆位置，用于桩杆复位时，发送复位指令

}PengganTypeDef;   //震动传感器


typedef struct 
{ 
	u8 value0;  				//
	u8 value1;  			  //
	u8 value2;  			  //
	u8 value3;  				//

}CsbTypeDef;        //超声波传感器

#endif





typedef struct 
{ 
	
	UsartConfTypeDef  	upload;  		//主板与工控机连接的串口
	UsartConfTypeDef  	gps;  			//主板与GPS连接的串口
	UsartConfTypeDef  	bump_hs; 		//主板与高森碰杆传感器连接的串口
	UsartConfTypeDef  	bump_24g; 	//主板与2.4G碰杆传感器连接的串口
	UsartConfTypeDef  	titl_all; 	//主板与倾角连接的串口（汇总后上传）
	UsartConfTypeDef  	titl_q;  		//主板与前轴倾角连接的串口
	UsartConfTypeDef  	titl_h;  		//主板与后轴倾角连接的串口
	UsartConfTypeDef		titl_g;  		//主板与挂轴倾角连接的串口
	UsartConfTypeDef		titl_mtc;  	//主板与二轮摩托车倾角连接的串口
	UsartConfTypeDef		network;  	//主板与二轮摩托车倾角连接的串口
	
	UsartConfTypeDef		csb_dbq;  	//主板与超声波（单边桥）传感器连接的串口
	UsartConfTypeDef		csb_sd;  	  //主板与超声波（隧道）传感器连接的串口

	
	SignalTypeDef				zytj;	  //座椅开关（调节）
	SignalTypeDef 			ss;	  	//手刹开关
	SignalTypeDef 			zz;	    //左转开关
	SignalTypeDef 			yz;	  	//右转开关
	SignalTypeDef 			yg;	  	//远光开关
	SignalTypeDef 			jg;	  	//近光开关
	SignalTypeDef 			lh;	    //离合开关
	SignalTypeDef 			js;	  	//脚刹开关
	
	SignalTypeDef 			xh;	  	//熄火开关
	SignalTypeDef 			qd;	    //启动开关
	SignalTypeDef 			aqd;	  //安全带开关
	SignalTypeDef 			sj;	    //示警开关
	SignalTypeDef 			xd;	  	//小灯开关
	SignalTypeDef 			lb;	  	//喇叭开关
	SignalTypeDef 			cm;	    //车门开关
//	SignalTypeDef 			dw1;	  //挡位1开关
//	SignalTypeDef 			dw2;	  //挡位2开关
//	
//	SignalTypeDef 			dw3;	  //挡位3开关
//	SignalTypeDef 			dw4;	  //挡位4开关
	SignalTypeDef 			zhs;	  //左后视开关
	SignalTypeDef 			nhs;	  //内后视开关
	SignalTypeDef 			fsc;	  //副刹开关
	SignalTypeDef 			wd;	    //雾灯开关
	SignalTypeDef 			ys;	  	//雨刷开关
	SignalTypeDef 			dcd;	  //倒车灯开关
	
	SignalTypeDef 			ysm;	  //钥匙门开关
//	SignalTypeDef 			rc1;	  //绕车开关1
//	SignalTypeDef 			rc2;	  //绕车开关2
//	SignalTypeDef 			rc3;	  //绕车开关3
	SignalTypeDef 			cd;	  	//闯动开关
	SignalTypeDef 			zyyl;	  //座椅开关（压力）
	PulseTypeDef				zs;	  	//转速
	SignalTypeDef 			lc;	  	//里程
	
	//SignalTypeDef 			zzxd_yj;//左转向灯硬件开关
	//SignalTypeDef 			yzxd_yj;//右转向灯硬件开关
	
	SignalTypeDef 			gcybp;		//观察仪表盘
	
	SignalTypeDef 			begin;	  //摩托车前手刹信号
	
	MultSignalTypeDef		dw;				//挡位
	MultSignalTypeDef		rc;				//绕车
	
	
	
	MultSignalTypeDef		dbq;			//单边桥信号组
	
	BoradInfo						board;		//板卡信息，板号
	
#ifdef  STC15W4K48S4
	SignalTypeDef 			tk;	  	//摩托车头盔
	SignalTypeDef 			zbs;	  //摩托车左把手
	SignalTypeDef 			ybs;	  //摩托车右把手
	SignalTypeDef 			zjtb;	  //摩托车左脚踏板
	SignalTypeDef 			yjtb;	  //摩托车右脚踏板
	SignalTypeDef 			pgjs;	  //碰杆接收
	SignalTypeDef 			qss;	  //摩托车前手刹信号
	
	PengganTypeDef     	bump[8];   //碰杆项目+单边桥项目
	
	GpsConifgTypeDef		gnss;    //gps配置
	

#endif

	


	
}FlashParameterTypeDef;//板载所有FLASH参数




//熄火信号评判的方式
#define SWITCHING_AND_START 0     //开关量+启动信号评判模式
#define SPEED_AND_START 1     	  //转速+启动信号评判模式
#define SWITCHING_AND_SPEED 2 	  //开关量和转速评判
#define SWITCHING_OR_SPEED 3  	  //开关量或转速评判
#define SWITCHING 4  						  //单开关量评判模式
#define SPEED 5      						  //单转速信号评判模式






//绕车开关

#define RCPIN1 1			//绕车开关信号线1
#define RCPIN2 2			//绕车开关信号线2
#define RCPIN3 3			//绕车开关信号线3

#define PRESS 70  		 //按下开关
#define NOPRESS 20     //没有按下

//挡位传感器

#define DWPIN1 1  		//挡位信号线1
#define DWPIN2 2      //挡位信号线2
#define DWPIN3 3  		//挡位信号线3
#define DWPIN4 4      //挡位信号线4
#define DWPIN5 5      //挡位信号线5

#define GEAR1 1  			//1档
#define GEAR2 2       //2档
#define GEAR3 3  			//3档
#define GEAR4 4       //4档
#define GEAR5 5  			//5档
#define GEARR 8       //R档

//挡位传感器类型
#define MAGNETIC	0  	//磁传感器
#define ANGLE 		1   //倾角传感器

//单边桥传感器
#define LEFT_FRONT_WHEEL		1  //左前轮传感器
#define LEFT_REAR_WHEEL			2	 //左后轮传感器
#define RIGHT_FRONT_WHEEL 	3	 //右前轮传感器
#define RIGHT_REAR_WHEEL 		4  //右后轮传感器
#define LEFT_MIDDLE_WHEEL 	5  //左挂车传感器
#define RIGHT_MIDDLE_WHEEL 	6	 //右挂车传感器

void BSP_GPIO_Init(void);
void BSP_ZhuansuCount_Init(void);
u8 BSP_ReadInputDataBit(SignalTypeDef *pSignal);
u8 BSP_ReadMultipleDataBit(MultSignalTypeDef *pSignal,u8 pin);
void BSP_LichengCount_Init(void);
u8 BSP_GetGpioStatus(u8 pin);//查询对应的IO口状态
//u8 BSP_MultipdelayOutput(MultSignalTypeDef *pSignal,u8 value);
//u8 BSP_xihuodelayOutput(SignalTypeDef *pSignal,u8 value);

#ifdef  STC15W4K48S4
u8 BSP_ReadBumpDataBit(SignalTypeDef *pSignal,u8 group,u8 value,u8 offset);
#endif

#endif


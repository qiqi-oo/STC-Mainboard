#ifndef __SINGNAL_H
#define __SINGNAL_H	 







#define PLACE_Q_AXLE 0 			//前轴
#define PLACE_H_AXLE 1			//后轴
#define PLACE_G_AXLE 2 			//挂轴
#define PLACE_MTC_AXLE 3		//摩托车
#define PLACE_ALL_AXLE 4		//所有的


#define LC_T0 1 //计数器T0
#define LC_T1 2 //计数器T1
#define LC_T2 3 //计数器T2
#define LC_T3 4 //计数器T3
#define LC_T4 5 //计数器T4

typedef struct 
{ 
	u8	RollL;					//X轴角度低字节
	u8 	RollH;  				//X轴角度高字节
	u8	PitchL;					//Y轴角度低字节
	u8 	PitchH;  				//Y轴角度高字节	
	u8	YawL;						//Z轴角度低字节
	u8 	YawH;  					//Z轴角度高字节	
	int Roll;						//滚转角
	int Pitch;  				//俯仰角
	int Yaw;  					//偏航角
}TiltSensorTypeDef;   //倾角传感器

extern xdata u16 zhuansu;

void GetFlashConfig(void);
void GetBaseBoardDataPack(u8 pDatabuf[], u16 lenth);
void GetTilt_Adjust_vaule(void); //获取二轮摩托车倾角传感器校准值
#ifdef  STC15W4K48S4	



#endif


#endif


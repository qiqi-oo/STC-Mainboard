#ifndef	__SERIAL_H
#define	__SERIAL_H


typedef struct 
{ 
	u8	Adjust_XL;					//X轴角度低字节
	u8 	Adjust_XH;  				//X轴角度高字节
	u8	Adjust_YL;					//Y轴角度低字节
	u8 	Adjust_YH;  				//Y轴角度高字节	

}TiltAdjustTypeDef;   		//



extern xdata volatile u8 start;


void SerialHandle(u8 USARTx);
void SerialDataUpload(u8 upload_usart);

#ifdef  STC15W4K48S4	
u8 Serial_HighSensorShock_Analy(u8 bump_usart); //高森HS-SKR无线震动传感器数据解析

u8 Serial_TiltSensor_Analy(u8 Tilt_usart,TiltSensorTypeDef *Tilt);//解析倾角传感器数据

void Serial_Sensor24GShock_Analy(u8 bump24g_usart,PengganTypeDef *pole); //2.4G震动传感器数据解析

void Serial_csb_dbq_Analy(u8 csb_dbq_usart,CsbTypeDef *csb); //超声波（单边桥传感器解析）

void Serial_csb_sd_Analy(u8 csb_sd_usart,CsbTypeDef *csb); //超声波（隧道传感器解析）


#endif



#endif
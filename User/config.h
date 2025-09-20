#ifndef		__CONFIG_H
#define		__CONFIG_H

//-------------------------------配置单片机型号-----------------------------------//

#define STC12C5A60S2     
//#define  STC15W4K48S4   		

////版本号22将板号改位flash配置
//V22-3过滤转速过高的问题，超过5000后，自动填充800
//V22-4增加485通讯（老主板）
//V22-5增加里程计数
//V22-6增加超声波传感器（单边桥与隧道）
//V22-8增加启动信号与钥匙信号关联。
//V24增加摩托车前手刹信号。
//V25-1优化倒挡信号，如果车辆的倒车灯亮，不取挡位传感器的值，直接返回倒挡。2024-03-28
//V26-1增加设备类型，配置参数增加device_type 2024-04-22
//V27-1增加4组传感器信号（碰杆+单边桥）输入配置  2024-04-28
//V27-2增加重庆摩托车挡位采集   2024-07-3
//V28-1增加增加挡位信号线为5根  2024-07-25，增加挡位信号线为5根
//V28-6增加挡位类型自定义接线模式，可手动配置挡位 2024-07-31
//V29-1增加触发开始考试的配置信号 2024-07-31
//V30-1增加主板数据触发方式，支持指令触发和上电触发 2024-09-3
//V30-1增加GPS端口重映射参数 2024-09-3
//V31-1增加空挡自定义标定值 2024-10-09
//V31-2增加固件版本号的打印 2024-11-15
//V32-1增加示警开关的信号输入 2024-11-27
//V32-6修改了双闪的采集条件（加了左右转信号的同步） 2024-11-27
//V32-9修改了端口号大于等于64时，直接信号状态返回0         2025-02-20
//V33-1修改了输出固件号的时间，在上传数据时，不在返回固件号 2025-04-11
//V34-0增加的里程计数脉冲跳变处理。2025-06-10
//V34-3增加转速熄火评判参数，着车和熄火参数分开。2025-06-11
//----------------------------------系统配置-------------------------------------//

//配置板号，详细定义见check.h
#define BOARD_NO   65535//实际取flash里面的配置
//单片机固件号（软件上会显示）
#define FIRMWARE_NUM 34

//次固件号，生成的hex的文件会有提示
#define FIRMWARE_MINOR_NUM 4

//校验单片机序列号,未定义不校验
//#define CHECKID 

//配置主板通讯数据长度
#define BASEBOARD_SIZE	60


//主板与上位机连接的串口 
#define DEBUG_USART 				USART1
#define DEBUG_BAUDRATE  		115200L

//控制台printf打印输出的串口号,仅输出
#define CONSOLE_USART				USART1			//可选USART1，USART2，USART3，USART4 DISABLE
#define CONSOLE_BAUDRATE		115200L			//可选2400L,4800L,9600L,19200L,38400L,115200L	
																				//如果串口被初始化别的功能，波特率可能会被覆盖

//使用调试模式时打开下面宏定义
//#define DEBUG	

//-----------------------------STC15W4K48S4编译配置-------------------------------//
#ifdef  STC15W4K48S4

//加载对应的启动文件
#include "./STC/stc15w4k48s4.h"

//网口
#define NETWORK_USART 			USART2
#define NETWORK_BAUDRATE  	115200L

#define NETWORK_STATE 			(pFlash->network.com)

//配置系统时钟频率。
#define MAIN_Fosc	22118400L
//#define MAIN_Fosc	11059200L	

//固件版本号

#define FIRMWARE_VERSION() printf("\r\nVersion:STC_15W4K_V%d.%d\r\n",(unsigned int)FIRMWARE_NUM,(unsigned int)FIRMWARE_MINOR_NUM)

#endif

//-----------------------------STC12C5A60S2编译配置-------------------------------//
#ifdef  STC12C5A60S2

//加载对应的启动文件
#include "./STC/stc12c5a60s2.h"

sbit P483=P3^7; //485使能端

//配置系统时钟频率。
#define MAIN_Fosc	11059200L	

//固件版本号

#define FIRMWARE_VERSION() printf("\r\nVersion:STC_12C5A_V%d.%d\r\n",(unsigned int)FIRMWARE_NUM,(unsigned int)FIRMWARE_MINOR_NUM)

	
#endif




#endif

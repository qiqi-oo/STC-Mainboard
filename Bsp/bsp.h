#ifndef	__BSP_H
#define	__BSP_H

#include	"./User/config.h"

#define TOTAL_IT EA


//主板与上位机连接的串口 
#define UPLOAD_USART 				(pFlash->upload.com) 
#define UPLOAD_BAUDRATE			(pFlash->upload.bote)


#ifdef  STC15W4K48S4


//主板与GPS板卡连接的串口 
#define GPS_USART 					(pFlash->gps.com)
#define GPS_BAUDRATE      	(pFlash->gps.bote)

//主板与高森碰杆传感器之间连接的串口
#define BUMP_HS_USART 			(pFlash->bump_hs.com)
#define BUMP_HS_BAUDRATE 		(pFlash->bump_hs.bote)

//主板与2.4G接收模块（碰杆传感器）之间连接的串口
#define BUMP_24G_USART 			(pFlash->bump_24g.com)
#define BUMP_24G_BAUDRATE 	(pFlash->bump_24g.bote)

//主板与（汇总后）连接的串口号
#define TILT_ALL_USART 		  (pFlash->titl_all.com)
#define TILT_ALL_BAUDRATE 	(pFlash->titl_all.bote)

//主板与车前轴连接的串口
#define TILT_Q_USART 				(pFlash->titl_q.com)
#define TILT_Q_BAUDRATE 		(pFlash->titl_q.bote)

//主板与车后轴连接的串口号
#define TILT_H_USART 				(pFlash->titl_h.com)
#define TILT_H_BAUDRATE 		(pFlash->titl_h.bote)

//主板与车挂轴连接的串口号
#define TILT_G_USART 				(pFlash->titl_g.com)
#define TILT_G_BAUDRATE			(pFlash->titl_g.bote)

//主板二轮摩托车与连接的串口
#define TILT_MTC_USART 			(pFlash->titl_mtc.com)
#define TILT_MTC_BAUDRATE 	(pFlash->titl_mtc.bote)


//主板与超声波传感器（单边桥）连接的串口号
#define CSB_DBQ_USART 				(pFlash->csb_dbq.com)
#define CSB_DBQ_BAUDRATE			(pFlash->csb_dbq.bote)

//主板与超声波传感器（隧道）连接的串口号
#define CSB_SD_USART 				(pFlash->csb_sd.com)
#define CSB_SD_BAUDRATE			(pFlash->csb_sd.bote)


#endif







void BSP_Init(void);

void Cmd_Start_Callback(void);
void Cmd_Stop_Callback(void);


#endif
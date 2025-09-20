#ifndef	__BSP_MCU_ID_H
#define	__BSP_MCU_ID_H

//单片机序列号的长度
#define ID_LENTH 7  //STC12与15长度都是7

void BSP_GetlocalId(u8 *strid);		//读取单片机ID信息


#endif


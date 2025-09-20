#ifndef __INCLUDES_H
#define __INCLUDES_H	 

//常用变量类型定义
typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

#define FALSE 0
#define TURE 1

#define		ENABLE		1
#define		DISABLE		0



#include "./Includes/gpio.h"  
#include "./Includes/flash.h" 
#include "./Includes/usart.h" 
#include "./Includes/timer.h" 
#include "./Bsp/bsp_gpio.h"
#include "./Bsp/bsp_flash.h"
#include "./Bsp/bsp_mcu_id.h"
#include "./Bsp/bsp_usart.h"
#include "./Bsp/bsp_delay.h"
#include "./Bsp/bsp.h"
#include "./App/check.h"
#include "./App/Signal.h"
#include "./App/serial.h"
#include "./App/gps.h"








#endif


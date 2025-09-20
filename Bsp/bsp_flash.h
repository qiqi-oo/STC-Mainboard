#ifndef __BSP_FLASH_H
#define __BSP_FLASH__H	

#include	"./User/config.h"
#include	"./User/includes.h"

//第一扇区0x0000--0x1ff
//第二扇区0x0200--0x3ff

#define FLASH_ADDR_UPLOAD_COM     		0x0001      //主板与上位机的连接串口号
#define FLASH_ADDR_UPLOAD_BOTE  			0x0002    	//主板与上位机的连接串口波特率
#define FLASH_ADDR_GPS_COM     				0x0003      //主板与GPS的连接串口号
#define FLASH_ADDR_GPS_BOTE  					0x0004    	//主板与GPS的连接串口波特率
#define FLASH_ADDR_GPS_COM_REMAP  		0x0014    	//串口是否重映射 0=重映射 ， 1=不映射

#define FLASH_ADDR_BUMP_HS_COM     		0x0005      //主板与高森碰杆传感器连接串口号
#define FLASH_ADDR_BUMP_HS_BOTE  			0x0006    	//主板与高森碰杆传感器连接串口波特率
#define FLASH_ADDR_BUMP_24G_COM     	0x0007      //主板与2.4G碰杆传感器连接串口号
#define FLASH_ADDR_BUMP_24G_BOTE  		0x0008    	//主板与2.4G碰杆传感器连接串口波特率


#define FLASH_ADDR_TILT_ALL_COM     	0x0009      //主板与倾角传感器的连接串口号(数据汇总后对接)
#define FLASH_ADDR_TILT_Q_COM     		0x000A      //主板与前轴倾角传感器的连接串口号（单传感器连接）
#define FLASH_ADDR_TILT_H_COM  				0x000B    	//主板与后轴倾角传感器的连接串口号（单传感器连接）
#define FLASH_ADDR_TILT_G_COM     		0x000C      //主板与挂轴倾角传感器的连接串口号（单传感器连接）
#define FLASH_ADDR_TILT_MTC_COM  			0x000D    	//主板与二轮摩托车倾角传感器的连接串口号（单传感器连接）
#define FLASH_ADDR_TILT_BOTE  				0x000E    	//主板与倾角传感器的连接串口波特率(倾角传感器波特率配置相同)

#define FLASH_ADDR_NETWORK_COM  			0x000F    	//主板网口模块功能是否启用

#define FLASH_ADDR_CSB_DBQ_COM     		0x0010      //主板与超声波（单边桥）传感器连接的串口号
#define FLASH_ADDR_CSB_DBQ_BOTE  			0x0011    	//主板与超声波（单边桥）传感器连接串口波特率

#define FLASH_ADDR_CSB_SD_COM     		0x0012      //主板与超声波（隧道）传感器连接串口号
#define FLASH_ADDR_CSB_SD_BOTE  			0x0013    	//主板与超声波（隧道）传感器连接串口波特率




#define FLASH_ADDR_ZYTJ_PIN     			0x0020      //座椅信号输入管脚位置
#define FLASH_ADDR_ZYTJ_MODEL  				0x0021      //座椅开关（调节）输入模式
#define FLASH_ADDR_ZYTJ_RISING_ED     0x0022      //座椅开关（调节）上升沿消抖
#define FLASH_ADDR_ZYTJ_FALLING_ED    0x0023      //座椅开关（调节）下降沿消抖
#define FLASH_ADDR_ZYTJ_TYPE    			0x0024      //座椅开关（调节）评判类型

#define FLASH_ADDR_SS_PIN             0x0028      //手刹开关输入管脚位置
#define FLASH_ADDR_SS_MODEL          	0x0029      //手刹开关输入模式
#define FLASH_ADDR_SS_RISING_ED       0x002A      //手刹开关上升沿消抖
#define FLASH_ADDR_SS_FALLING_ED      0x002B      //手刹开关下降沿消抖
#define FLASH_ADDR_SS_TYPE        		0x002C      //手刹开关评判类型

#define FLASH_ADDR_ZZ_PIN             0x0030      //左转开关输入管脚位置
#define FLASH_ADDR_ZZ_MODEL          	0x0031      //左转开关输入模式
#define FLASH_ADDR_ZZ_RISING_ED       0x0032      //左转开关上升沿消抖
#define FLASH_ADDR_ZZ_FALLING_ED      0x0033      //左转开关下降沿消抖
#define FLASH_ADDR_ZZ_TYPE      			0x0034      //左转开关评判类型

#define FLASH_ADDR_YZ_PIN             0x0038      //右转开关输入管脚位置
#define FLASH_ADDR_YZ_MODEL          	0x0039      //右转开关输入模式
#define FLASH_ADDR_YZ_RISING_ED       0x003A      //右转开关上升沿消抖
#define FLASH_ADDR_YZ_FALLING_ED      0x003B      //右转开关下降沿消抖
#define FLASH_ADDR_YZ_TYPE      			0x003C      //右转开关评判类型

#define FLASH_ADDR_YG_PIN             0x0040      //远光开关输入管脚位置
#define FLASH_ADDR_YG_MODEL          	0x0041      //远光开关输入模式
#define FLASH_ADDR_YG_RISING_ED       0x0042      //远光开关上升沿消抖
#define FLASH_ADDR_YG_FALLING_ED      0x0043      //远光开关下降沿消抖
#define FLASH_ADDR_YG_TYPE      			0x0044      //远光开关评判类型

#define FLASH_ADDR_JG_PIN             0x0048      //近光开关输入管脚位置
#define FLASH_ADDR_JG_MODEL          	0x0049      //近光开关输入模式
#define FLASH_ADDR_JG_RISING_ED       0x004A      //近光开关上升沿消抖
#define FLASH_ADDR_JG_FALLING_ED      0x004B      //近光开关下降沿消抖
#define FLASH_ADDR_JG_TYPE      			0x004C      //近光开关评判类型

#define FLASH_ADDR_LH_PIN             0x0050      //离合开关输入管脚位置
#define FLASH_ADDR_LH_MODEL          	0x0051      //离合开关输入模式
#define FLASH_ADDR_LH_RISING_ED       0x0052      //离合开关上升沿消抖
#define FLASH_ADDR_LH_FALLING_ED      0x0053      //离合开关下降沿消抖
#define FLASH_ADDR_LH_TYPE      			0x0054      //离合开关评判类型

#define FLASH_ADDR_JS_PIN             0x0058      //脚刹开关输入管脚位置
#define FLASH_ADDR_JS_MODEL          	0x0059      //脚刹开关输入模式
#define FLASH_ADDR_JS_RISING_ED       0x005A      //脚刹开关上升沿消抖
#define FLASH_ADDR_JS_FALLING_ED      0x005B      //脚刹开关下降沿消抖
#define FLASH_ADDR_JS_TYPE      			0x005C      //脚刹开关评判类型

#define FLASH_ADDR_XH_PIN             0x0060      //熄火开关输入管脚位置
#define FLASH_ADDR_XH_MODEL          	0x0061      //熄火开关输入模式
#define FLASH_ADDR_XH_RISING_ED       0x0062      //熄火开关上升沿消抖
#define FLASH_ADDR_XH_FALLING_ED      0x0063      //熄火开关下降沿消抖
#define FLASH_ADDR_XH_TYPE            0x0064      //评判熄火方式

#define FLASH_ADDR_QD_PIN             0x0068      //启动开关输入管脚位置
#define FLASH_ADDR_QD_MODEL          	0x0069      //启动开关输入模式
#define FLASH_ADDR_QD_RISING_ED       0x006A      //启动开关上升沿消抖
#define FLASH_ADDR_QD_FALLING_ED      0x006B      //启动开关下降沿消抖
#define FLASH_ADDR_QD_TYPE            0x006C      //启动方式

#define FLASH_ADDR_AQD_PIN            0x0070      //安全带开关输入管脚位置
#define FLASH_ADDR_AQD_MODEL          0x0071      //安全带开关输入模式
#define FLASH_ADDR_AQD_RISING_ED      0x0072      //安全带开关上升沿消抖
#define FLASH_ADDR_AQD_FALLING_ED     0x0073      //安全带开关下降沿消抖
#define FLASH_ADDR_AQD_TYPE      			0x0074      //安全带开关评判类型

#define FLASH_ADDR_SJ_PIN             0x0078      //示警开关输入管脚位置
#define FLASH_ADDR_SJ_MODEL           0x0079      //示警开关输入模式
#define FLASH_ADDR_SJ_RISING_ED       0x007A      //示警开关上升沿消抖
#define FLASH_ADDR_SJ_FALLING_ED      0x007B      //示警开关下降沿消抖
#define FLASH_ADDR_SJ_TYPE      			0x007C      //示警开关评判类型

#define FLASH_ADDR_XD_PIN             0x0080      //小灯开关输入管脚位置
#define FLASH_ADDR_XD_MODEL          	0x0081      //小灯开关输入模式
#define FLASH_ADDR_XD_RISING_ED       0x0082      //小灯开关上升沿消抖
#define FLASH_ADDR_XD_FALLING_ED      0x0083      //小灯开关下降沿消抖
#define FLASH_ADDR_XD_TYPE     				0x0084      //小灯开关评判类型

#define FLASH_ADDR_LB_PIN             0x0088      //喇叭开关输入管脚位置
#define FLASH_ADDR_LB_MODEL           0x0089      //喇叭开关输入模式
#define FLASH_ADDR_LB_RISING_ED       0x008A      //喇叭开关正上升沿消抖
#define FLASH_ADDR_LB_FALLING_ED      0x008B      //喇叭开关下降沿消抖
#define FLASH_ADDR_LB_TYPE     				0x008C      //喇叭开关评判类型

#define FLASH_ADDR_CM_PIN             0x0090      //车门开关输入管脚位置
#define FLASH_ADDR_CM_MODEL           0x0091      //车门开关输入模式
#define FLASH_ADDR_CM_RISING_ED       0x0092      //车门开关上升沿消抖
#define FLASH_ADDR_CM_FALLING_ED      0x0093      //车门开关下降沿消抖
#define FLASH_ADDR_CM_TYPE     				0x0094      //车门开关评判类型

#define FLASH_ADDR_DW_PIN1            0x0098      //挡位开关1输入管脚位置
#define FLASH_ADDR_DW_MODEL         	0x0099      //挡位开关1输入模式
#define FLASH_ADDR_DW_RISING_ED      	0x009A      //挡位开关1上升沿消抖
#define FLASH_ADDR_DW_FALLING_ED     	0x009B      //挡位开关1下降沿消抖
#define FLASH_ADDR_DW_TYPE          	0x009C      //挡位类型
#define FLASH_ADDR_DW_VALUE_1         0x009D      //1挡位标定值

#define FLASH_ADDR_DW_PIN2            0x00A0      //挡位开关2输入管脚位置
//#define FLASH_ADDR_DW2_MODEL        0x00A1      //挡位开关2输入模式
//#define FLASH_ADDR_DW2_RISING_ED    0x00A2      //挡位开关2上升沿消抖
//#define FLASH_ADDR_DW2_FALLING_ED   0x00A3      //挡位开关2下降沿消抖
#define FLASH_ADDR_DW_VALUE_2         0x00A4      //2挡位标定值

#define FLASH_ADDR_DW_PIN3            0x00A8      //挡位开关3输入管脚位置
//#define FLASH_ADDR_DW3_MODEL        0x00A9      //挡位开关3输入模式
//#define FLASH_ADDR_DW3_RISING_ED    0x00AA      //挡位开关3上升沿消抖
//#define FLASH_ADDR_DW3_FALLING_ED   0x00AB      //挡位开关3下降沿消抖
#define FLASH_ADDR_DW_VALUE_3         0x00AC      //3挡位标定值

#define FLASH_ADDR_DW_PIN4            0x00B0      //挡位开关4输入管脚位置
//#define FLASH_ADDR_DW4_MODEL        0x00B1      //挡位开关4输入模式
//#define FLASH_ADDR_DW4_RISING_ED    0x00B2      //挡位开关4上升沿消抖
#define FLASH_ADDR_DW_VALUE_ZERO   		0x00B3      //空挡标定值
#define FLASH_ADDR_DW_VALUE_4         0x00B4      //4挡位标定值
#define FLASH_ADDR_DW_PIN5            0x00B5      //挡位开关5输入管脚位置
#define FLASH_ADDR_DW_VALUE_5         0x00B6      //5挡位标定值
#define FLASH_ADDR_DW_VALUE_R         0x00B7      //倒挡位标定值

#define FLASH_ADDR_ZHS_PIN            0x00B8      //左后视开关输入管脚位置
#define FLASH_ADDR_ZHS_MODEL         	0x00B9      //左后视开关输入模式
#define FLASH_ADDR_ZHS_RISING_ED      0x00BA      //左后视开关上升沿消抖
#define FLASH_ADDR_ZHS_FALLING_ED     0x00BB      //左后视开关下降沿消抖
#define FLASH_ADDR_ZHS_TYPE          	0x00BC      //左后视类型

#define FLASH_ADDR_NHS_PIN            0x00C0      //内后视开关输入管脚位置
#define FLASH_ADDR_NHS_MODEL         	0x00C1      //内后视开关输入模式
#define FLASH_ADDR_NHS_RISING_ED      0x00C2      //内后视开关上升沿消抖
#define FLASH_ADDR_NHS_FALLING_ED     0x00C3      //内后视开关下降沿消抖
#define FLASH_ADDR_NHS_TYPE          	0x00C4      //内后视类型

#define FLASH_ADDR_FSC_PIN            0x00C8      //副刹开关输入管脚位置
#define FLASH_ADDR_FSC_MODEL          0x00C9      //副刹开关输入模式
#define FLASH_ADDR_FSC_RISING_ED      0x00CA      //副刹开关上升沿消抖
#define FLASH_ADDR_FSC_FALLING_ED     0x00CB      //副刹开关下降沿消抖
#define FLASH_ADDR_FSC_TYPE          	0x00CC      //副刹视类型

#define FLASH_ADDR_WD_PIN             0x00D0      //雾灯开关输入管脚位置
#define FLASH_ADDR_WD_MODEL          	0x00D1      //雾灯开关输入模式
#define FLASH_ADDR_WD_RISING_ED       0x00D2      //雾灯开关上升沿消抖
#define FLASH_ADDR_WD_FALLING_ED      0x00D3      //雾灯开关下降沿消抖
#define FLASH_ADDR_WD_TYPE          	0x00D4      //雾灯评判类型和方式

 
#define FLASH_ADDR_YS_PIN             0x00D8      //雨刷开关输入管脚位置
#define FLASH_ADDR_YS_MODEL          	0x00D9      //雨刷开关输入模式
#define FLASH_ADDR_YS_RISING_ED       0x00DA      //雨刷开关上升沿消抖
#define FLASH_ADDR_YS_FALLING_ED      0x00DB      //雨刷开关下降沿消抖
#define FLASH_ADDR_YS_TYPE          	0x00DC      //雨刷评判类型和方式

#define FLASH_ADDR_DCD_PIN            0x00E0      //倒车灯开关输入管脚位置
#define FLASH_ADDR_DCD_MODEL         	0x00E1      //倒车灯开关输入模式
#define FLASH_ADDR_DCD_RISING_ED      0x00E2      //倒车灯开关上升沿消抖
#define FLASH_ADDR_DCD_FALLING_ED     0x00E3      //倒车灯开关下降沿消抖
#define FLASH_ADDR_DCD_TYPE          	0x00E4      //倒车灯评判类型和方式

#define FLASH_ADDR_YSM_PIN            0x00E8      //钥匙门开关输入管脚位置
#define FLASH_ADDR_YSM_MODEL         	0x00E9      //钥匙门开关输入模式
#define FLASH_ADDR_YSM_RISING_ED      0x00EA      //钥匙门开上升沿消抖
#define FLASH_ADDR_YSM_FALLING_ED     0x00EB      //钥匙门开关下降沿消抖
#define FLASH_ADDR_YSM_TYPE          	0x00EC      //钥匙门评判类型和方式

#define FLASH_ADDR_RC_PIN1            0x00F0      //绕车开关1输入管脚位置
#define FLASH_ADDR_RC_MODEL          	0x00F1      //绕车开关1关输入模式
#define FLASH_ADDR_RC_RISING_ED      	0x00F2      //绕车开关1上升沿消抖
#define FLASH_ADDR_RC_FALLING_ED     	0x00F3      //绕车开关1下降沿消抖
#define FLASH_ADDR_RC_TYPE           	0x00F4      //绕车模式

#define FLASH_ADDR_RC_PIN2            0x00F8      //绕车开关2输入管脚位置
//#define FLASH_ADDR_RC2_MODEL         	0x00F9      //绕车开关2关输入模式
//#define FLASH_ADDR_RC2_RISING_ED      0x00FA      //绕车开关2上升沿消抖
//#define FLASH_ADDR_RC2_FALLING_ED     0x00FB      //绕车开关2下降沿消抖

#define FLASH_ADDR_RC_PIN3            0x0100      //绕车开关3输入管脚位置
//#define FLASH_ADDR_RC3_MODEL         	0x0101      //绕车开关3关输入模式
//#define FLASH_ADDR_RC3_RISING_ED      0x0102      //绕车开关3上升沿消抖
//#define FLASH_ADDR_RC3_FALLING_ED     0x0103      //绕车开关3下降沿消抖

#define FLASH_ADDR_CD_PIN             0x0108      //闯动开关输入管脚位置
#define FLASH_ADDR_CD_MODEL          	0x0109      //闯动开关关输入模式
#define FLASH_ADDR_CD_RISING_ED      	0x010A      //闯动开关上升沿消抖
#define FLASH_ADDR_CD_FALLING_ED     	0x010B      //闯动开关下降沿消抖
#define FLASH_ADDR_CD_TYPE          	0x010C      //闯动评判类型和方式

#define FLASH_ADDR_ZYYL_PIN           0x0110      //座椅开关（压力）输入管脚位置
#define FLASH_ADDR_ZYYL_MODEL        	0x0111      //座椅开关（压力）关输入模式
#define FLASH_ADDR_ZYYL_RISING_ED     0x0112      //座椅开关（压力）上升沿消抖
#define FLASH_ADDR_ZYYL_FALLING_ED    0x0113      //座椅开关（压力）下降沿消抖
#define FLASH_ADDR_ZYYL_TYPE          0x0114      //座椅开关（压力）评判类型和方式

//#define FLASH_ADDR_ZSJS_PIN           0x0118      //转速计数输入管脚位置
//#define FLASH_ADDR_ZSJS_MODEL         0x0119      //转速计数关输入模式
//#define FLASH_ADDR_ZSJS_RISING_ED     0x011A      //转速计数下降沿消抖
//#define FLASH_ADDR_ZSJS_FALLING_ED    0x011B      //转速计数上升沿消抖
//#define FLASH_ADDR_ZSJS_TYPE          0x011C      //转速计数评判类型和方式

#define FLASH_ADDR_LCJS_PIN           0x0120      //里程计数输入管脚位置
#define FLASH_ADDR_LCJS_MODEL         0x0121      //里程计数关输入模式
#define FLASH_ADDR_LCJS_RISING_ED     0x0122      //里程
#define FLASH_ADDR_LCJS_FALLING_ED    0x0123      //跳变范围
#define FLASH_ADDR_LCJS_TYPE   				0x0124      //里程计数评判类型和方式

#define FLASH_ADDR_ZZXDYJ_PIN         0x0128      //左转向灯硬件开关输入管脚位置
#define FLASH_ADDR_ZZXDYJ_MODEL       0x0129      //左转向灯硬件开关输入模式
#define FLASH_ADDR_ZZXDYJ_RISING_ED   0x012A      //左转向灯硬件开关上升沿消抖
#define FLASH_ADDR_ZZXDYJ_FALLING_ED  0x012B      //左转向灯硬件开关下降沿消抖
#define FLASH_ADDR_ZZXDYJ_TYPE        0x012C     	//左转向灯硬件开关评判类型和方式

#define FLASH_ADDR_YZXDYJ_PIN         0x0130      //右转向灯硬件开关输入管脚位置
#define FLASH_ADDR_YZXDYJ_MODEL       0x0131      //右转向灯硬件开关输入模式
#define FLASH_ADDR_YZXDYJ_RISING_ED   0x0132      //右转向灯硬件开关上升沿消抖
#define FLASH_ADDR_YZXDYJ_FALLING_ED  0x0133      //右转向灯硬件开关下降沿消抖
#define FLASH_ADDR_YZXDYJ_TYPE        0x0134     	//右转向灯硬件开关评判类型和方式


#define FLASH_ADDR_DBQ_FALLING_ED     0x0136      //单边桥传感器下降沿消抖
#define FLASH_ADDR_DBQ_TYPE           0x0137      //单边桥传感器类型

#define FLASH_ADDR_DBQ_PIN1      			0x0138      //单边桥左前轮开关输入管脚位置
#define FLASH_ADDR_DBQ_PIN2      			0x0139      //单边桥左后轮开关输入管脚位置
#define FLASH_ADDR_DBQ_PIN3      			0x013A      //单边桥右前轮开关输入管脚位置
#define FLASH_ADDR_DBQ_PIN4      			0x013B      //单边桥右后轮开关输入管脚位置
#define FLASH_ADDR_DBQ_PIN5      			0x013C      //单边桥左挂轮开关输入管脚位置
#define FLASH_ADDR_DBQ_PIN6      			0x013D      //单边桥右挂轮开关输入管脚位置
#define FLASH_ADDR_DBQ_MODEL     			0x013E      //单边桥传感器开关输入模式
#define FLASH_ADDR_DBQ_RISING_ED   		0x013F      //单边桥传感器开关上升沿消抖

#define FLASH_ADDR_GCYBP_PIN          0x0140      //观察仪表盘开关输入管脚位置
#define FLASH_ADDR_GCYBP_MODEL       	0x0141      //观察仪表盘开关输入模式
#define FLASH_ADDR_GCYBP_RISING_ED   	0x0142      //观察仪表盘开关上升沿消抖
#define FLASH_ADDR_GCYBP_FALLING_ED  	0x0143      //观察仪表盘开关下降沿消抖
#define FLASH_ADDR_GCYBP_TYPE        	0x0144     	//观察仪表盘评判类型和方式

#define FLASH_ADDR_TK_PIN          		0x0148      //摩托车头盔开关输入管脚位置
#define FLASH_ADDR_TK_MODEL       		0x0149      //摩托车头盔开关输入模式
#define FLASH_ADDR_TK_RISING_ED   		0x014A      //摩托车头盔开关上升沿消抖
#define FLASH_ADDR_TK_FALLING_ED  		0x014B      //摩托车头盔开关下降沿消抖
#define FLASH_ADDR_TK_TYPE        		0x014C     	//摩托车头盔评判类型和方式

#define FLASH_ADDR_ZBS_PIN          	0x0150      //摩托车左把手开关输入管脚位置
#define FLASH_ADDR_ZBS_MODEL       		0x0151      //摩托车左把手开关输入模式
#define FLASH_ADDR_ZBS_RISING_ED   		0x0152      //摩托车左把手开关上升沿消抖
#define FLASH_ADDR_ZBS_FALLING_ED  		0x0153      //摩托车左把手开关下降沿消抖
#define FLASH_ADDR_ZBS_TYPE        		0x0154     	//摩托车左把手评判类型和方式

#define FLASH_ADDR_YBS_PIN          	0x0158      //摩托车右把手开关输入管脚位置
#define FLASH_ADDR_YBS_MODEL       		0x0159      //摩托车右把手开关输入模式
#define FLASH_ADDR_YBS_RISING_ED   		0x015A      //摩托车右把手开关上升沿消抖
#define FLASH_ADDR_YBS_FALLING_ED  		0x015B      //摩托车右把手开关下降沿消抖
#define FLASH_ADDR_YBS_TYPE        		0x015C     	//摩托车右把手评判类型和方式

#define FLASH_ADDR_ZJTB_PIN          	0x0160      //摩托车左踏板开关输入管脚位置
#define FLASH_ADDR_ZJTB_MODEL       	0x0161      //摩托车左踏板开关输入模式
#define FLASH_ADDR_ZJTB_RISING_ED   	0x0162      //摩托车左踏板开关上升沿消抖
#define FLASH_ADDR_ZJTB_FALLING_ED  	0x0163      //摩托车左踏板开关下降沿消抖
#define FLASH_ADDR_ZJTB_TYPE        	0x0164     	//摩托车左踏板评判类型和方式

#define FLASH_ADDR_YJTB_PIN          	0x0168      //摩托车右踏板开关输入管脚位置
#define FLASH_ADDR_YJTB_MODEL       	0x0169      //摩托车右踏板开关输入模式
#define FLASH_ADDR_YJTB_RISING_ED   	0x016A      //摩托车右踏板开关上升沿消抖
#define FLASH_ADDR_YJTB_FALLING_ED  	0x016B      //摩托车右踏板开关下降沿消抖
#define FLASH_ADDR_YJTB_TYPE        	0x016C     	//摩托车右踏板评判类型和方式

#define FLASH_ADDR_PGJS_PIN          	0x0170      //碰杆接收管脚位置
#define FLASH_ADDR_PGJS_MODEL       	0x0171      //碰杆接收输入模式
#define FLASH_ADDR_PGJS_RISING_ED   	0x0172      //碰杆接收上升沿消抖
#define FLASH_ADDR_PGJS_FALLING_ED  	0x0173      //碰杆接收下降沿消抖
#define FLASH_ADDR_PGJS_TYPE        	0x0174     	//碰杆接收类型和方式

//#define FLASH_ADDR_TILT_ADJUST_XL     0x0171      //倾角传感器校准值XL
//#define FLASH_ADDR_TILT_ADJUST_XH     0x0172      //倾角传感器校准值XH
//#define FLASH_ADDR_TILT_ADJUST_YL     0x0173      //倾角传感器校准值YL
//#define FLASH_ADDR_TILT_ADJUST_YH    	0x0174      //倾角传感器校准值YH
//#define FLASH_ADDR_TILT_ADJUST_ZERO   0x0175      //错误校验写1时自动校准零偏
//#define FLASH_ADDR_TILT_TYPE     			0x0176      //倾角传感器类型


#define FLASH_ADDR_PGJS_1_NAME        0x0180     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_1_N0     			0x0181     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_1_COUNT      	0x0182     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_1_TYPE      	0x0183     	//项目杆的类型

#define FLASH_ADDR_PGJS_2_NAME       	0x0184     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_2_N0    			0x0185     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_2_COUNT      	0x0186     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_2_TYPE      	0x0187     	//项目杆的类型

#define FLASH_ADDR_PGJS_3_NAME       	0x0188     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_3_N0     			0x0189     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_3_COUNT      	0x018A     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_3_TYPE      	0x018B     	//项目杆的类型

#define FLASH_ADDR_PGJS_4_NAME       	0x018C     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_4_N0    			0x018D     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_4_COUNT     	0x018E     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_4_TYPE      	0x018F     	//项目杆的类型


#define FLASH_ADDR_QSS_PIN          	0x0190      //摩托车前手刹管脚位置
#define FLASH_ADDR_QSS_MODEL       		0x0191      //摩托车前手刹输入模式
#define FLASH_ADDR_QSS_RISING_ED   		0x0192      //摩托车前手刹上升沿消抖
#define FLASH_ADDR_QSS_FALLING_ED  		0x0193      //摩托车前手刹下降沿消抖
#define FLASH_ADDR_QSS_TYPE        		0x0194     	//摩托车前手刹和方式

#define FLASH_ADDR_PGJS_5_NAME       	0x0198     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_5_N0    			0x0199     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_5_COUNT     	0x019A     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_5_TYPE      	0x019B     	//项目杆的类型

#define FLASH_ADDR_PGJS_6_NAME       	0x019C     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_6_N0    			0x019D     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_6_COUNT     	0x019E     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_6_TYPE      	0x019F     	//项目杆的类型

#define FLASH_ADDR_PGJS_7_NAME       	0x01A0     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_7_N0    			0x01A1     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_7_COUNT     	0x01A2     	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_7_TYPE      	0x01A3     	//项目杆的类型

#define FLASH_ADDR_PGJS_8_NAME       	0x01A4     	//碰杆接收项目名称
#define FLASH_ADDR_PGJS_8_N0    			0x01A5     	//碰杆接收项目编号
#define FLASH_ADDR_PGJS_8_COUNT     	0x01A6    	//项目杆的数量,按照绑定顺序，依次绑定
#define FLASH_ADDR_PGJS_8_TYPE      	0x01A7     	//项目杆的类型


#define FLASH_ADDR_BEGIN_PIN          0x01A8      //开始考试信号线输入位置
#define FLASH_ADDR_BEGIN_MODEL       	0x01A9      //开始考试信号线输入模式
#define FLASH_ADDR_BEGIN_RISING_ED   	0x01AA      //开始考试信号线上升沿消抖
#define FLASH_ADDR_BEGIN_FALLING_ED  	0x01AB      //开始考试信号线下降沿消抖
#define FLASH_ADDR_BEGIN_TYPE        	0x01AC    	//开始考试信号线类型和方式




#define FLASH_ADDR_ZS_IDLIN_MIN       0x01D0      //启动发动机时最小脉冲计数（大于该计数会判定为车辆启动）
#define FLASH_ADDR_ZS_BS              0x01D1      //脉冲计数倍数
#define FLASH_ADDR_ZS_SAMPLING_TIME 	0x01D2      //脉冲采样时间
#define FLASH_ADDR_ZS_INIT_VALUE     	0x01D3      //初始转速 0=默认0，1=默认800
#define FLASH_ADDR_ZS_PIN							0x01D4      //转速输入管脚
#define FLASH_ADDR_ZS_XH_MAX					0x01D5      //熄火后发动机的最大脉冲计数（小于该计数会判定为车辆熄火）

#define FLASH_ADDR_GNSS_MODEL         0x01D8      //gps的型号


//#define adds_Card_data_mode       0x01E0     		//主板发送数据模式0=主板数据，1=主板数据+GPS数据
//#define adds_Card_com_mode        0x01E1     		//主板通讯模式0=232模式通讯，1=485方式通讯

#define FLASH_ADDR_CAR_BRAND_MODEL    0x01FA     	//车辆的品牌型号，用于CAN采集(STM32使用)
#define FLASH_ADDR_TRIGGER_MODE  			0x01FB     	//主板数据触发机制，0=指令触发 1=上电触发
#define FLASH_ADDR_DEVICE_TYPE       	0x01FC     	//设备类型 1= 手持设备 0=车载板卡

#define FLASH_ADDR_BOARD_ID_L       	0x01FD     	//板号地位
#define FLASH_ADDR_BOARD_ID_H        	0x01FE     	//板号高位

#define FLASH_ADDR_END              	0x01ff     	//结束地址


//指针常量，指向flash数据在内存中的首地址，全局变量可在各个文件中使用
extern xdata FlashParameterTypeDef const *const pFlash;
   
void BSP_GetFlashConfig();
void BSP_FlashWriteByte(u16 addr, u8 value);



#endif


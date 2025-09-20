#include "./User/includes.h"

xdata FlashParameterTypeDef FlashCacheBuf = {0};//用于储存FLASH中的的数据（将flash的数据读到SRAM中）

//指针常量，指向flash数据在内存中的首地址，全局变量可在各个文件中使用
xdata FlashParameterTypeDef const *const pFlash  =  &FlashCacheBuf;
//========================================================================
// 函数:BSP_GetFlashConfig(SignalLineTotalTypeDef *pFlash)
// 描述: 读取flash里面的配置参数
// 参数：*pFlash指向需要保存数据的内存首地址3
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_GetFlashConfig(void)
{

			//主板与上位机的连接串口号
			pFlash->upload.com       			=     IapReadByte(FLASH_ADDR_UPLOAD_COM);     		//主板与上位机的连接串口号
			pFlash->upload.bote         	=     IapReadByte(FLASH_ADDR_UPLOAD_BOTE);      	//主板与上位机的连接串口波特率
	
			//主板与GPS的连接串口号
			pFlash->gps.com       				=     IapReadByte(FLASH_ADDR_GPS_COM);     				//主板与GPS的连接串口号
			pFlash->gps.bote          		=     IapReadByte(FLASH_ADDR_GPS_BOTE);      			//主板与GPS的连接串口波特率
			pFlash->gps.remap          		=     IapReadByte(FLASH_ADDR_GPS_COM_REMAP);      //主板与GPS的连接串口重映射
	
	
	
			//主板与高森碰杆传感器连接的串口
			pFlash->bump_hs.com       		=     IapReadByte(FLASH_ADDR_BUMP_HS_COM);     		//主板与上位机的连接串口号
			pFlash->bump_hs.bote         	=     IapReadByte(FLASH_ADDR_BUMP_HS_BOTE);      	//主板与上位机的连接串口波特率
	
			//主板与2.4G碰杆传感器连接的串口
			pFlash->bump_24g.com       		=     IapReadByte(FLASH_ADDR_BUMP_24G_COM);     	//主板与2.4G碰杆传感器连接串口号
			pFlash->bump_24g.bote        	=     IapReadByte(FLASH_ADDR_BUMP_24G_BOTE);      //主板与2.4G碰杆传感器连接串口波特率
	
	
			//主板与倾角连接的串口（汇总后上传）
			pFlash->titl_all.com       		=     IapReadByte(FLASH_ADDR_TILT_ALL_COM);    		//主板与倾角连接的串口（汇总后上传）串口号
			pFlash->titl_all.bote       	=     IapReadByte(FLASH_ADDR_TILT_BOTE);      		//主板与倾角连接的串口波特率
	
			//主板与前轴倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_q.com       			=     IapReadByte(FLASH_ADDR_TILT_Q_COM);     		//主板与前轴倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_q.bote       		=     IapReadByte(FLASH_ADDR_TILT_BOTE);      	  //主板与倾角连接的串口波特率
			
			//主板与后轴倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_h.com       			=     IapReadByte(FLASH_ADDR_TILT_H_COM);     		//主板与后轴倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_h.bote       		=     IapReadByte(FLASH_ADDR_TILT_BOTE);      	  //主板与倾角连接的串口波特率
			
			//主板与挂轴倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_g.com       			=     IapReadByte(FLASH_ADDR_TILT_G_COM);     		//主板与挂轴倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_g.bote       		=     IapReadByte(FLASH_ADDR_TILT_BOTE);      	  //主板与倾角连接的串口波特率
			
			//主板与二轮摩托车倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_mtc.com       		=     IapReadByte(FLASH_ADDR_TILT_MTC_COM);     	//主板与二轮摩托车倾角传感器的连接串口号（单传感器连接）
			pFlash->titl_mtc.bote       	=     IapReadByte(FLASH_ADDR_TILT_BOTE);      	  //主板与倾角连接的串口波特率
			
			//主板网口模块
			pFlash->network.com       		=     IapReadByte(FLASH_ADDR_NETWORK_COM);     		//主板网络模块是否启用
			
			
		  //主板与超声波（单边桥）传感器的连接串口号（单传感器连接）
			pFlash->csb_dbq.com       		=     IapReadByte(FLASH_ADDR_CSB_DBQ_COM);     		//主板与挂轴倾角传感器的连接串口号（单传感器连接）
			pFlash->csb_dbq.bote       		=     IapReadByte(FLASH_ADDR_CSB_DBQ_BOTE);      	  //主板与倾角连接的串口波特率
			
			//主板与超声波（隧道）传感器的连接串口号（单传感器连接）
			pFlash->csb_sd.com       		  =     IapReadByte(FLASH_ADDR_CSB_SD_COM);     	//主板与二轮摩托车倾角传感器的连接串口号（单传感器连接）
			pFlash->csb_sd.bote       	  =     IapReadByte(FLASH_ADDR_CSB_SD_BOTE);      	  //主板与倾角连接的串口波特率
	
			//座椅开关（调节）
			pFlash->zytj.pin       		 		=     IapReadByte(FLASH_ADDR_ZYTJ_PIN);     			//座椅开关（调节）输入管脚位置
			pFlash->zytj.modle           	=     IapReadByte(FLASH_ADDR_ZYTJ_MODEL);      		//座椅开关（调节）输入模式
			pFlash->zytj.rising_ed     		=     IapReadByte(FLASH_ADDR_ZYTJ_RISING_ED);    	//座椅开关（调节）上升沿消抖
			pFlash->zytj.falling_ed     	=     IapReadByte(FLASH_ADDR_ZYTJ_FALLING_ED);  	//座椅开关（调节）下降沿消抖
			pFlash->zytj.type     				=     IapReadByte(FLASH_ADDR_ZYTJ_TYPE);  				//座椅开关（调节）评判类型和方式
			//手刹开关
	    pFlash->ss.pin               	=     IapReadByte(FLASH_ADDR_SS_PIN);           	//手刹开关输入管脚位置
			pFlash->ss.modle             	=     IapReadByte(FLASH_ADDR_SS_MODEL);        		//手刹开关输入模式
			pFlash->ss.rising_ed         	=     IapReadByte(FLASH_ADDR_SS_RISING_ED);      	//手刹开关上升沿消抖
			pFlash->ss.falling_ed        	=     IapReadByte(FLASH_ADDR_SS_FALLING_ED);    	//手刹开关下降沿消抖
			pFlash->ss.type     					=     IapReadByte(FLASH_ADDR_SS_TYPE);  					//手刹开关评判类型和方式
			//左转开关
		  pFlash->zz.pin               	=     IapReadByte(FLASH_ADDR_ZZ_PIN);           	//左转开关输入管脚位置
			pFlash->zz.modle             	=     IapReadByte(FLASH_ADDR_ZZ_MODEL);        		//左转开关输入模式
			pFlash->zz.rising_ed         	=     IapReadByte(FLASH_ADDR_ZZ_RISING_ED);      	//左转开关上升沿消抖
			pFlash->zz.falling_ed        	=     IapReadByte(FLASH_ADDR_ZZ_FALLING_ED);    	//左转开关下降沿消抖
			pFlash->zz.type     					=     IapReadByte(FLASH_ADDR_ZZ_TYPE);  					//左转开关评判类型和方式
			//右转开关
			pFlash->yz.pin               	=     IapReadByte(FLASH_ADDR_YZ_PIN);           	//右转开关输入管脚位置
			pFlash->yz.modle             	=     IapReadByte(FLASH_ADDR_YZ_MODEL);        		//右转开关输入模式
			pFlash->yz.rising_ed         	=     IapReadByte(FLASH_ADDR_YZ_RISING_ED);      	//右转开关上升沿消抖
			pFlash->yz.falling_ed        	=     IapReadByte(FLASH_ADDR_YZ_FALLING_ED);    	//右转开关下降沿消抖
			pFlash->yz.type     					=     IapReadByte(FLASH_ADDR_YZ_TYPE);  					//右转开关评判类型和方式
			//远光开关
			pFlash->yg.pin               	=     IapReadByte(FLASH_ADDR_YG_PIN);           	//远光开关输入管脚位置
			pFlash->yg.modle             	=     IapReadByte(FLASH_ADDR_YG_MODEL);        		//远光开关输入模式
			pFlash->yg.rising_ed         	=     IapReadByte(FLASH_ADDR_YG_RISING_ED);      	//远光开关上升沿消抖
			pFlash->yg.falling_ed       	=     IapReadByte(FLASH_ADDR_YG_FALLING_ED);    	//远光开关下降沿消抖
			pFlash->yg.type     					=     IapReadByte(FLASH_ADDR_YG_TYPE);  					//远光开关评判类型和方式
			//近光开关
			pFlash->jg.pin               	=     IapReadByte(FLASH_ADDR_JG_PIN);           	//近光开关输入管脚位置
			pFlash->jg.modle             	=     IapReadByte(FLASH_ADDR_JG_MODEL);        		//近光开关输入模式
			pFlash->jg.rising_ed         	=     IapReadByte(FLASH_ADDR_JG_RISING_ED);       //近光开关上升沿消抖
			pFlash->jg.falling_ed        	=     IapReadByte(FLASH_ADDR_JG_FALLING_ED);    	//近光开关下降沿消抖
			pFlash->jg.type     					=     IapReadByte(FLASH_ADDR_JG_TYPE);  					//近光开关评判类型和方式
			//离合开关
		  pFlash->lh.pin               	=     IapReadByte(FLASH_ADDR_LH_PIN);           	//离合开关输入管脚位置
			pFlash->lh.modle             	=     IapReadByte(FLASH_ADDR_LH_MODEL);        		//离合开关输入模式
			pFlash->lh.rising_ed         	=     IapReadByte(FLASH_ADDR_LH_RISING_ED);      	//离合开关上升沿消抖
			pFlash->lh.falling_ed       	=     IapReadByte(FLASH_ADDR_LH_FALLING_ED);    	//离合开关下降沿消抖
			pFlash->lh.type     			=     IapReadByte(FLASH_ADDR_LH_TYPE);  					//离合开关评判类型和方式
			//脚刹开关
		  pFlash->js.pin               	=     IapReadByte(FLASH_ADDR_JS_PIN);             //脚刹开关输入管脚位置
			pFlash->js.modle             	=     IapReadByte(FLASH_ADDR_JS_MODEL);           //脚刹开关输入模式
			pFlash->js.rising_ed         	=     IapReadByte(FLASH_ADDR_JS_RISING_ED);       //脚刹开关上升沿消抖
			pFlash->js.falling_ed        	=     IapReadByte(FLASH_ADDR_JS_FALLING_ED);      //脚刹开关下降沿消抖
			pFlash->js.type     					=     IapReadByte(FLASH_ADDR_JS_TYPE);  					//脚刹开关评判类型和方式
			//熄火开关
	    pFlash->xh.pin               	=     IapReadByte(FLASH_ADDR_XH_PIN);           	//熄火开关输入管脚位置
			pFlash->xh.modle             	=     IapReadByte(FLASH_ADDR_XH_MODEL);        		//熄火开关输入模式
			pFlash->xh.rising_ed         	=     IapReadByte(FLASH_ADDR_XH_RISING_ED);      	//熄火开关上升沿消抖
			pFlash->xh.falling_ed        	=     IapReadByte(FLASH_ADDR_XH_FALLING_ED);    	//熄火开关下降沿消抖
			pFlash->xh.type              	=     IapReadByte(FLASH_ADDR_XH_TYPE);          	//熄火开关评判方式
			//启动开关
		  pFlash->qd.pin               	=     IapReadByte(FLASH_ADDR_QD_PIN);             //启动开关输入管脚位置
			pFlash->qd.modle             	=     IapReadByte(FLASH_ADDR_QD_MODEL);           //启动开关输入模式
			pFlash->qd.rising_ed         	=     IapReadByte(FLASH_ADDR_QD_RISING_ED);      	//启动开关上升沿消抖
			pFlash->qd.falling_ed        	=     IapReadByte(FLASH_ADDR_QD_FALLING_ED);    	//启动开关下降沿消抖
			pFlash->qd.type              	=     IapReadByte(FLASH_ADDR_QD_TYPE);          	//启动方式	
			//安全带开关
			pFlash->aqd.pin             	=     IapReadByte(FLASH_ADDR_AQD_PIN);           	//安全带开关输入管脚位置
			pFlash->aqd.modle            	=     IapReadByte(FLASH_ADDR_AQD_MODEL);        	//安全带开关输入模式
			pFlash->aqd.rising_ed        	=     IapReadByte(FLASH_ADDR_AQD_RISING_ED);      //安全带开关上升沿消抖
			pFlash->aqd.falling_ed       	=     IapReadByte(FLASH_ADDR_AQD_FALLING_ED);    	//安全带开关下降沿消抖
			pFlash->aqd.type     					=     IapReadByte(FLASH_ADDR_AQD_TYPE);  					//安全带开关评判类型和方式
			//示警开关
			pFlash->sj.pin             	  =     IapReadByte(FLASH_ADDR_SJ_PIN);           	//示警开关输入管脚位置
			pFlash->sj.modle            	=     IapReadByte(FLASH_ADDR_SJ_MODEL);        	  //示警开关输入模式
			pFlash->sj.rising_ed        	=     IapReadByte(FLASH_ADDR_SJ_RISING_ED);       //示警开关上升沿消抖
			pFlash->sj.falling_ed       	=     IapReadByte(FLASH_ADDR_SJ_FALLING_ED);    	//示警开关下降沿消抖
			pFlash->sj.type     					=     IapReadByte(FLASH_ADDR_SJ_TYPE);  					//示警开关评判类型和方式
			//小灯开关
			pFlash->xd.pin               	=     IapReadByte(FLASH_ADDR_XD_PIN);           	//小灯开关输入管脚位置
			pFlash->xd.modle             	=     IapReadByte(FLASH_ADDR_XD_MODEL);        		//小灯开关输入模式
			pFlash->xd.rising_ed         	=     IapReadByte(FLASH_ADDR_XD_RISING_ED);      	//小灯开关上升沿消抖
			pFlash->xd.falling_ed        	=     IapReadByte(FLASH_ADDR_XD_FALLING_ED);    	//小灯开关下降沿消抖
			pFlash->xd.type     					=     IapReadByte(FLASH_ADDR_XD_TYPE);  					//小灯开关评判类型和方式
			//喇叭开关
		  pFlash->lb.pin               	=     IapReadByte(FLASH_ADDR_LB_PIN);           	//喇叭开关输入管脚位置
			pFlash->lb.modle             	=     IapReadByte(FLASH_ADDR_LB_MODEL);        		//喇叭开关输入模式
			pFlash->lb.rising_ed         	=     IapReadByte(FLASH_ADDR_LB_RISING_ED);      	//喇叭开关上升沿消抖
			pFlash->lb.falling_ed        	=     IapReadByte(FLASH_ADDR_LB_FALLING_ED);    	//喇叭开关下降沿消抖
			pFlash->lb.type     					=     IapReadByte(FLASH_ADDR_LB_TYPE);  					//喇叭开关评判类型和方式
			//车门开关
		  pFlash->cm.pin               	=     IapReadByte(FLASH_ADDR_CM_PIN);           	//车门开关输入管脚位置
			pFlash->cm.modle             	=     IapReadByte(FLASH_ADDR_CM_MODEL);        		//车门开关输入模式
			pFlash->cm.rising_ed         	=     IapReadByte(FLASH_ADDR_CM_RISING_ED);      	//车门开关上升沿消抖
			pFlash->cm.falling_ed       	=     IapReadByte(FLASH_ADDR_CM_FALLING_ED);    	//车门开关下降沿消抖
			pFlash->cm.type     					=     IapReadByte(FLASH_ADDR_CM_TYPE);  					//车门开关评判类型和方式
			//挡位传感器
		  pFlash->dw.pin1              	=     IapReadByte(FLASH_ADDR_DW_PIN1);          	//挡位传感器信号线1输入管脚位置
			pFlash->dw.pin2            		=     IapReadByte(FLASH_ADDR_DW_PIN2);       			//挡位传感器信号线2输入管脚位置
			pFlash->dw.pin3         			=     IapReadByte(FLASH_ADDR_DW_PIN3);     				//挡位传感器信号线3输入管脚位置
			pFlash->dw.pin4       				=     IapReadByte(FLASH_ADDR_DW_PIN4);   					//挡位传感器信号线4输入管脚位置
			pFlash->dw.pin5       				=     IapReadByte(FLASH_ADDR_DW_PIN5);   					//挡位传感器信号线5输入管脚位置
			pFlash->dw.modle             	=     IapReadByte(FLASH_ADDR_DW_MODEL);       		//挡位传感器输入模式
			pFlash->dw.rising_ed        	=     IapReadByte(FLASH_ADDR_DW_RISING_ED);     	//挡位传感器上升沿消抖
			pFlash->dw.falling_ed        	=     IapReadByte(FLASH_ADDR_DW_FALLING_ED);   		//挡位传感器下降沿消抖
			pFlash->dw.value[0]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_1);   			//1挡位标定值
			pFlash->dw.value[1]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_2);   			//2挡位标定值
			pFlash->dw.value[2]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_3);   			//3挡位标定值
			pFlash->dw.value[3]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_4);   			//4挡位标定值
			pFlash->dw.value[4]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_5);   			//5挡位标定值
			pFlash->dw.value[5]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_R);   			//倒挡挡位标定值
			pFlash->dw.value[6]       		=     IapReadByte(FLASH_ADDR_DW_VALUE_ZERO);   		//空挡挡位标定值
			pFlash->dw.type              	=     IapReadByte(FLASH_ADDR_DW_TYPE);         		//挡位传感器类型
			//左后视开关
			pFlash->zhs.pin              	=     IapReadByte(FLASH_ADDR_ZHS_PIN);          	//左后视开关输入管脚位置
			pFlash->zhs.modle            	=     IapReadByte(FLASH_ADDR_ZHS_MODEL);       		//左后视开关输入模式
			pFlash->zhs.rising_ed        	=     IapReadByte(FLASH_ADDR_ZHS_RISING_ED);     	//左后视开关上升沿消抖
			pFlash->zhs.falling_ed      	=     IapReadByte(FLASH_ADDR_ZHS_FALLING_ED);   	//左后视开关下降沿消抖
			pFlash->zhs.type     					=     IapReadByte(FLASH_ADDR_ZHS_TYPE);  					//左后视开关评判类型和方式
			//内后视开关
			pFlash->nhs.pin              	=     IapReadByte(FLASH_ADDR_NHS_PIN);          	//内后视开关输入管脚位置
			pFlash->nhs.modle            	=     IapReadByte(FLASH_ADDR_NHS_MODEL);       		//内后视开关输入模式
			pFlash->nhs.rising_ed        	=     IapReadByte(FLASH_ADDR_NHS_RISING_ED);     	//内后视开关上升沿消抖
			pFlash->nhs.falling_ed       	=     IapReadByte(FLASH_ADDR_NHS_FALLING_ED);   	//内后视开关下降沿消抖
			pFlash->nhs.type     				 	=     IapReadByte(FLASH_ADDR_NHS_TYPE);  					//内后视开关评判类型和方式
			//副刹开关
			pFlash->fsc.pin              	=     IapReadByte(FLASH_ADDR_FSC_PIN);           	//副刹开关输入管脚位置
			pFlash->fsc.modle            	=     IapReadByte(FLASH_ADDR_FSC_MODEL);        	//副刹开关输入模式
			pFlash->fsc.rising_ed        	=     IapReadByte(FLASH_ADDR_FSC_RISING_ED);      //副刹开关上升沿消抖
			pFlash->fsc.falling_ed       	=     IapReadByte(FLASH_ADDR_FSC_FALLING_ED);    	//副刹开关下降沿消抖
			pFlash->fsc.type     					=     IapReadByte(FLASH_ADDR_FSC_TYPE);  					//副刹开关评判类型和方式
			//雾灯开关
			pFlash->wd.pin               	=     IapReadByte(FLASH_ADDR_WD_PIN);           	//雾灯开关输入管脚位置
			pFlash->wd.modle             	=     IapReadByte(FLASH_ADDR_WD_MODEL);        		//雾灯开关输入模式
			pFlash->wd.rising_ed         	=     IapReadByte(FLASH_ADDR_WD_RISING_ED);      	//雾灯开关上升沿消抖
			pFlash->wd.falling_ed        	=     IapReadByte(FLASH_ADDR_WD_FALLING_ED);    	//雾灯开关下降沿消抖
			pFlash->wd.type     					=     IapReadByte(FLASH_ADDR_WD_TYPE);  					//雾灯开关评判类型和方式
			//雨刷开关
	    pFlash->ys.pin               	=     IapReadByte(FLASH_ADDR_YS_PIN);           	//雨刷开关输入管脚位置
			pFlash->ys.modle             	=     IapReadByte(FLASH_ADDR_YS_MODEL);        		//雨刷开关输入模式
			pFlash->ys.rising_ed         	=     IapReadByte(FLASH_ADDR_YS_RISING_ED);      	//雨刷开关上升沿消抖
			pFlash->ys.falling_ed        	=     IapReadByte(FLASH_ADDR_YS_FALLING_ED);    	//雨刷开关下降沿消抖
			pFlash->ys.type     					=     IapReadByte(FLASH_ADDR_YS_TYPE);  					//雨刷开关评判类型和方式
			//倒车灯开关
			pFlash->dcd.pin              	=     IapReadByte(FLASH_ADDR_DCD_PIN);           	//倒车灯开关输入管脚位置
			pFlash->dcd.modle           	=     IapReadByte(FLASH_ADDR_DCD_MODEL);        	//倒车灯开关输入模式
			pFlash->dcd.rising_ed        	=     IapReadByte(FLASH_ADDR_DCD_RISING_ED);      //倒车灯开关上升沿消抖
			pFlash->dcd.falling_ed       	=     IapReadByte(FLASH_ADDR_DCD_FALLING_ED);    	//倒车灯开关下降沿消抖
			pFlash->dcd.type     					=     IapReadByte(FLASH_ADDR_DCD_TYPE);  					//倒车灯开关评判类型和方式
			//钥匙门开关
			pFlash->ysm.pin            		=     IapReadByte(FLASH_ADDR_YSM_PIN);           	//钥匙门开关输入管脚位置
			pFlash->ysm.modle          		=     IapReadByte(FLASH_ADDR_YSM_MODEL);       		//钥匙门开关输入模式
			pFlash->ysm.rising_ed      		=     IapReadByte(FLASH_ADDR_YSM_RISING_ED);      //钥匙门开关上升沿消抖
			pFlash->ysm.falling_ed    		=     IapReadByte(FLASH_ADDR_YSM_FALLING_ED);    	//钥匙门开关下降沿消抖
			pFlash->ysm.type     					=     IapReadByte(FLASH_ADDR_YSM_TYPE);  					//钥匙门开关评判类型和方式
			//绕车开关1
		  pFlash->rc.pin1             	=     IapReadByte(FLASH_ADDR_RC_PIN1);           	//绕车1号开关输入管脚位置
			pFlash->rc.pin2           		=     IapReadByte(FLASH_ADDR_RC_PIN2);        		//绕车2号开关输入管脚位置
			pFlash->rc.pin3       				=     IapReadByte(FLASH_ADDR_RC_PIN3);      			//绕车3号开关输入管脚位置
			pFlash->rc.modle           		=     IapReadByte(FLASH_ADDR_RC_MODEL);        		//绕车开关输入模式
			pFlash->rc.rising_ed       		=     IapReadByte(FLASH_ADDR_RC_RISING_ED);      	//绕车开关上升沿消抖
			pFlash->rc.falling_ed      		=     IapReadByte(FLASH_ADDR_RC_FALLING_ED);    	//绕车开关下降沿消抖
			pFlash->rc.type            		=     IapReadByte(FLASH_ADDR_RC_TYPE);          	//绕车开关1类型
			//闯动开关
			pFlash->cd.pin            		=     IapReadByte(FLASH_ADDR_CD_PIN);            	//闯动开关输入管脚位置
			pFlash->cd.modle         			=     IapReadByte(FLASH_ADDR_CD_MODEL);         	//闯动开关输入模式
			pFlash->cd.rising_ed      		=     IapReadByte(FLASH_ADDR_CD_RISING_ED);       //闯动开关上升沿消抖
			pFlash->cd.falling_ed     		=     IapReadByte(FLASH_ADDR_CD_FALLING_ED);     	//闯动开关下降沿消抖
			pFlash->cd.type     					=     IapReadByte(FLASH_ADDR_CD_TYPE);  					//闯动开关评判类型和方式
			//座椅开关（压力）
		  pFlash->zyyl.pin             	=     IapReadByte(FLASH_ADDR_ZYYL_PIN);          	//座椅开关（压力）输入管脚位置
			pFlash->zyyl.modle           	=     IapReadByte(FLASH_ADDR_ZYYL_MODEL);       	//座椅开关（压力）输入模式
			pFlash->zyyl.rising_ed       	=     IapReadByte(FLASH_ADDR_ZYYL_RISING_ED);     //座椅开关（压力）上升沿消抖
			pFlash->zyyl.falling_ed      	=     IapReadByte(FLASH_ADDR_ZYYL_FALLING_ED);   	//座椅开关下降沿消抖
			pFlash->zyyl.type     				=     IapReadByte(FLASH_ADDR_ZYYL_TYPE);  				//座椅开关评判类型和方式
			//里程计数
		  pFlash->lc.pin             		=     IapReadByte(FLASH_ADDR_LCJS_PIN);          	//里程计数输入管脚位置
			pFlash->lc.modle           		=     IapReadByte(FLASH_ADDR_LCJS_MODEL);       	//里程计数输入模式
			pFlash->lc.rising_ed       		=     IapReadByte(FLASH_ADDR_LCJS_RISING_ED);     //里程计数下降沿消抖
			pFlash->lc.falling_ed      		=     IapReadByte(FLASH_ADDR_LCJS_FALLING_ED);   	//里程计数上升沿消抖
			pFlash->lc.type     					=     IapReadByte(FLASH_ADDR_LCJS_TYPE);  				//里程计数评判类型和方式
			//观察仪表盘
		  pFlash->gcybp.pin            	=     IapReadByte(FLASH_ADDR_GCYBP_PIN);          //观察仪表盘输入管脚位置
			pFlash->gcybp.modle          	=     IapReadByte(FLASH_ADDR_GCYBP_MODEL);       	//观察仪表盘输入模式
			pFlash->gcybp.rising_ed      	=     IapReadByte(FLASH_ADDR_GCYBP_RISING_ED);    //观察仪表盘上升沿消抖
			pFlash->gcybp.falling_ed     	=     IapReadByte(FLASH_ADDR_GCYBP_FALLING_ED);   //观察仪表盘下降沿消抖
			pFlash->gcybp.type     				=     IapReadByte(FLASH_ADDR_GCYBP_TYPE);  				//观察仪表盘评判类型和方式
			
			//触发开始考试
		  pFlash->begin.pin            	=     IapReadByte(FLASH_ADDR_BEGIN_PIN);          //触发开始考试输入管脚位置
			pFlash->begin.modle          	=     IapReadByte(FLASH_ADDR_BEGIN_MODEL);       	//触发开始考试输入模式
			pFlash->begin.rising_ed      	=     IapReadByte(FLASH_ADDR_BEGIN_RISING_ED);    //触发开始考试上升沿消抖
			pFlash->begin.falling_ed     	=     IapReadByte(FLASH_ADDR_BEGIN_FALLING_ED);   //触发开始考试下降沿消抖
			pFlash->begin.type     				=     IapReadByte(FLASH_ADDR_BEGIN_TYPE);  				//触发开始考试评判类型和方式
			//转速
			pFlash->zs.pin            		=     IapReadByte(FLASH_ADDR_ZS_PIN);         		 //启动发动机时最小脉冲计数（大于该值车辆启动）
			pFlash->zs.min          			=     IapReadByte(FLASH_ADDR_ZS_IDLIN_MIN);        //转速怠速最小脉冲计数
			pFlash->zs.max          			=     IapReadByte(FLASH_ADDR_ZS_XH_MAX);           //熄火后发动机的最大脉冲计数（小于该值车辆熄火）
			pFlash->zs.bs      						=     IapReadByte(FLASH_ADDR_ZS_BS);    					 //转速脉冲计数放大倍数
			pFlash->zs.sampling_time     	=     IapReadByte(FLASH_ADDR_ZS_SAMPLING_TIME);    //转速脉冲采样时间
			pFlash->zs.init_value     		=     IapReadByte(FLASH_ADDR_ZS_INIT_VALUE);			 //初始转速 0=默认0，1=默认800
			//单边桥传感器
			pFlash->dbq.pin1            	=     IapReadByte(FLASH_ADDR_DBQ_PIN1);         		//单边桥信号输入管脚位置1
			pFlash->dbq.pin2          		=     IapReadByte(FLASH_ADDR_DBQ_PIN2);        			//单边桥信号输入管脚位置2
			pFlash->dbq.pin3      				=     IapReadByte(FLASH_ADDR_DBQ_PIN3);    					//单边桥信号输入管脚位置3
			pFlash->dbq.pin4     					=     IapReadByte(FLASH_ADDR_DBQ_PIN4);    					//单边桥信号输入管脚位置4
			pFlash->dbq.pin5     					=     IapReadByte(FLASH_ADDR_DBQ_PIN5);			 				//单边桥信号输入管脚位置5
			pFlash->dbq.pin6            	=     IapReadByte(FLASH_ADDR_DBQ_PIN6);         		//单边桥信号输入管脚位置6
			pFlash->dbq.modle          		=     IapReadByte(FLASH_ADDR_DBQ_MODEL);        		//单边桥信号输入模式
			pFlash->dbq.rising_ed      		=     IapReadByte(FLASH_ADDR_DBQ_RISING_ED);    		//单边桥信号输入上升沿消抖时间
			pFlash->dbq.falling_ed    		=     IapReadByte(FLASH_ADDR_DBQ_FALLING_ED);    		//单边桥信号输入下降沿消抖时间
			pFlash->dbq.type     					=     IapReadByte(FLASH_ADDR_DBQ_TYPE);			 				//单边桥信号输入传感器类型		
			
			//板卡信息 板号board
			pFlash->board.trigger_mode		=     IapReadByte(FLASH_ADDR_TRIGGER_MODE);   			//数据触发模式
			pFlash->board.device_type			=     IapReadByte(FLASH_ADDR_DEVICE_TYPE);    			//板卡类型
			pFlash->board.number_L    		=     IapReadByte(FLASH_ADDR_BOARD_ID_L);    				//板号低位
			pFlash->board.number_H     		=     IapReadByte(FLASH_ADDR_BOARD_ID_H);			 			//板号高位
			
#ifdef  STC15W4K48S4			
			//摩托车头盔传感器
		  pFlash->tk.pin             		=     	IapReadByte(FLASH_ADDR_TK_PIN);          			//摩托车头盔开关（压力）输入管脚位置
			pFlash->tk.modle           		=     	IapReadByte(FLASH_ADDR_TK_MODEL);       			//摩托车头盔开关（压力）输入模式
			pFlash->tk.rising_ed       		=     	IapReadByte(FLASH_ADDR_TK_RISING_ED);     		//摩托车头盔开关（压力）上升沿消抖
			pFlash->tk.falling_ed      		=     	IapReadByte(FLASH_ADDR_TK_FALLING_ED);   			//摩托车头盔开关下降沿消抖
			pFlash->tk.type     					=     	IapReadByte(FLASH_ADDR_TK_TYPE);  						//摩托车头盔开关评判类型和方式	
			
			//摩托车左把手传感器
		  pFlash->zbs.pin             	=     	IapReadByte(FLASH_ADDR_ZBS_PIN);          		//摩托车左把手开关（压力）输入管脚位置
			pFlash->zbs.modle           	=     	IapReadByte(FLASH_ADDR_ZBS_MODEL);       			//摩托车左把手开关（压力）输入模式
			pFlash->zbs.rising_ed       	=     	IapReadByte(FLASH_ADDR_ZBS_RISING_ED);     		//摩托车左把手开关（压力）上升沿消抖
			pFlash->zbs.falling_ed      	=     	IapReadByte(FLASH_ADDR_ZBS_FALLING_ED);   		//摩托车左把手开关下降沿消抖
			pFlash->zbs.type     					=     	IapReadByte(FLASH_ADDR_ZBS_TYPE);  						//摩托车左把手开关评判类型和方式	
			
			//摩托车右把手传感器
		  pFlash->ybs.pin             	=     	IapReadByte(FLASH_ADDR_YBS_PIN);          		//摩托车右把手开关（压力）输入管脚位置
			pFlash->ybs.modle           	=     	IapReadByte(FLASH_ADDR_YBS_MODEL);       			//摩托车右把手开关（压力）输入模式
			pFlash->ybs.rising_ed       	=     	IapReadByte(FLASH_ADDR_YBS_RISING_ED);     		//摩托车右把手开关（压力）上升沿消抖
			pFlash->ybs.falling_ed      	=     	IapReadByte(FLASH_ADDR_YBS_FALLING_ED);   		//摩托车右把手开关下降沿消抖
			pFlash->ybs.type     					=     	IapReadByte(FLASH_ADDR_YBS_TYPE);  						//摩托车右把手开关评判类型和方式	
			
			//摩托车左踏板传感器
		  pFlash->zjtb.pin             	=     	IapReadByte(FLASH_ADDR_ZJTB_PIN);          		//摩托车左踏板开关（压力）输入管脚位置
			pFlash->zjtb.modle           	=     	IapReadByte(FLASH_ADDR_ZJTB_MODEL);       		//摩托车左踏板开关（压力）输入模式
			pFlash->zjtb.rising_ed       	=     	IapReadByte(FLASH_ADDR_ZJTB_RISING_ED);     	//摩托车左踏板开关（压力）上升沿消抖
			pFlash->zjtb.falling_ed      	=     	IapReadByte(FLASH_ADDR_ZJTB_FALLING_ED);   		//摩托车左踏板开关下降沿消抖
			pFlash->zjtb.type     				=     	IapReadByte(FLASH_ADDR_ZJTB_TYPE);  					//摩托车左踏板开关评判类型和方式	
			
			//摩托车右踏板传感器
		  pFlash->yjtb.pin             	=     	IapReadByte(FLASH_ADDR_YJTB_PIN);          		//摩托车右踏板开关（压力）输入管脚位置
			pFlash->yjtb.modle           	=     	IapReadByte(FLASH_ADDR_YJTB_MODEL);       		//摩托车右踏板开关（压力）输入模式
			pFlash->yjtb.rising_ed       	=     	IapReadByte(FLASH_ADDR_YJTB_RISING_ED);     	//摩托车右踏板开关（压力）上升沿消抖
			pFlash->yjtb.falling_ed      	=     	IapReadByte(FLASH_ADDR_YJTB_FALLING_ED);   		//摩托车右踏板开关下降沿消抖
			pFlash->yjtb.type     				=     	IapReadByte(FLASH_ADDR_YJTB_TYPE);  					//摩托车右踏板开关评判类型和方式	
			
			//碰杆接收
		  pFlash->pgjs.pin             	=     	IapReadByte(FLASH_ADDR_PGJS_PIN);          		//碰杆项目管脚位置
			pFlash->pgjs.modle          	=     	IapReadByte(FLASH_ADDR_PGJS_MODEL);       		//碰杆项目输入模式
			pFlash->pgjs.rising_ed       	=     	IapReadByte(FLASH_ADDR_PGJS_RISING_ED);     	//碰杆项目上升沿消抖
			pFlash->pgjs.falling_ed      	=     	IapReadByte(FLASH_ADDR_PGJS_FALLING_ED);   		//碰杆项目下降沿消抖
			pFlash->pgjs.type     				=     	IapReadByte(FLASH_ADDR_PGJS_TYPE);  					//碰杆项目评判类型和方式	
			
			//碰杆项目1
		  pFlash->bump[0].name          =     	IapReadByte(FLASH_ADDR_PGJS_1_NAME);          //碰杆项目名称
			pFlash->bump[0].number        =     	IapReadByte(FLASH_ADDR_PGJS_1_N0);       			//碰杆项目编号
			pFlash->bump[0].count       	=     	IapReadByte(FLASH_ADDR_PGJS_1_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[0].type       		=     	IapReadByte(FLASH_ADDR_PGJS_1_TYPE);     			//碰杆项目对应传感器类型
			
			//碰杆项目2
		  pFlash->bump[1].name          =     	IapReadByte(FLASH_ADDR_PGJS_2_NAME);          //碰杆项目名称
			pFlash->bump[1].number        =     	IapReadByte(FLASH_ADDR_PGJS_2_N0);       			//碰杆项目编号
			pFlash->bump[1].count       	=     	IapReadByte(FLASH_ADDR_PGJS_2_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[1].type       		=     	IapReadByte(FLASH_ADDR_PGJS_2_TYPE);     			//碰杆项目对应传感器类型
			
			//碰杆项目3
		  pFlash->bump[2].name          =     	IapReadByte(FLASH_ADDR_PGJS_3_NAME);          //碰杆项目名称
			pFlash->bump[2].number        =     	IapReadByte(FLASH_ADDR_PGJS_3_N0);       			//碰杆项目编号
			pFlash->bump[2].count       	=     	IapReadByte(FLASH_ADDR_PGJS_3_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[2].type       		=     	IapReadByte(FLASH_ADDR_PGJS_3_TYPE);     			//碰杆项目对应传感器类型
			
			//碰杆项目4
		  pFlash->bump[3].name          =     	IapReadByte(FLASH_ADDR_PGJS_4_NAME);          //碰杆项目名称
			pFlash->bump[3].number        =     	IapReadByte(FLASH_ADDR_PGJS_4_N0);       			//碰杆项目编号
			pFlash->bump[3].count       	=     	IapReadByte(FLASH_ADDR_PGJS_4_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[3].type       		=     	IapReadByte(FLASH_ADDR_PGJS_4_TYPE);     			//碰杆项目对应传感器类型
			
			
		 //摩托车前手刹
		  pFlash->qss.pin             	=     	IapReadByte(FLASH_ADDR_QSS_PIN);          		//摩托车前手刹输入管脚位置
			pFlash->qss.modle           	=     	IapReadByte(FLASH_ADDR_QSS_MODEL);       			//摩托车前手刹输入模式
			pFlash->qss.rising_ed       	=     	IapReadByte(FLASH_ADDR_QSS_RISING_ED);     		//摩托车前手刹上升沿消抖
			pFlash->qss.falling_ed      	=     	IapReadByte(FLASH_ADDR_QSS_FALLING_ED);   		//摩托车前手刹下降沿消抖
			pFlash->qss.type     				  =     	IapReadByte(FLASH_ADDR_QSS_TYPE);  						//摩托车前手刹类型和方式	
			
			//碰杆项目5
		  pFlash->bump[4].name          =     	IapReadByte(FLASH_ADDR_PGJS_5_NAME);          //碰杆项目名称
			pFlash->bump[4].number        =     	IapReadByte(FLASH_ADDR_PGJS_5_N0);       			//碰杆项目编号
			pFlash->bump[4].count       	=     	IapReadByte(FLASH_ADDR_PGJS_5_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[4].type       		=     	IapReadByte(FLASH_ADDR_PGJS_5_TYPE);     			//碰杆项目对应传感器类型
			
			//碰杆项目6
		  pFlash->bump[5].name          =     	IapReadByte(FLASH_ADDR_PGJS_6_NAME);          //碰杆项目名称
			pFlash->bump[5].number        =     	IapReadByte(FLASH_ADDR_PGJS_6_N0);       			//碰杆项目编号
			pFlash->bump[5].count       	=     	IapReadByte(FLASH_ADDR_PGJS_6_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[5].type       		=     	IapReadByte(FLASH_ADDR_PGJS_6_TYPE);     			//碰杆项目对应传感器类型
			
			//碰杆项目7
		  pFlash->bump[6].name          =     	IapReadByte(FLASH_ADDR_PGJS_7_NAME);          //碰杆项目名称
			pFlash->bump[6].number        =     	IapReadByte(FLASH_ADDR_PGJS_7_N0);       			//碰杆项目编号
			pFlash->bump[6].count       	=     	IapReadByte(FLASH_ADDR_PGJS_7_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[6].type       		=     	IapReadByte(FLASH_ADDR_PGJS_7_TYPE);     			//碰杆项目对应传感器类型
			
			//碰杆项目8
		  pFlash->bump[7].name          =     	IapReadByte(FLASH_ADDR_PGJS_8_NAME);          //碰杆项目名称
			pFlash->bump[7].number        =     	IapReadByte(FLASH_ADDR_PGJS_8_N0);       			//碰杆项目编号
			pFlash->bump[7].count       	=     	IapReadByte(FLASH_ADDR_PGJS_8_COUNT);     		//碰杆项目对应杆的数量
			pFlash->bump[7].type       		=     	IapReadByte(FLASH_ADDR_PGJS_8_TYPE);     			//碰杆项目对应传感器类型
					
		 //GNSS型号
			pFlash->gnss.model       			=     	IapReadByte(FLASH_ADDR_GNSS_MODEL);     			//GNSS型号
#endif
}
//========================================================================
// 函数: BPS_FlashWriteByte(u16 addr, u8 value)
// 描述: 按照字节写入flash，写入前先备份数据
// 参数：addr为要写入字节数据的地址，value为字节数据
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_FlashWriteByte(u16 addr, u8 value)
{

	BSP_GetFlashConfig();//缓存flash数据
	IapEraseSector(addr);//擦除扇区
	//写入数据
	
	//主板与上位机的连接串口号
	addr == FLASH_ADDR_UPLOAD_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_UPLOAD_COM, FlashCacheBuf.upload.com);
	addr == FLASH_ADDR_UPLOAD_BOTE 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_UPLOAD_BOTE, FlashCacheBuf.upload.bote);
	
	//主板与GPS连接串口号
	addr == FLASH_ADDR_GPS_COM 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GPS_COM, FlashCacheBuf.gps.com);
	addr == FLASH_ADDR_GPS_BOTE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GPS_BOTE, FlashCacheBuf.gps.bote);
	addr == FLASH_ADDR_GPS_COM_REMAP 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GPS_COM_REMAP, FlashCacheBuf.gps.remap);
	
	//主板与高森碰杆传感器连接的串口
	addr == FLASH_ADDR_BUMP_HS_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BUMP_HS_COM, FlashCacheBuf.bump_hs.com);
	addr == FLASH_ADDR_BUMP_HS_BOTE 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BUMP_HS_BOTE, FlashCacheBuf.bump_hs.bote);
	
	//主板与2.4G碰杆传感器连接的串口
	addr == FLASH_ADDR_BUMP_24G_COM 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BUMP_24G_COM, FlashCacheBuf.bump_24g.com);
	addr == FLASH_ADDR_BUMP_24G_BOTE 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BUMP_24G_BOTE, FlashCacheBuf.bump_24g.bote);
		
	//主板与倾角连接的串口（汇总后接入）
	addr == FLASH_ADDR_TILT_ALL_COM 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_ALL_COM, FlashCacheBuf.titl_all.com);
	addr == FLASH_ADDR_TILT_BOTE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_BOTE, FlashCacheBuf.titl_all.bote);
	
	//主板与前轴倾角传感器的连接串口号（单传感器连接）
	addr == FLASH_ADDR_TILT_Q_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_Q_COM, FlashCacheBuf.titl_q.com);
	addr == FLASH_ADDR_TILT_BOTE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_BOTE, FlashCacheBuf.titl_q.bote);
	
	//主板与后轴倾角传感器的连接串口号（单传感器连接）
	addr == FLASH_ADDR_TILT_H_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_H_COM, FlashCacheBuf.titl_h.com);
	addr == FLASH_ADDR_TILT_BOTE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_BOTE, FlashCacheBuf.titl_h.bote);
	
	//主板与挂轴倾角传感器的连接串口号（单传感器连接）
	addr == FLASH_ADDR_TILT_G_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_G_COM, FlashCacheBuf.titl_g.com);
	addr == FLASH_ADDR_TILT_BOTE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_BOTE, FlashCacheBuf.titl_g.bote);
	
	//主板与二轮摩托车倾角传感器的连接串口号（单传感器连接）
	addr == FLASH_ADDR_TILT_MTC_COM 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_MTC_COM, FlashCacheBuf.titl_mtc.com);
	addr == FLASH_ADDR_TILT_BOTE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TILT_BOTE, FlashCacheBuf.titl_mtc.bote);
	
	//主板网口模块
	addr == FLASH_ADDR_NETWORK_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_NETWORK_COM, FlashCacheBuf.network.com);
	
	
	//主板与超声波（单边桥）传感器的连接串口号
	addr == FLASH_ADDR_CSB_DBQ_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CSB_DBQ_COM, FlashCacheBuf.csb_dbq.com);
	addr == FLASH_ADDR_CSB_DBQ_BOTE 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CSB_DBQ_BOTE, FlashCacheBuf.csb_dbq.bote);
	
	//主板与超声波（隧道）传感器的连接串口号
	addr == FLASH_ADDR_CSB_SD_COM 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CSB_SD_COM, FlashCacheBuf.csb_sd.com);
	addr == FLASH_ADDR_CSB_SD_BOTE 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CSB_SD_BOTE, FlashCacheBuf.csb_sd.bote);
	

	//座椅开关（调节）
	addr == FLASH_ADDR_ZYTJ_PIN 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYTJ_PIN, FlashCacheBuf.zytj.pin);
	addr == FLASH_ADDR_ZYTJ_MODEL 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYTJ_MODEL,FlashCacheBuf.zytj.modle);
	addr == FLASH_ADDR_ZYTJ_RISING_ED 		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYTJ_RISING_ED,FlashCacheBuf.zytj.rising_ed);
	addr == FLASH_ADDR_ZYTJ_FALLING_ED 		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYTJ_FALLING_ED,FlashCacheBuf.zytj.falling_ed);
	addr == FLASH_ADDR_ZYTJ_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYTJ_TYPE,	FlashCacheBuf.zytj.type);
  //手刹开关
	addr == FLASH_ADDR_SS_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SS_PIN, FlashCacheBuf.ss.pin);
	addr == FLASH_ADDR_SS_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SS_MODEL,FlashCacheBuf.ss.modle);
	addr == FLASH_ADDR_SS_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SS_RISING_ED,FlashCacheBuf.ss.rising_ed);
	addr == FLASH_ADDR_SS_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SS_FALLING_ED,	FlashCacheBuf.ss.falling_ed);
	addr == FLASH_ADDR_SS_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SS_TYPE,	FlashCacheBuf.ss.type);
	//左转开关
	addr == FLASH_ADDR_ZZ_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZZ_PIN, FlashCacheBuf.zz.pin);
	addr == FLASH_ADDR_ZZ_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZZ_MODEL,FlashCacheBuf.zz.modle);
	addr == FLASH_ADDR_ZZ_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZZ_RISING_ED,FlashCacheBuf.zz.rising_ed);
	addr == FLASH_ADDR_ZZ_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZZ_FALLING_ED,	FlashCacheBuf.zz.falling_ed);
	addr == FLASH_ADDR_ZZ_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZZ_TYPE,	FlashCacheBuf.zz.type);
	//右转开关
	addr == FLASH_ADDR_YZ_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YZ_PIN, FlashCacheBuf.yz.pin);
	addr == FLASH_ADDR_YZ_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YZ_MODEL,FlashCacheBuf.yz.modle);
	addr == FLASH_ADDR_YZ_RISING_ED 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YZ_RISING_ED,FlashCacheBuf.yz.rising_ed);
	addr == FLASH_ADDR_YZ_FALLING_ED 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YZ_FALLING_ED,	FlashCacheBuf.yz.falling_ed);
	addr == FLASH_ADDR_YZ_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YZ_TYPE,	FlashCacheBuf.yz.type);
	//远光开关
	addr == FLASH_ADDR_YG_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YG_PIN, FlashCacheBuf.yg.pin);
	addr == FLASH_ADDR_YG_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YG_MODEL,FlashCacheBuf.yg.modle);
	addr == FLASH_ADDR_YG_RISING_ED 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YG_RISING_ED,FlashCacheBuf.yg.rising_ed);
	addr == FLASH_ADDR_YG_FALLING_ED 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YG_FALLING_ED,	FlashCacheBuf.yg.falling_ed);
	addr == FLASH_ADDR_YG_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YG_TYPE,	FlashCacheBuf.yg.type);
	//近光开关
	addr == FLASH_ADDR_JG_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JG_PIN, FlashCacheBuf.jg.pin);
	addr == FLASH_ADDR_JG_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JG_MODEL,FlashCacheBuf.jg.modle);
	addr == FLASH_ADDR_JG_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JG_RISING_ED,FlashCacheBuf.jg.rising_ed);
	addr == FLASH_ADDR_JG_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JG_FALLING_ED,	FlashCacheBuf.jg.falling_ed);
	addr == FLASH_ADDR_JG_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JG_TYPE,	FlashCacheBuf.jg.type);
	//离合开关
	addr == FLASH_ADDR_LH_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LH_PIN, FlashCacheBuf.lh.pin);
	addr == FLASH_ADDR_LH_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LH_MODEL,FlashCacheBuf.lh.modle);
	addr == FLASH_ADDR_LH_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LH_RISING_ED,FlashCacheBuf.lh.rising_ed);
	addr == FLASH_ADDR_LH_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LH_FALLING_ED,	FlashCacheBuf.lh.falling_ed);
	addr == FLASH_ADDR_LH_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LH_TYPE,	FlashCacheBuf.lh.type);
	//脚刹开关
	addr == FLASH_ADDR_JS_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JS_PIN, FlashCacheBuf.js.pin);
	addr == FLASH_ADDR_JS_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JS_MODEL,FlashCacheBuf.js.modle);
	addr == FLASH_ADDR_JS_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JS_RISING_ED,FlashCacheBuf.js.rising_ed);
	addr == FLASH_ADDR_JS_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JS_FALLING_ED,	FlashCacheBuf.js.falling_ed);
	addr == FLASH_ADDR_JS_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_JS_TYPE,	FlashCacheBuf.js.type);
	//熄火开关
	addr == FLASH_ADDR_XH_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XH_PIN, FlashCacheBuf.xh.pin);
	addr == FLASH_ADDR_XH_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XH_MODEL,FlashCacheBuf.xh.modle);
	addr == FLASH_ADDR_XH_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XH_RISING_ED,FlashCacheBuf.xh.rising_ed);
	addr == FLASH_ADDR_XH_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XH_FALLING_ED,	FlashCacheBuf.xh.falling_ed);
	addr == FLASH_ADDR_XH_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XH_TYPE,	FlashCacheBuf.xh.type);
	//启动开关
	addr == FLASH_ADDR_QD_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QD_PIN, FlashCacheBuf.qd.pin);
	addr == FLASH_ADDR_QD_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QD_MODEL,FlashCacheBuf.qd.modle);
	addr == FLASH_ADDR_QD_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QD_RISING_ED,FlashCacheBuf.qd.rising_ed);
	addr == FLASH_ADDR_QD_FALLING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QD_FALLING_ED,	FlashCacheBuf.qd.falling_ed);
	addr == FLASH_ADDR_QD_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QD_TYPE,	FlashCacheBuf.qd.type);
	//安全带开关
	addr == FLASH_ADDR_AQD_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_AQD_PIN, FlashCacheBuf.aqd.pin);
	addr == FLASH_ADDR_AQD_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_AQD_MODEL,FlashCacheBuf.aqd.modle);
	addr == FLASH_ADDR_AQD_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_AQD_RISING_ED,FlashCacheBuf.aqd.rising_ed);
	addr == FLASH_ADDR_AQD_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_AQD_FALLING_ED,	FlashCacheBuf.aqd.falling_ed);
	addr == FLASH_ADDR_AQD_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_AQD_TYPE,	FlashCacheBuf.aqd.type);
	//示警开关
	addr == FLASH_ADDR_SJ_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SJ_PIN, FlashCacheBuf.sj.pin);
	addr == FLASH_ADDR_SJ_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SJ_MODEL,FlashCacheBuf.sj.modle);
	addr == FLASH_ADDR_SJ_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SJ_RISING_ED,FlashCacheBuf.sj.rising_ed);
	addr == FLASH_ADDR_SJ_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SJ_FALLING_ED,	FlashCacheBuf.sj.falling_ed);
	addr == FLASH_ADDR_SJ_TYPE 					  ? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_SJ_TYPE,	FlashCacheBuf.sj.type);
	//小灯开关
	addr == FLASH_ADDR_XD_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XD_PIN, FlashCacheBuf.xd.pin);
	addr == FLASH_ADDR_XD_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XD_MODEL,FlashCacheBuf.xd.modle);
	addr == FLASH_ADDR_XD_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XD_RISING_ED,FlashCacheBuf.xd.rising_ed);
	addr == FLASH_ADDR_XD_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XD_FALLING_ED,	FlashCacheBuf.xd.falling_ed);
	addr == FLASH_ADDR_XD_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_XD_TYPE,	FlashCacheBuf.xd.type);
	//喇叭开关
	addr == FLASH_ADDR_LB_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LB_PIN, FlashCacheBuf.lb.pin);
	addr == FLASH_ADDR_LB_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LB_MODEL,FlashCacheBuf.lb.modle);
	addr == FLASH_ADDR_LB_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LB_RISING_ED,FlashCacheBuf.lb.rising_ed);
	addr == FLASH_ADDR_LB_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LB_FALLING_ED,	FlashCacheBuf.lb.falling_ed);
	addr == FLASH_ADDR_LB_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LB_TYPE,	FlashCacheBuf.lb.type);
	//车门开关
	addr == FLASH_ADDR_CM_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CM_PIN, FlashCacheBuf.cm.pin);
	addr == FLASH_ADDR_CM_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CM_MODEL,FlashCacheBuf.cm.modle);
	addr == FLASH_ADDR_CM_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CM_RISING_ED,FlashCacheBuf.cm.rising_ed);
	addr == FLASH_ADDR_CM_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CM_FALLING_ED,	FlashCacheBuf.cm.falling_ed);
	addr == FLASH_ADDR_CM_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CM_TYPE,	FlashCacheBuf.cm.type);
	//挡位传感器
	addr == FLASH_ADDR_DW_PIN1 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_PIN1,FlashCacheBuf.dw.pin1);
	addr == FLASH_ADDR_DW_PIN2 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_PIN2,FlashCacheBuf.dw.pin2);
	addr == FLASH_ADDR_DW_PIN3 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_PIN3,FlashCacheBuf.dw.pin3);
	addr == FLASH_ADDR_DW_PIN4 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_PIN4,FlashCacheBuf.dw.pin4);
	addr == FLASH_ADDR_DW_PIN5 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_PIN5,FlashCacheBuf.dw.pin5);
	addr == FLASH_ADDR_DW_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_MODEL,FlashCacheBuf.dw.modle);
	addr == FLASH_ADDR_DW_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_RISING_ED,FlashCacheBuf.dw.rising_ed);
	addr == FLASH_ADDR_DW_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_FALLING_ED,FlashCacheBuf.dw.falling_ed);
	addr == FLASH_ADDR_DW_TYPE						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_TYPE,FlashCacheBuf.dw.type);
	addr == FLASH_ADDR_DW_VALUE_1					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_1,FlashCacheBuf.dw.value[0]);
	addr == FLASH_ADDR_DW_VALUE_2					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_2,FlashCacheBuf.dw.value[1]);
	addr == FLASH_ADDR_DW_VALUE_3					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_3,FlashCacheBuf.dw.value[2]);
	addr == FLASH_ADDR_DW_VALUE_4					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_4,FlashCacheBuf.dw.value[3]);
	addr == FLASH_ADDR_DW_VALUE_5					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_5,FlashCacheBuf.dw.value[4]);
	addr == FLASH_ADDR_DW_VALUE_R					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_R,FlashCacheBuf.dw.value[5]);
	addr == FLASH_ADDR_DW_VALUE_ZERO			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DW_VALUE_ZERO,FlashCacheBuf.dw.value[6]);

	//左后视开关
	addr == FLASH_ADDR_ZHS_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZHS_PIN, FlashCacheBuf.zhs.pin);
	addr == FLASH_ADDR_ZHS_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZHS_MODEL,FlashCacheBuf.zhs.modle);
	addr == FLASH_ADDR_ZHS_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZHS_RISING_ED,FlashCacheBuf.zhs.rising_ed);
	addr == FLASH_ADDR_ZHS_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZHS_FALLING_ED,	FlashCacheBuf.zhs.falling_ed);
	addr == FLASH_ADDR_ZHS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZHS_TYPE,	FlashCacheBuf.zhs.type);
	//内后视开关
	addr == FLASH_ADDR_NHS_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_NHS_PIN, FlashCacheBuf.nhs.pin);
	addr == FLASH_ADDR_NHS_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_NHS_MODEL,FlashCacheBuf.nhs.modle);
	addr == FLASH_ADDR_NHS_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_NHS_RISING_ED,FlashCacheBuf.nhs.rising_ed);
	addr == FLASH_ADDR_NHS_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_NHS_FALLING_ED,	FlashCacheBuf.nhs.falling_ed);
	addr == FLASH_ADDR_NHS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_NHS_TYPE,	FlashCacheBuf.nhs.type);
	//副刹开关
	addr == FLASH_ADDR_FSC_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_FSC_PIN, FlashCacheBuf.fsc.pin);
	addr == FLASH_ADDR_FSC_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_FSC_MODEL,FlashCacheBuf.fsc.modle);
	addr == FLASH_ADDR_FSC_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_FSC_RISING_ED,FlashCacheBuf.fsc.rising_ed);
	addr == FLASH_ADDR_FSC_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_FSC_FALLING_ED,	FlashCacheBuf.fsc.falling_ed);
	addr == FLASH_ADDR_FSC_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_FSC_TYPE,	FlashCacheBuf.fsc.type);
	//雾灯开关
	addr == FLASH_ADDR_WD_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_WD_PIN, FlashCacheBuf.wd.pin);
	addr == FLASH_ADDR_WD_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_WD_MODEL,FlashCacheBuf.wd.modle);
	addr == FLASH_ADDR_WD_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_WD_RISING_ED,FlashCacheBuf.wd.rising_ed);
	addr == FLASH_ADDR_WD_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_WD_FALLING_ED,	FlashCacheBuf.wd.falling_ed);
	addr == FLASH_ADDR_WD_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_WD_TYPE,	FlashCacheBuf.wd.type);
	//雨刷开关
	addr == FLASH_ADDR_YS_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YS_PIN, FlashCacheBuf.ys.pin);
	addr == FLASH_ADDR_YS_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YS_MODEL,FlashCacheBuf.ys.modle);
	addr == FLASH_ADDR_YS_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YS_RISING_ED,FlashCacheBuf.ys.rising_ed);
	addr == FLASH_ADDR_YS_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YS_FALLING_ED,	FlashCacheBuf.ys.falling_ed);
	addr == FLASH_ADDR_YS_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YS_TYPE,	FlashCacheBuf.ys.type);
	//倒车灯开关
	addr == FLASH_ADDR_DCD_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DCD_PIN, FlashCacheBuf.dcd.pin);
	addr == FLASH_ADDR_DCD_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DCD_MODEL,FlashCacheBuf.dcd.modle);
	addr == FLASH_ADDR_DCD_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DCD_RISING_ED,FlashCacheBuf.dcd.rising_ed);
	addr == FLASH_ADDR_DCD_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DCD_FALLING_ED,	FlashCacheBuf.dcd.falling_ed);
	addr == FLASH_ADDR_DCD_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DCD_TYPE,	FlashCacheBuf.dcd.type);
	//钥匙门开关
	addr == FLASH_ADDR_YSM_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YSM_PIN, FlashCacheBuf.ysm.pin);
	addr == FLASH_ADDR_YSM_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YSM_MODEL,FlashCacheBuf.ysm.modle);
	addr == FLASH_ADDR_YSM_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YSM_RISING_ED,FlashCacheBuf.ysm.rising_ed);
	addr == FLASH_ADDR_YSM_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YSM_FALLING_ED,	FlashCacheBuf.ysm.falling_ed);
	addr == FLASH_ADDR_YSM_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YSM_TYPE,	FlashCacheBuf.ysm.type);
	//绕车开关1
	addr == FLASH_ADDR_RC_PIN1 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_PIN1,FlashCacheBuf.rc.pin1);
	addr == FLASH_ADDR_RC_PIN2 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_PIN2,FlashCacheBuf.rc.pin2);
	addr == FLASH_ADDR_RC_PIN3 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_PIN3,FlashCacheBuf.rc.pin3);
	addr == FLASH_ADDR_RC_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_MODEL,FlashCacheBuf.rc.modle);
	addr == FLASH_ADDR_RC_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_RISING_ED,FlashCacheBuf.rc.rising_ed);
	addr == FLASH_ADDR_RC_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_FALLING_ED,	FlashCacheBuf.rc.falling_ed);
	addr == FLASH_ADDR_RC_TYPE						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_RC_TYPE,	FlashCacheBuf.rc.type);
	//闯动开关
	addr == FLASH_ADDR_CD_PIN 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CD_PIN, FlashCacheBuf.cd.pin);
	addr == FLASH_ADDR_CD_MODEL 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CD_MODEL,FlashCacheBuf.cd.modle);
	addr == FLASH_ADDR_CD_RISING_ED 			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CD_RISING_ED,FlashCacheBuf.cd.rising_ed);
	addr == FLASH_ADDR_CD_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CD_FALLING_ED,	FlashCacheBuf.cd.falling_ed);
	addr == FLASH_ADDR_CD_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_CD_TYPE,	FlashCacheBuf.cd.type);
	//座椅开关（压力)
	addr == FLASH_ADDR_ZYYL_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYYL_PIN, FlashCacheBuf.zyyl.pin);
	addr == FLASH_ADDR_ZYYL_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYYL_MODEL,FlashCacheBuf.zyyl.modle);
	addr == FLASH_ADDR_ZYYL_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYYL_RISING_ED,FlashCacheBuf.zyyl.rising_ed);
	addr == FLASH_ADDR_ZYYL_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYYL_FALLING_ED,	FlashCacheBuf.zyyl.falling_ed);
	addr == FLASH_ADDR_ZYYL_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZYYL_TYPE,	FlashCacheBuf.zyyl.type);
	
	//里程计数
	addr == FLASH_ADDR_LCJS_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LCJS_PIN, FlashCacheBuf.lc.pin);
	addr == FLASH_ADDR_LCJS_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LCJS_MODEL,FlashCacheBuf.lc.modle);
	addr == FLASH_ADDR_LCJS_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LCJS_RISING_ED,FlashCacheBuf.lc.rising_ed);
	addr == FLASH_ADDR_LCJS_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LCJS_FALLING_ED,	FlashCacheBuf.lc.falling_ed);
	addr == FLASH_ADDR_LCJS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_LCJS_TYPE,	FlashCacheBuf.lc.type);
	
	//观察仪表盘
	addr == FLASH_ADDR_GCYBP_PIN					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GCYBP_PIN, FlashCacheBuf.gcybp.pin);
	addr == FLASH_ADDR_GCYBP_MODEL				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GCYBP_MODEL,FlashCacheBuf.gcybp.modle);
	addr == FLASH_ADDR_GCYBP_RISING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GCYBP_RISING_ED,FlashCacheBuf.gcybp.rising_ed);
	addr == FLASH_ADDR_GCYBP_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GCYBP_FALLING_ED,	FlashCacheBuf.gcybp.falling_ed);
	addr == FLASH_ADDR_GCYBP_TYPE 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GCYBP_TYPE,	FlashCacheBuf.gcybp.type);
	
	
	//触发开始考试信号
	addr == FLASH_ADDR_BEGIN_PIN					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BEGIN_PIN, FlashCacheBuf.begin.pin);
	addr == FLASH_ADDR_BEGIN_MODEL				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BEGIN_MODEL,FlashCacheBuf.begin.modle);
	addr == FLASH_ADDR_BEGIN_RISING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BEGIN_RISING_ED,FlashCacheBuf.begin.rising_ed);
	addr == FLASH_ADDR_BEGIN_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BEGIN_FALLING_ED,	FlashCacheBuf.begin.falling_ed);
	addr == FLASH_ADDR_BEGIN_TYPE 				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BEGIN_TYPE,	FlashCacheBuf.begin.type);
	
	//转速
	addr == FLASH_ADDR_ZS_PIN							? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZS_PIN, FlashCacheBuf.zs.pin);
	addr == FLASH_ADDR_ZS_IDLIN_MIN				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZS_IDLIN_MIN,FlashCacheBuf.zs.min);
	addr == FLASH_ADDR_ZS_XH_MAX					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZS_XH_MAX,FlashCacheBuf.zs.max);
	addr == FLASH_ADDR_ZS_BS							? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZS_BS,FlashCacheBuf.zs.bs);
	addr == FLASH_ADDR_ZS_SAMPLING_TIME		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZS_SAMPLING_TIME,FlashCacheBuf.zs.sampling_time);
	addr == FLASH_ADDR_ZS_INIT_VALUE			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZS_INIT_VALUE,	FlashCacheBuf.zs.init_value);	

	//单边桥传感器
	addr == FLASH_ADDR_DBQ_PIN1						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_PIN1,FlashCacheBuf.dbq.pin1);
	addr == FLASH_ADDR_DBQ_PIN2						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_PIN2,FlashCacheBuf.dbq.pin2);
	addr == FLASH_ADDR_DBQ_PIN3						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_PIN3,FlashCacheBuf.dbq.pin3);
	addr == FLASH_ADDR_DBQ_PIN4						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_PIN4,FlashCacheBuf.dbq.pin4);
	addr == FLASH_ADDR_DBQ_PIN5						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_PIN5,FlashCacheBuf.dbq.pin5);	
	addr == FLASH_ADDR_DBQ_PIN6						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_PIN6,FlashCacheBuf.dbq.pin6);
	addr == FLASH_ADDR_DBQ_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_MODEL,FlashCacheBuf.dbq.modle);
	addr == FLASH_ADDR_DBQ_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_RISING_ED,FlashCacheBuf.dbq.rising_ed);
	addr == FLASH_ADDR_DBQ_FALLING_ED		  ? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_FALLING_ED,	FlashCacheBuf.dbq.falling_ed);
	addr == FLASH_ADDR_DBQ_TYPE						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DBQ_TYPE,	FlashCacheBuf.dbq.type);	
	
	
	//板卡信息 板号board
	addr == FLASH_ADDR_TRIGGER_MODE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TRIGGER_MODE, FlashCacheBuf.board.trigger_mode);
	addr == FLASH_ADDR_DEVICE_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_DEVICE_TYPE, FlashCacheBuf.board.device_type);
	addr == FLASH_ADDR_BOARD_ID_L					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BOARD_ID_L, FlashCacheBuf.board.number_L);
	addr == FLASH_ADDR_BOARD_ID_H					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_BOARD_ID_H, FlashCacheBuf.board.number_H);
	
#ifdef  STC15W4K48S4	
	//摩托车头盔
	addr == FLASH_ADDR_TK_PIN							? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TK_PIN, FlashCacheBuf.tk.pin);
	addr == FLASH_ADDR_TK_MODEL						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TK_MODEL,FlashCacheBuf.tk.modle);
	addr == FLASH_ADDR_TK_RISING_ED				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TK_RISING_ED,FlashCacheBuf.tk.rising_ed);
	addr == FLASH_ADDR_TK_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TK_FALLING_ED,	FlashCacheBuf.tk.falling_ed);
	addr == FLASH_ADDR_TK_TYPE 						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_TK_TYPE,	FlashCacheBuf.tk.type);
	
	//摩托车左把手
	addr == FLASH_ADDR_ZBS_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZBS_PIN, FlashCacheBuf.zbs.pin);
	addr == FLASH_ADDR_ZBS_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZBS_MODEL,FlashCacheBuf.zbs.modle);
	addr == FLASH_ADDR_ZBS_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZBS_RISING_ED,FlashCacheBuf.zbs.rising_ed);
	addr == FLASH_ADDR_ZBS_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZBS_FALLING_ED,	FlashCacheBuf.zbs.falling_ed);
	addr == FLASH_ADDR_ZBS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZBS_TYPE,	FlashCacheBuf.zbs.type);
	
	//摩托车右把手
	addr == FLASH_ADDR_YBS_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YBS_PIN, FlashCacheBuf.ybs.pin);
	addr == FLASH_ADDR_YBS_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YBS_MODEL,FlashCacheBuf.ybs.modle);
	addr == FLASH_ADDR_YBS_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YBS_RISING_ED,FlashCacheBuf.ybs.rising_ed);
	addr == FLASH_ADDR_YBS_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YBS_FALLING_ED,	FlashCacheBuf.ybs.falling_ed);
	addr == FLASH_ADDR_YBS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YBS_TYPE,	FlashCacheBuf.ybs.type);
	
	//摩托车左脚踏板
	addr == FLASH_ADDR_ZJTB_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZJTB_PIN, FlashCacheBuf.zjtb.pin);
	addr == FLASH_ADDR_ZJTB_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZJTB_MODEL,FlashCacheBuf.zjtb.modle);
	addr == FLASH_ADDR_ZJTB_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZJTB_RISING_ED,FlashCacheBuf.zjtb.rising_ed);
	addr == FLASH_ADDR_ZJTB_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZJTB_FALLING_ED,	FlashCacheBuf.zjtb.falling_ed);
	addr == FLASH_ADDR_ZJTB_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_ZJTB_TYPE,	FlashCacheBuf.zjtb.type);
	
	//摩托车右脚踏板
	addr == FLASH_ADDR_YJTB_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YJTB_PIN, FlashCacheBuf.yjtb.pin);
	addr == FLASH_ADDR_YJTB_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YJTB_MODEL,FlashCacheBuf.yjtb.modle);
	addr == FLASH_ADDR_YJTB_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YJTB_RISING_ED,FlashCacheBuf.yjtb.rising_ed);
	addr == FLASH_ADDR_YJTB_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YJTB_FALLING_ED,	FlashCacheBuf.yjtb.falling_ed);
	addr == FLASH_ADDR_YJTB_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_YJTB_TYPE,	FlashCacheBuf.yjtb.type);
	
	//碰杆接收
	addr == FLASH_ADDR_PGJS_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_PIN, FlashCacheBuf.pgjs.pin);
	addr == FLASH_ADDR_PGJS_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_MODEL,FlashCacheBuf.pgjs.modle);
	addr == FLASH_ADDR_PGJS_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_RISING_ED,FlashCacheBuf.pgjs.rising_ed);
	addr == FLASH_ADDR_PGJS_FALLING_ED		? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_FALLING_ED,	FlashCacheBuf.pgjs.falling_ed);
	addr == FLASH_ADDR_PGJS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_TYPE,	FlashCacheBuf.pgjs.type);

	//碰杆项目1
	addr == FLASH_ADDR_PGJS_1_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_1_NAME, FlashCacheBuf.bump[0].name);
	addr == FLASH_ADDR_PGJS_1_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_1_N0,FlashCacheBuf.bump[0].number);
	addr == FLASH_ADDR_PGJS_1_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_1_COUNT,FlashCacheBuf.bump[0].count);
	addr == FLASH_ADDR_PGJS_1_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_1_TYPE,FlashCacheBuf.bump[0].type);
	
	//碰杆项目2
	addr == FLASH_ADDR_PGJS_2_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_2_NAME, FlashCacheBuf.bump[1].name);
	addr == FLASH_ADDR_PGJS_2_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_2_N0,FlashCacheBuf.bump[1].number);
	addr == FLASH_ADDR_PGJS_2_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_2_COUNT,FlashCacheBuf.bump[1].count);
	addr == FLASH_ADDR_PGJS_2_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_2_TYPE,FlashCacheBuf.bump[1].type);
	
	//碰杆项目3
	addr == FLASH_ADDR_PGJS_3_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_3_NAME, FlashCacheBuf.bump[2].name);
	addr == FLASH_ADDR_PGJS_3_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_3_N0,FlashCacheBuf.bump[2].number);
	addr == FLASH_ADDR_PGJS_3_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_3_COUNT,FlashCacheBuf.bump[2].count);
	addr == FLASH_ADDR_PGJS_3_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_3_TYPE,FlashCacheBuf.bump[2].type);
	
	//碰杆项目4
	addr == FLASH_ADDR_PGJS_4_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_4_NAME, FlashCacheBuf.bump[3].name);
	addr == FLASH_ADDR_PGJS_4_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_4_N0,FlashCacheBuf.bump[3].number);
	addr == FLASH_ADDR_PGJS_4_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_4_COUNT,FlashCacheBuf.bump[3].count);
	addr == FLASH_ADDR_PGJS_4_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_4_TYPE,FlashCacheBuf.bump[3].type);
	
		//摩托车前手刹
	addr == FLASH_ADDR_QSS_PIN						? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QSS_PIN, FlashCacheBuf.qss.pin);
	addr == FLASH_ADDR_QSS_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QSS_MODEL,FlashCacheBuf.qss.modle);
	addr == FLASH_ADDR_QSS_RISING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QSS_RISING_ED,FlashCacheBuf.qss.rising_ed);
	addr == FLASH_ADDR_QSS_FALLING_ED			? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QSS_FALLING_ED,	FlashCacheBuf.qss.falling_ed);
	addr == FLASH_ADDR_QSS_TYPE 					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_QSS_TYPE,	FlashCacheBuf.qss.type);
	
	//碰杆项目5
	addr == FLASH_ADDR_PGJS_5_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_5_NAME, FlashCacheBuf.bump[4].name);
	addr == FLASH_ADDR_PGJS_5_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_5_N0,FlashCacheBuf.bump[4].number);
	addr == FLASH_ADDR_PGJS_5_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_5_COUNT,FlashCacheBuf.bump[4].count);
	addr == FLASH_ADDR_PGJS_5_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_5_TYPE,FlashCacheBuf.bump[4].type);
	
	//碰杆项目6
	addr == FLASH_ADDR_PGJS_6_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_6_NAME, FlashCacheBuf.bump[5].name);
	addr == FLASH_ADDR_PGJS_6_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_6_N0,FlashCacheBuf.bump[5].number);
	addr == FLASH_ADDR_PGJS_6_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_6_COUNT,FlashCacheBuf.bump[5].count);
	addr == FLASH_ADDR_PGJS_6_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_6_TYPE,FlashCacheBuf.bump[5].type);
	
	//碰杆项目7
	addr == FLASH_ADDR_PGJS_7_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_7_NAME, FlashCacheBuf.bump[6].name);
	addr == FLASH_ADDR_PGJS_7_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_7_N0,FlashCacheBuf.bump[6].number);
	addr == FLASH_ADDR_PGJS_7_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_7_COUNT,FlashCacheBuf.bump[6].count);
	addr == FLASH_ADDR_PGJS_7_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_7_TYPE,FlashCacheBuf.bump[6].type);
	
	//碰杆项目8
	addr == FLASH_ADDR_PGJS_8_NAME				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_8_NAME, FlashCacheBuf.bump[7].name);
	addr == FLASH_ADDR_PGJS_8_N0					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_8_N0,FlashCacheBuf.bump[7].number);
	addr == FLASH_ADDR_PGJS_8_COUNT				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_8_COUNT,FlashCacheBuf.bump[7].count);
	addr == FLASH_ADDR_PGJS_8_TYPE				? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_PGJS_8_TYPE,FlashCacheBuf.bump[7].type);

	//GNSS型号
	addr == FLASH_ADDR_GNSS_MODEL					? IapWriteByte(addr,value) : IapWriteByte(FLASH_ADDR_GNSS_MODEL,FlashCacheBuf.gnss.model);









#endif
	
}


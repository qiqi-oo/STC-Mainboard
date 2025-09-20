#include <stdio.h>
#include "./User/includes.h"
#include <string.h>

#define ID_ADDR_RAM 0xF1                //STC系列ID号的存放在RAM区的地址
//#define ID_ADDR_ROM 0x03f9      //1K程序空间的MCU(如                                             STC15F201EA, STC15F101EA)
//#define ID_ADDR_ROM 0x07f9      //2K程序空间的MCU(如                              STC15F402EACS, STC15F202EA, STC15F102EA)
//#define ID_ADDR_ROM 0x0bf9      //3K程序空间的MCU(如                                             STC15F203EA, STC15F103EA)
//#define ID_ADDR_ROM 0x0ff9      //4K程序空间的MCU(如               STC15F804EACS, STC15F404EACS, STC15F204EA, STC15F104EA)
//#define ID_ADDR_ROM 0x13f9      //5K程序空间的MCU(如                                             STC15F205EA, STC15F105EA)
//#define ID_ADDR_ROM 0x1ff9      //8K程序空间的MCU(如STC15F2K08S2,  STC15F808EACS, STC15F408EACS)
//#define ID_ADDR_ROM 0x27f9      //10K程序空间的MCU(如                             STC15F410EACS)
//#define ID_ADDR_ROM 0x2ff9      //12K程序空间的MCU(如              STC15F812EACS, STC15F412EACS)
//#define ID_ADDR_ROM 0x3ff9      //16K程序空间的MCU(如STC15F2K16S2, STC15F816EACS)
//#define ID_ADDR_ROM 0x4ff9      //20K程序空间的MCU(如STC15F2K20S2, STC15F820EACS)
//#define ID_ADDR_ROM 0x5ff9      //24K程序空间的MCU(如              STC15F824EACS)
//#define ID_ADDR_ROM 0x6ff9      //28K程序空间的MCU(如              STC15F828EACS)
//#define ID_ADDR_ROM 0x7ff9      //32K程序空间的MCU(如STC15F2K32S2)
//#define ID_ADDR_ROM 0x9ff9      //40K程序空间的MCU(如STC15F2K40S2)
#define ID_ADDR_ROM 0xbff9      	//48K程序空间的MCU(如STC15F2K48S2)
//#define ID_ADDR_ROM 0xcff9      //52K程序空间的MCU(如STC15F2K52S2)
//#define ID_ADDR_ROM 0xdff9      //56K程序空间的MCU(如STC15F2K56S2)
//========================================================================
// 函数: BSP_GetlocalId(char *strid)
// 描述: 读取MCU芯片的序列号
// 参数：*strid[]指向串号保存的内存，保存格式为字符串
//			 lenth  读取的串号长度，STC12系列/STC12系列,长度为7
// 返回: 无
// 版本: V1.0, 2022-10-17
//========================================================================
void BSP_GetlocalId(u8 *id)				//读取单片机ID信息
{
		unsigned char idata *iptr;
    //unsigned char code *cptr;
    unsigned char i=0;
			
    iptr = ID_ADDR_RAM;                 //从RAM区读取ID号
    for (i=0; i<7; i++)             		//读7个字节
    {
			*id++ = (*iptr++);			
    }
		
//		while(i)
//		{
//			
//			printf("ID = ");	
//			for (i=0; i<7; i++)             		//读7个字节
//			{
//				printf("%b02X",localid[i]);	
//						
//			}
//			printf("\r\n");	
//			delay_ms(1000);	
//	  }
		
		
//    cptr = ID_ADDR_ROM;              	//从程序区读取ID号
//    for (i=0; i<7; i++)              	//读7个字节
//    {
//        *id++ = (*cptr++);             //发送ID到串口
//    }			
}
/***********************************************************************/
#ifndef	__FLASH_H
#define	__FLASH_H
#include	"./User/config.h"


u8 IapReadByte(u16 addr);
void IapWriteByte(u16 addr, u8 dat);
void IapEraseSector(u16 addr);

#endif



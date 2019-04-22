/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sdfat.h                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :SD FAT16system Library Header      */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_SDFAT_H_
#define CORON_SDFAT_H_

/* Include -----------------------------------------------------------*/
#include "sdcard.h"

/* Type define -------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Define ------------------------------------------------------------*/
#define SDIO_CD_H	GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define SDIO_CD_L	GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define SDIO_D1_H	GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define SDIO_D1_L	GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define SDIO_D2_H	GPIO_SetBits(GPIOC, GPIO_Pin_10)
#define SDIO_D2_L	GPIO_ResetBits(GPIOC, GPIO_Pin_10)

#define BlockSize            512 /* Block Size in Bytes */
#define BufferWordsSize      (BlockSize >> 2)
#define NumberOfBlocks       2  /* For Multi Blocks operation (Read/Write) */
#define MultiBufferWordsSize ((BlockSize * NumberOfBlocks) >> 2)

/* Extern ------------------------------------------------------------*/
extern u32	hidden_sector;
extern u32	fat_sector,dir_sector,dat_sector;
extern u8 	sectors_per_cluster;
extern u32 buf512[512];
extern u32 Buffer_Block_Tx[BufferWordsSize], Buffer_Block_Rx[BufferWordsSize];
extern u32 Buffer_MultiBlock_Tx[MultiBufferWordsSize], Buffer_MultiBlock_Rx[MultiBufferWordsSize];
extern volatile TestStatus EraseStatus,TransferStatus1,TransferStatus2;

extern int 	SD_FATinit();
extern void 	SD_read(u32 adr);
extern void 	SD_write(u32 adr);
extern s16 		SD_char_to_num(char *s,char len);
extern void 	SD_num_to_char(long num,u8 len,char *s);
extern void 	SD_getDirSector(void);
extern u16		SD_getFileList(u32 sec,char *sn,char (*file_name)[8],u32 *sct_num,u32 *size);
extern u32 		SD_serchDirectory(const char* s);

#endif /*CORON_SDFAT_H_*/

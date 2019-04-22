/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sdtxt.h                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :SD Text File R&W Library Header    */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_SDTXT_H_
#define CORON_SDTXT_H_

#include "coron_conf.h"

/* Extern ------------------------------------------------------------*/
extern void SD_search_txt(void);

#ifdef _CORON_USBCDC
extern void SD_txt_USBput(u8 txt_num,u8 header_flag);
#endif

#ifdef _CORON_UART
extern void SD_txt_UARTput(u8 txt_num,u8 header_flag);
#endif

extern char SD_txt_read_c(u8 txt_num,u32 s_num);
extern void SD_txt_write_c(u8 txt_num,u32 s_num,char wbuf);
extern void SD_txt_read_s(u8 txt_num,u32 s_num,char* buf,u16 len);
extern void SD_txt_write_s(u8 txt_num,u32 s_num,char* buf,u16 len);

extern u32	txt_dir_sector;
extern u32 txt_sector_num[50];
extern u32 txt_size[50];
extern char txt_name[50][8];
extern u8 txt_count;

#endif /*CORON_SDTXT_H_*/

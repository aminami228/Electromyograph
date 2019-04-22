/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sdwav.h                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :SD "WAV"play Library Header        */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_SDWAV_H_
#define CORON_SDWAV_H_

/* Extern ------------------------------------------------------------*/
extern void SD_search_wav();
extern void SD_play_wav(u8 wav_num);

extern u32	sound_sector;
extern u32 wav_sector_num[50];
extern u32 wav_size[50];
extern char wav_name[50][8];
extern u8 wav_count;

#endif /*CORON_SDWAV_H_*/

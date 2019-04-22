/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sound.h                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Speaker output Library Header      */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_SOUND_H_
#define CORON_SOUND_H_

/* Extern ------------------------------------------------------------*/
extern u8 	sound_flag;				//再生フラグ
extern u8 	sound_buf[2][512];		//音データバッファ
extern u16 sound_buf0_count;		//音データバッファbuf[0]バイトカウント数
extern u16 sound_buf1_count;		//音データバッファbuf[1]バイトカウント数
extern u8 	read_flag;				//バッファ格納完了フラグ

extern void SPK_init(void);
extern void TIM5_SOUND_IRQ();

#endif /*CORON_SOUND_H_*/

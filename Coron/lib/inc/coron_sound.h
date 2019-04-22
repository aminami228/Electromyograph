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
extern u8 	sound_flag;				//�Đ��t���O
extern u8 	sound_buf[2][512];		//���f�[�^�o�b�t�@
extern u16 sound_buf0_count;		//���f�[�^�o�b�t�@buf[0]�o�C�g�J�E���g��
extern u16 sound_buf1_count;		//���f�[�^�o�b�t�@buf[1]�o�C�g�J�E���g��
extern u8 	read_flag;				//�o�b�t�@�i�[�����t���O

extern void SPK_init(void);
extern void TIM5_SOUND_IRQ();

#endif /*CORON_SOUND_H_*/

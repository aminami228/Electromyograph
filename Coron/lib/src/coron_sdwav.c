/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sdwav.c                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :SD "WAV"play Library Source        */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_SD
#ifdef _CORON_SOUND
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Global variables ----------------------------------------------------------*/
u32	sound_sector=0;			//WAV�t�@�C���f�B���N�g���̃Z�N�^�ԍ�
u32 wav_sector_num[50];		//�eWAV�t�@�C���̃Z�N�^�ԍ�
u32 wav_size[50];			//WAV�t�@�C���̃T�C�Y
char wav_name[50][8];		//WAV�t�@�C���̖��O
u8 wav_count;				//"SoundData"�t�H���_����WAV�t�@�C���̐�

//==============================================================================
// SD�J�[�hWAV�t�@�C������
//==============================================================================
void SD_search_wav(void){
	sound_sector=SD_serchDirectory("SOUNDD");
	wav_count=SD_getFileList(sound_sector,"WAV",wav_name,wav_sector_num,wav_size);
}

//==============================================================================
// SD�J�[�hWAV�t�@�C���Đ�(�Z�N�^�ԍ�)
//==============================================================================
void SD_play_wav(u8 wav_num){
	u32 size;
	u32 sct,sec_num,n,i;
	u32 last_byte_num;
	size =wav_size[wav_num];
	sct  =wav_sector_num[wav_num];
		
	/* TIM5 enable counter */
	TIM_Cmd(TIM5, ENABLE);	
	//WAV�t�@�C���f�[�^������Z�N�^���|1
	sec_num=(size/512);
	//�Ō�̃Z�N�^�̃o�C�g���|1
	last_byte_num=(size%512)-1;
	
	//�ŏ��̃Z�N�^�����w�b�_�����΂�
	SD_read(sct*512);
    for(i=0;i<0x3a;i++){sound_buf[0][i]=0x80;}
    for(i=0x3a;i<512;i++){sound_buf[0][i]=buf512[i];}
    sound_flag=1;

	//�Q�ڈȍ~�̃Z�N�^��ǂݍ���
    for(n=1;n<(sec_num);n++){
    	SD_read(512*(n + sct));
    	if(sound_flag==2){
        	for(i=0;i<512;i++){sound_buf[0][i]=buf512[i];}
        	while(sound_flag==2){read_flag=1;}
        	read_flag=0;
    	}
    	else if(sound_flag==1){
        	for(i=0;i<512;i++){sound_buf[1][i]=buf512[i];}
        	while(sound_flag==1){read_flag=1;}
        	read_flag=0;
    	}
    }
	//�Ō�̃Z�N�^��ǂݍ���(�f�[�^�������������΂�)
    SD_read(512*(sct+sec_num));
    for(i=last_byte_num;i<512;i++){
    	buf512[i]=0x80;
    }
    
	if(sound_flag==2){
    	for(i=1;i<512;i++){sound_buf[0][i]=buf512[i];}
    	while(sound_flag==2){read_flag=1;}
	}
	else if(sound_flag==1){
    	for(i=0;i<512;i++){sound_buf[1][i]=buf512[i];}
    	while(sound_flag==1){read_flag=1;}
	}
        
    sound_flag=0;

	/* TIM5 disable counter */
	TIM_Cmd(TIM5, DISABLE);	
}

#endif
#endif

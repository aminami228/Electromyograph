/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sound.c                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Speaker output Library Source      */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_SOUND
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Global variables ----------------------------------------------------------*/
u8 	sound_flag=0;				//�Đ��t���O
u8 	sound_buf[2][512];			//���f�[�^�o�b�t�@
u16 sound_buf0_count=0;			//���f�[�^�o�b�t�@buf[0]�o�C�g�J�E���g��
u16 sound_buf1_count=0;			//���f�[�^�o�b�t�@buf[1]�o�C�g�J�E���g��
u8 	read_flag=0;				//�o�b�t�@�i�[�����t���O

//==============================================================================
// �X�s�[�J�o�͏�����
//==============================================================================
void SPK_init(void){
	GPIO_InitTypeDef 		GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	DAC_InitTypeDef   		DAC_InitStructure;
    NVIC_InitTypeDef 		NVIC_InitStructure;

    /* Default reset */
    TIM_DeInit(TIM5);
    
	//Speaker init      
    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Enable the TIM5 Interrupt */
    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
	
    /* TIM5 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
	/* TIM5 configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 653;
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0004;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	/* Immediate load of TIM5 Precaler value */
	TIM_PrescalerConfig(TIM5, 0x0004, TIM_PSCReloadMode_Immediate);
	/* Clear TIM5 update pending flag */
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	/* Enable TIM5 Update interrupt */
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	/* TIM5 disable counter */
	TIM_Cmd(TIM5, DISABLE);	
	
    /* DAC channel1 Configuration */
	DAC_StructInit(&DAC_InitStructure);
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);

    /* Ensable DAC Channel1 */
    DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC_Align_8b_R,0x80);
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);    	
}

//==============================================================================
// �X�s�[�J�[�A�i���O�o��(TIM5���荞��)
//==============================================================================
void TIM5_SOUND_IRQ(){
	//22[kHz]
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);//TIM5���荞�݃t���O�N���A

RESTART:
	//���f�[�^��buf0��buf1�Ō��݂ɍĐ�(SD�J�[�h�̓ǂݍ��݂Ɖ��Đ��𓯎��ɂ����)
	if(sound_flag==1){//buf0�Đ�
    	if(sound_buf0_count==512){	//buf0���Đ��I��
   			if(read_flag==1){		//	buf1���f�[�^�ǂݍ��݊����m�F
   	    		sound_buf0_count=0;
   	   			sound_flag=2;		//	buf1�Đ��J�n
   	   			goto RESTART;
   			}
    	}
    	else{
    		//DAC1 �o�͓d���l(8bit�E�l)�Z�b�g
   			DAC_SetChannel1Data(DAC_Align_8b_R, sound_buf[0][sound_buf0_count]);
    		//DAC1 �o�̓g���K�Z�b�g
    		DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
    		sound_buf0_count++;
    	}
   	}
    else if(sound_flag==2){//buf1�Đ�
    	if(sound_buf1_count==512){	//buf1���Đ��I��
   			if(read_flag==1){		//	buf0���f�[�^�ǂݍ��݊����m�F
   	    		sound_buf1_count=0;
   	    		sound_flag=1;		//	buf0�Đ��J�n
   	   			goto RESTART;
   			}
    	}
    	else{
    		//DAC1 �o�͓d���l(8bit�E�l)�Z�b�g
    		DAC_SetChannel1Data(DAC_Align_8b_R, sound_buf[1][sound_buf1_count]);
    		//DAC1 �o�̓g���K�Z�b�g
    		DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);
    		sound_buf1_count++;
   		}
   	}
    else if(sound_flag==0){//���f�[�^�Đ���~
    	sound_buf0_count=0;
    	sound_buf1_count=0;
    }
}

#endif
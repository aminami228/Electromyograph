/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_rc.c                         */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :RCservo Library Source             */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_RC
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Global variables ----------------------------------------------------------*/
u16 rc_mot_ipos[2][8];				//�p�x�ڕW�l
u8  rc_step_flag=0;					//���x����t���O
s16 rc_mot_pos_step[2][8];			//���x����X�e�b�v�p
u8 	rc_mot_ch[2];
u8 	rc_step_num=0;					
u8 	rc_step_count=0;				

u16 rc_mot_pos[2][8];				//���݂̊e�T�[�{�o�͊p�x
u16 rc_mot_pos_home[2][8];			//�e�T�[�{�̃z�[���|�W�V����
s16 rc_mot_pos_trim[2][8];			//�e�T�[�{�̃g����
u16 rc_mot_motion_pos[100][2][8];	//���[�V�����f�[�^�̊e�o�͊p�x
u8  rc_mot_motion_spd[100];			//���[�V�����f�[�^�̃T�[�{�X�s�[�h
u8  rc_mot_motion_cnt;

/* Prototype -----------------------------------------------------------------*/
void RC_exeHomePosition();
void RC_init();
void RC_enable();
void RC_disable();
void RC_move(u8 time);

//==============================================================================
// RC1_20msPWM�o��(TIM3���荞��)
//==============================================================================
void TIM3_RC1_IRQ(){
	//CC1���荞��(700~2300[us])
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);//TIM3_CC1���荞�݃t���O�N���A
	    //�p���X�̗�������
	    RC1_PWM_L;
	}
	//CC2���荞��(2500[us](x8=20[ms]))
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET){
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);//TIM3_CC2���荞�݃t���O�N���A
	    //PWM�o��ch�Z�b�g(3to8 decode)
	    switch(rc_mot_ch[0]){
			case 0:RC1_A0_L;RC1_A1_L;RC1_A2_L;break;//RC1-0
			case 1:RC1_A0_H;RC1_A1_L;RC1_A2_L;break;//RC1-1
			case 2:RC1_A0_L;RC1_A1_H;RC1_A2_L;break;//RC1-2
			case 3:RC1_A0_H;RC1_A1_H;RC1_A2_L;break;//RC1-3
			case 4:RC1_A0_L;RC1_A1_L;RC1_A2_H;break;//RC1-4
			case 5:RC1_A0_H;RC1_A1_L;RC1_A2_H;break;//RC1-5
			case 6:RC1_A0_L;RC1_A1_H;RC1_A2_H;break;//RC1-6
			case 7:RC1_A0_H;RC1_A1_H;RC1_A2_H;break;//RC1-7
		}
	    //�p���X�̗����グ
	    RC1_PWM_H;
		//CC1���荞�݃^�C�~���O�̃Z�b�g(������������[us]�Z�b�g)
		TIM_SetCompare1(TIM3, (rc_mot_pos[0][rc_mot_ch[0]] - rc_mot_pos_trim[0][rc_mot_ch[0]]));
		if(rc_mot_ch[0]>6){rc_mot_ch[0]=0;}//ch7 -> ch0
		else{rc_mot_ch[0]++;}
	}
}

//==============================================================================
// RC2_20msPWM�o��(TIM4���荞��)
//==============================================================================
void TIM4_RC2_IRQ(){
	//CC1���荞��(700~2300[us])
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET){
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);//TIM4_CC1���荞�݃t���O�N���A
	    //�p���X�̗�������
	    RC2_PWM_L;
	}
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET){
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);//TIM4_CC2���荞�݃t���O�N���A
	    //PWM�o��ch�Z�b�g(3to8 decode)
	    switch(rc_mot_ch[0]){
			case 0:RC2_A0_L;RC2_A1_L;RC2_A2_L;break;//RC2-0
			case 1:RC2_A0_H;RC2_A1_L;RC2_A2_L;break;//RC2-1
			case 2:RC2_A0_L;RC2_A1_H;RC2_A2_L;break;//RC2-2
			case 3:RC2_A0_H;RC2_A1_H;RC2_A2_L;break;//RC2-3
			case 4:RC2_A0_L;RC2_A1_L;RC2_A2_H;break;//RC2-4
			case 5:RC2_A0_H;RC2_A1_L;RC2_A2_H;break;//RC2-5
			case 6:RC2_A0_L;RC2_A1_H;RC2_A2_H;break;//RC2-6
			case 7:RC2_A0_H;RC2_A1_H;RC2_A2_H;break;//RC2-7
		}
	    //�p���X�̗����グ
	    RC2_PWM_H;
		//CC1���荞�݃^�C�~���O�̃Z�b�g(������������[us]�Z�b�g)
		TIM_SetCompare1(TIM4, (rc_mot_pos[1][rc_mot_ch[1]] - rc_mot_pos_trim[1][rc_mot_ch[1]]));
		if(rc_mot_ch[1]>6){rc_mot_ch[1]=0;}//ch7 -> ch0
		else{rc_mot_ch[1]++;}
	}
}

//==============================================================================
// RC�T�[�{���x����(TIM6���荞��)
//==============================================================================
void TIM6_RC_Speed(){
	int i,j=0;
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);//TIM6���荞�݃t���O�N���A

	if(rc_step_flag){//���x���䋖�t���O�m�F
		//�X�e�b�v�p��������
		if(rc_step_num>=rc_step_count){
			for(i=0;i<2;i++){
				for(j=0;j<8;j++){
					//���̃X�e�b�v�p�̌v�Z(���덷�y���̈�)
					rc_mot_pos_step[i][j]=((s16)rc_mot_ipos[i][j]-(s16)rc_mot_pos[i][j])/(rc_step_num-rc_step_count);
					//1�X�e�b�v���ړ�
					rc_mot_pos[i][j] += rc_mot_pos_step[i][j];
				}
			}
		}
		else{
			rc_step_count=0;
			rc_step_flag=0;
		}
		rc_step_count++;
	}
}

//==============================================================================
// RC�T�[�{�@�z�[���|�W�V�������s
//==============================================================================
void RC_exeHomePosition(){
	int i;
    for(i=0;i<8;i++){
    	rc_mot_ipos[0][i]=rc_mot_pos_home[0][i];
    	rc_mot_ipos[1][i]=rc_mot_pos_home[1][i];
    }
	RC_enable();
    RC_move(100);
	while(rc_step_flag);
}

//==============================================================================
// RC�T�[�{�@�p�����[�^������
//==============================================================================
void RC_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
    
	int i;
	
    /* Default reset */
    TIM_DeInit(TIM3);
    TIM_DeInit(TIM4);
    TIM_DeInit(TIM6);
	
	//RC1 init
    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	//RC2 init
    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    /* TIM6 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
    /* Enable the TIM3 Interrupt */
    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Enable the TIM4 Interrupt */
    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
    /* Enable the TIM6 Interrupt */
    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 

	/* TIM3 configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 2500;
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1);
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* Immediate load of TIM3 Precaler value */
	TIM_PrescalerConfig(TIM3,(72-1), TIM_PSCReloadMode_Immediate);
	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
	/* Output Compare Active Mode configuration: Channel2 */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 2500;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);  
	TIM_ITConfig(TIM3, TIM_IT_CC1|TIM_IT_CC2, ENABLE);
	/* Clear TIM3 update pending flag */
	TIM_ClearFlag(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4);
	  
	/* TIM4 configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 2500;
	TIM_TimeBaseStructure.TIM_Prescaler = (72-1);
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/* Immediate load of TIM4 Precaler value */
	TIM_PrescalerConfig(TIM4,(72-1), TIM_PSCReloadMode_Immediate);
	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);
	/* Output Compare Active Mode configuration: Channel2 */
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 2500;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);  
	TIM_ITConfig(TIM4, TIM_IT_CC1|TIM_IT_CC2, ENABLE);
	/* Clear TIM4 update pending flag */
	TIM_ClearFlag(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4);
	  
	/* TIM6 configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 72;
	TIM_TimeBaseStructure.TIM_Prescaler = (20000-1);
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	/* Immediate load of TIM6 Precaler value */
	TIM_PrescalerConfig(TIM6, 20000-1, TIM_PSCReloadMode_Immediate);
	/* Clear TIM6 update pending flag */
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	/* Enable TIM6 Update interrupt */
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	/* TIM3 disable counter */
	TIM_Cmd(TIM3, DISABLE);
	/* TIM4 disable counter */
	TIM_Cmd(TIM4, DISABLE);
	/* TIM6 disable counter */
	TIM_Cmd(TIM6, DISABLE);    
    
	RC_disable();
    rc_mot_ch[0]=0;
    rc_mot_ch[1]=0;	
	for(i=0;i<8;i++){
    	rc_mot_pos[0][i]=1500;
    	rc_mot_pos[1][i]=1500;
    	rc_mot_ipos[0][i]=1500;
    	rc_mot_ipos[1][i]=1500;
    	rc_mot_pos_home[0][i]=1500;
    	rc_mot_pos_home[1][i]=1500;
    	rc_mot_pos_trim[0][i]=0;
    	rc_mot_pos_trim[1][i]=0;
    }
}

//==============================================================================
// RC�T�[�{�@�o�͊J�n
//==============================================================================
void RC_enable(){
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4, ENABLE);	
	TIM_Cmd(TIM6, ENABLE);    
}

//==============================================================================
// RC�T�[�{�@�o�͒�~
//==============================================================================
void RC_disable(){
	TIM_Cmd(TIM3, DISABLE);
	TIM_Cmd(TIM4, DISABLE);	
	TIM_Cmd(TIM6, DISABLE);    
}

//==============================================================================
// RC�T�[�{�@�ڕW�p�x�ֈړ�(���x����t��)
//==============================================================================
void RC_move(u8 time){
	int i,j;
	//�ő��ړ���
	if(time==0){
		for(i=0;i<2;i++){
			for(j=0;j<8;j++){
				rc_mot_pos[i][j]=rc_mot_ipos[i][j];
			}
		}		
	}
	//���x���䎞
	else{
		rc_step_num=time;	//�X�e�b�v�񐔃Z�b�g(1��=20ms)
		rc_step_flag=1;		//���x����J�n
	}
}

#endif

/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_dc.c                         */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :DCmotor PWM control Library Source */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_DC
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"
/* Global variables ----------------------------------------------------------*/
s8 	mot1_cw=0,mot2_cw=0;		//出力モード選択
u8	mot1_duty=0,mot2_duty=0;	//PWM出力 Duty比(%)

//==============================================================================
// DCモータPWM出力(TIM2割り込み)
//==============================================================================
void TIM2_DCmotor_pwm(){
	//CC1割り込み(2[kHz]=500[us])
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){		
	    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);//TIM2_CC1割り込みフラグクリア
	    //パルスの立ち上げ
	    if(mot1_duty!=0){
	    	switch(mot1_cw){
	    		case MODE_CW:		MOT1A_H;MOT1B_L;break;	//正転
	    		case MODE_CCW:		MOT1A_L;MOT1B_H;break;	//逆転
	    		case MODE_BRAKE:	MOT1A_L;MOT1B_L;break;	//ブレーキ
	    		case MODE_STOP:		MOT1A_H;MOT1B_H;break;	//ハイインピーダンス
	    	}
	    }
	    else{MOT1A_L;MOT1B_L;}
	    if(mot2_duty!=0){
	    	switch(mot2_cw){
	    		case MODE_CW:		MOT2A_H;MOT2B_L;break;	//正転
	    		case MODE_CCW:		MOT2A_L;MOT2B_H;break;	//逆転
	    		case MODE_BRAKE:	MOT2A_L;MOT2B_L;break;	//ブレーキ
	    		case MODE_STOP:		MOT2A_H;MOT2B_H;break;	//ハイインピーダンス
	    	}
	    }
	    else{MOT2A_L;MOT2B_L;}
	    TIM_SetCompare2(TIM2,mot1_duty);//CC2割り込みタイミングのセット(MOT1 Duty幅)	    	
	    TIM_SetCompare3(TIM2,mot2_duty);//CC3割り込みタイミングのセット(MOT2 Duty幅)
	}
	//CC2割り込み(5*mot1_duty[us])
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC2) != RESET){
	    TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);//TIM2_CC2割り込みフラグクリア
	    //パルスの立ち下げ
	    switch(mot1_cw){
	    	case MODE_CW:
	    	case MODE_CCW:
	    	case MODE_BRAKE:
	    	    if(mot1_duty<100){MOT1A_L;MOT1B_L;}break;
	    	case MODE_STOP:
	    		MOT1A_H;MOT1B_H;break;
	    }	    
	}
	//CC3割り込み(5*mot2_duty[us])
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET){
	    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);//TIM2_CC3割り込みフラグクリア
	    switch(mot2_cw){
	    	case MODE_CW:
	    	case MODE_CCW:
	    	case MODE_BRAKE:
	    	    if(mot2_duty<100){MOT2A_L;MOT2B_L;}break;
	    	case MODE_STOP:
	    		MOT2A_H;MOT2B_H;break;
	    }	    
	}
	//CC4割り込み
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET){
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);//TIM2_CC4割り込みフラグクリア
	}
}

//==============================================================================
// DCモータ初期化
//==============================================================================
void DC_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
	//DC_motor init
    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	MOT1A_L;MOT1B_L;MOT2A_L;MOT2B_L;
	
	/* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Enable the TIM2 Interrupt */
    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    TIM_DeInit(TIM2);
    /* Time base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 100;
    TIM_TimeBaseStructure.TIM_Prescaler = (240-1);
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* Immediate load of TIM2 Precaler value */
	TIM_PrescalerConfig(TIM2,(240-1), TIM_PSCReloadMode_Immediate);

    /* Output Compare Active Mode configuration: Channel1 */
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 100;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    //  /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

    /* Output Compare Active Mode configuration: Channel2 */
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = mot1_duty;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);

    /* Output Compare Active Mode configuration: Channel3 */
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = mot2_duty;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);

    /* Output Compare Active Mode configuration: Channel4 */
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 100;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    
    /* TIM IT enable */
    TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 , ENABLE);  
    /* TIM2 disable counter */
    TIM_Cmd(TIM2, DISABLE);
	/* Clear TIM2 update pending flag */
	TIM_ClearFlag(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4);
}

//==============================================================================
// DCモータ 出力許可
//==============================================================================
void DC_enable(){
	mot1_duty=0;
	mot2_duty=0;
	TIM_Cmd(TIM2, ENABLE);	
}

//==============================================================================
// DCモータ 出力禁止
//==============================================================================
void DC_disable(){
	mot1_duty=0;
	mot2_duty=0;
	TIM_Cmd(TIM2, DISABLE);
	MOT1A_L;MOT1B_L;MOT2A_L;MOT2B_L;
}

#endif

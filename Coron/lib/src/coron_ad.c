/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_ad.c                         */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron AD convert Library Source    */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_AD
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Private define ------------------------------------------------------------*/
#define IOA_ADC_SampleTime ADC_SampleTime_28Cycles5  //ADのサンプリングスピード

/* Global variables ----------------------------------------------------------*/
vu16 coron_IOA_ADValue[6]={0,0,0,0,0,0};			  //AD結果収納バッファ

//==============================================================================
// IOA0～5の指定されたポートをADポートとして設定
//==============================================================================
void IOA_AD_init(u8 port){
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
			
    /* Enable ADC1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    /* Enable DMA1 clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    //IOA0～5の内、指定されたポートをAINに設定する
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = port;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* Enable the DMA1 Channel 5 Interrupt */

    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    	
	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)coron_IOA_ADValue;		//ADCの結果を格納する配列のアドレス
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 6;								//6ポート分のバッファ
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);  
    /* DMA1 Channel1 enable */
    DMA_Cmd(DMA1_Channel1, ENABLE);
    /* Enable Channel1 Transfer complete interrupt */
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	    	
	/* ADC1 configuration ------------------------------------------------------*/
    ADC_DeInit(ADC1);
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;			//スキャンモード
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//連続モード
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 6;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC1 regular channels configuration */ 
	if(IOA_pin_0==(port&0x0001)){ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, IOA_ADC_SampleTime);}
	if(IOA_pin_1==(port&0x0002)){ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, IOA_ADC_SampleTime);}
	if(IOA_pin_2==(port&0x0004)){ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, IOA_ADC_SampleTime);}
	if(IOA_pin_3==(port&0x0008)){ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, IOA_ADC_SampleTime);}
	if(IOA_pin_4==(port&0x0010)){ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 5, IOA_ADC_SampleTime);}
	if(IOA_pin_5==(port&0x0020)){ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 6, IOA_ADC_SampleTime);}
	    
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);	
}

//==============================================================================
// AD入力許可(開始)
//==============================================================================
void AD_enable(void){
    /* DMA1 Channel1 enable */
    DMA_Cmd(DMA1_Channel1, ENABLE);
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//==============================================================================
// AD入力禁止(停止)
//==============================================================================
void AD_disable(void){
	/* Stop ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
    /* DMA1 Channel1 enable */
    DMA_Cmd(DMA1_Channel1, DISABLE);
}

#endif

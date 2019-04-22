/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_conf.h                       */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron Peripheral configuration     */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_CONF_H_
#define CORON_CONF_H_
/*
  ���g�p����@�\�ɍ��킹�Đݒ��ύX���邱��
  (�g�p���Ȃ��@�\��#define�`�s��//�ŃR�����g�A�E�g)
*/
/*************************************************/
/*               DfuSe�̎g�p                     */
/* ��DfuSe���g�p���Ȃ��ꍇ�̓R�����g�A�E�g       */
/*                                               */
/* �����̕��@�ŏ���(JTAG��)���s���ꍇ�́A        */
/*   ���̃R�����g�A�E�g�ɉ����āA                */
/*   [ld_script/coron_ld_sclipt.ld]��            */
/*   �t�@�C�����̎w���ɍ��킹�ĕҏW���Ă�������  */
/* (���̃G�f�B�^�[�Ƀh���b�O���h���b�v�ŕҏW�\)*/
/*************************************************/
#define _DFU_MODE

/*************************************************/
/*   A/D�|�[�g�Ƃ��Đݒ肷��IOA�|�[�g�̎w��      */
/*************************************************/
//�SIOA�|�[�gAD�|�[�g�Ƃ��Đݒ�
#define IOA_AD_SET_PORT  IOA_pin_0|IOA_pin_1|IOA_pin_2|IOA_pin_3|IOA_pin_4|IOA_pin_5

/*-Example-
 //IOA1,IOA3,IOA5��AD�|�[�g�Ƃ��Đݒ肷��ꍇ
 #define IOA_AD_SET_PORT  IOA_pin_1|IOA_pin_3|IOA_pin_5	
*/

/*************************************************/
/*         Coron�Ŏg�p����@�\���w��             */
/*   (���g�p���Ȃ��@�\�̓R�����g�A�E�g����)      */
/*************************************************/
#define _CORON_AD			//IOA�A�i���O����
#define _CORON_DC			//DC���[�^�o��
#define _CORON_RC			//RC�T�[�{�o��
#define _CORON_SD			//SD�J�[�h���o��
#define _CORON_SOUND		//�X�s�[�J�o��(��_CORON_SD���g�p)
#define _CORON_SDTXT		//SD�J�[�hTXT�t�@�C�����o��(��_CORON_SD���g�p)
#define _CORON_USBCDC		//USB ���zCOM�|�[�g
#define _CORON_UART		//UART���o��(CN-UART&XBee)
//��_CORON_UART�g�p���ɂ�LD2&LD3��UART�ʐM���j�^�p�ɂȂ�܂�

/*************************************************/
/*                UART�ʐM�ݒ�                   */
/*************************************************/
/* �{�[���[�g */
#define UART_BAUDRATE 9600 

/* �f�[�^�� */
#define UART_LENGTH   USART_WordLength_8b	  //8Bit
//#define UART_LENGTH   USART_WordLength_9b   //9Bit

/* �X�g�b�v�r�b�g */
#define UART_STOP     USART_StopBits_1 	  //  1Bit
//#define UART_STOP     USART_StopBits_0_5 	  //0.5Bit
//#define UART_STOP     USART_StopBits_2 	  //  2Bit
//#define UART_STOP     USART_StopBits_1_5 	  //1.5Bit

/* �p���e�B */
#define UART_PARITY   USART_Parity_No	  	  //����
//#define UART_PARITY   USART_Parity_Even	  //�
//#define UART_PARITY   USART_Parity_Odd	  //����

/* �t���[����(�������Œ�) */
#define UART_Flow      USART_HardwareFlowControl_None

/*************************************************/
/*     Coron�Ŏg�p���邻�̑��̋@�\���w��         */
/*   (���g�p���Ȃ��@�\�̓R�����g�A�E�g����)      */
/*************************************************/
//<A/D�R���o�[�^>
//#define _ADC
//#define _ADC1				//IOA�A�i���O���͂Ŏg�p
//#define _ADC2
//#define _ADC3

//<D/A�R���o�[�^>
//#define _DAC				//�X�s�[�J�o�͂Ŏg�p

//<DMA>
//#define _DMA				
//#define _DMA1_Channel1
//#define _DMA1_Channel2	//IOA�A�i���O���͂Ŏg�p
//#define _DMA1_Channel3
//#define _DMA1_Channel4
//#define _DMA1_Channel5
//#define _DMA1_Channel6
//#define _DMA1_Channel7
//#define _DMA2_Channel1
//#define _DMA2_Channel2
//#define _DMA2_Channel3
//#define _DMA2_Channel4	//SD�J�[�h���o�͂Ŏg�p
//#define _DMA2_Channel5

//<�O�����荞��>
//#define _EXTI

//<I2C�ʐM>
//#define _I2C
//#define _I2C2				//CN-IO(PB10->I2C2_SCL PB11->I2C2_SDA PB12->I2C2_SMBAL)�ɐڑ�

//<�d���Ǘ�>
//#define _PWR

//<SPI�ʐM>
//#define _SPI
//#define _SPI2				//CN-IO(PB12->SPI2_NSS PB13->SPI2_SCK PB14->SPI2_MISO PB15->SPI2_MOSI)�ɐڑ�

//<�^�C�}�[>
//#define _TIM
//#define _TIM1
//#define _TIM2				//DC���[�^�o�͂Ŏg�p
//#define _TIM3				//RC�T�[�{�o�͂Ŏg�p
//#define _TIM4				//RC�T�[�{�o�͂Ŏg�p
//#define _TIM5				//�X�s�[�J�o�͂Ŏg�p
//#define _TIM6				//RC�T�[�{�o�͂Ŏg�p
//#define _TIM7
//#define _TIM8

//<�V���A���ʐM>
//#define _USART
//#define _USART2			//CN-UART(or XBee)�ɐڑ�
//#define _USART3			//CN-IO(PB10->TX3 PB11->RX3)�ɐڑ�

/*************************************************/
/*             (���ȉ��A�ύX�s��)                */
/*************************************************/
/****************************/
#ifdef _CORON_AD
  #define _ADC
  #define _ADC1
  #define _DMA
  #define _DMA1_Channel1
#endif
/****************************/
/****************************/
#ifdef _CORON_RC
  #define _TIM
  #define _TIM3
  #define _TIM4
  #define _TIM6
#endif
/****************************/
/****************************/
#ifdef _CORON_DC
  #define _TIM
  #define _TIM2
#endif
/****************************/
/****************************/
#ifdef _CORON_SD
  #define _SDIO
  #define _DMA
  #define _DMA2_Channel4
#ifdef _CORON_SOUND
  #define _DAC
  #define _TIM
  #define _TIM5
#endif
#endif
/****************************/
/****************************/
#ifdef _CORON_UART
  #define _USART
  #define _USART2
#endif
/****************************/

#endif /*CORON_CONF_H_*/

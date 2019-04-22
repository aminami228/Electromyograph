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
  ※使用する機能に合わせて設定を変更すること
  (使用しない機能の#define～行を//でコメントアウト)
*/
/*************************************************/
/*               DfuSeの使用                     */
/* ※DfuSeを使用しない場合はコメントアウト       */
/*                                               */
/* ※他の方法で書込(JTAG等)を行う場合は、        */
/*   このコメントアウトに加えて、                */
/*   [ld_script/coron_ld_sclipt.ld]を            */
/*   ファイル内の指示に合わせて編集してください  */
/* (このエディターにドラッグ＆ドロップで編集可能)*/
/*************************************************/
#define _DFU_MODE

/*************************************************/
/*   A/Dポートとして設定するIOAポートの指定      */
/*************************************************/
//全IOAポートADポートとして設定
#define IOA_AD_SET_PORT  IOA_pin_0|IOA_pin_1|IOA_pin_2|IOA_pin_3|IOA_pin_4|IOA_pin_5

/*-Example-
 //IOA1,IOA3,IOA5をADポートとして設定する場合
 #define IOA_AD_SET_PORT  IOA_pin_1|IOA_pin_3|IOA_pin_5	
*/

/*************************************************/
/*         Coronで使用する機能を指定             */
/*   (※使用しない機能はコメントアウトする)      */
/*************************************************/
#define _CORON_AD			//IOAアナログ入力
#define _CORON_DC			//DCモータ出力
#define _CORON_RC			//RCサーボ出力
#define _CORON_SD			//SDカード入出力
#define _CORON_SOUND		//スピーカ出力(※_CORON_SDを使用)
#define _CORON_SDTXT		//SDカードTXTファイル入出力(※_CORON_SDを使用)
#define _CORON_USBCDC		//USB 仮想COMポート
#define _CORON_UART		//UART入出力(CN-UART&XBee)
//※_CORON_UART使用時にはLD2&LD3はUART通信モニタ用になります

/*************************************************/
/*                UART通信設定                   */
/*************************************************/
/* ボーレート */
#define UART_BAUDRATE 9600 

/* データ長 */
#define UART_LENGTH   USART_WordLength_8b	  //8Bit
//#define UART_LENGTH   USART_WordLength_9b   //9Bit

/* ストップビット */
#define UART_STOP     USART_StopBits_1 	  //  1Bit
//#define UART_STOP     USART_StopBits_0_5 	  //0.5Bit
//#define UART_STOP     USART_StopBits_2 	  //  2Bit
//#define UART_STOP     USART_StopBits_1_5 	  //1.5Bit

/* パリティ */
#define UART_PARITY   USART_Parity_No	  	  //無し
//#define UART_PARITY   USART_Parity_Even	  //奇数
//#define UART_PARITY   USART_Parity_Odd	  //偶数

/* フロー制御(※無し固定) */
#define UART_Flow      USART_HardwareFlowControl_None

/*************************************************/
/*     Coronで使用するその他の機能を指定         */
/*   (※使用しない機能はコメントアウトする)      */
/*************************************************/
//<A/Dコンバータ>
//#define _ADC
//#define _ADC1				//IOAアナログ入力で使用
//#define _ADC2
//#define _ADC3

//<D/Aコンバータ>
//#define _DAC				//スピーカ出力で使用

//<DMA>
//#define _DMA				
//#define _DMA1_Channel1
//#define _DMA1_Channel2	//IOAアナログ入力で使用
//#define _DMA1_Channel3
//#define _DMA1_Channel4
//#define _DMA1_Channel5
//#define _DMA1_Channel6
//#define _DMA1_Channel7
//#define _DMA2_Channel1
//#define _DMA2_Channel2
//#define _DMA2_Channel3
//#define _DMA2_Channel4	//SDカード入出力で使用
//#define _DMA2_Channel5

//<外部割り込み>
//#define _EXTI

//<I2C通信>
//#define _I2C
//#define _I2C2				//CN-IO(PB10->I2C2_SCL PB11->I2C2_SDA PB12->I2C2_SMBAL)に接続

//<電源管理>
//#define _PWR

//<SPI通信>
//#define _SPI
//#define _SPI2				//CN-IO(PB12->SPI2_NSS PB13->SPI2_SCK PB14->SPI2_MISO PB15->SPI2_MOSI)に接続

//<タイマー>
//#define _TIM
//#define _TIM1
//#define _TIM2				//DCモータ出力で使用
//#define _TIM3				//RCサーボ出力で使用
//#define _TIM4				//RCサーボ出力で使用
//#define _TIM5				//スピーカ出力で使用
//#define _TIM6				//RCサーボ出力で使用
//#define _TIM7
//#define _TIM8

//<シリアル通信>
//#define _USART
//#define _USART2			//CN-UART(or XBee)に接続
//#define _USART3			//CN-IO(PB10->TX3 PB11->RX3)に接続

/*************************************************/
/*             (※以下、変更不可)                */
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

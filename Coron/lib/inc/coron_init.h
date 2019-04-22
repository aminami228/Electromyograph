/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_init.h                       */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron initialize Library Header    */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
/* Includes ------------------------------------------------------------------*/
#ifndef CORON_INIT_H_
#define CORON_INIT_H_

/* Define ------------------------------------------------------------*/
#define SW_USER	!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)

#define LD1_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define LD1_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define LD2_OFF	GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define LD2_ON		GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define LD3_OFF	GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define LD3_ON		GPIO_ResetBits(GPIOA, GPIO_Pin_3)
	
#define IOA_pin_0	GPIO_Pin_0
#define IOA_pin_1	GPIO_Pin_1
#define IOA_pin_2	GPIO_Pin_2
#define IOA_pin_3	GPIO_Pin_3
#define IOA_pin_4	GPIO_Pin_4
#define IOA_pin_5	GPIO_Pin_5
#define GPIO_IOA	GPIOC

#define SW_SDIO_CD	!GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)

/* Extern ------------------------------------------------------------*/
extern void coron_init();

#endif /*CORON_INIT_H_*/

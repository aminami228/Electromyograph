/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_ad.h                         */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron AD convert Library Header    */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_AD_H_
#define CORON_AD_H_

/* Define ------------------------------------------------------------*/
#define ADC1_DR_Address    ((u32)0x4001244C)
#define IOA_pin_0		GPIO_Pin_0
#define IOA_pin_1		GPIO_Pin_1
#define IOA_pin_2		GPIO_Pin_2
#define IOA_pin_3		GPIO_Pin_3
#define IOA_pin_4		GPIO_Pin_4
#define IOA_pin_5		GPIO_Pin_5
#define IOA_pin_NONE	0
#define GPIO_IOA		GPIOC

/* Extern ------------------------------------------------------------*/
extern vu16 coron_IOA_ADValue[6];
extern void IOA_AD_init(u8 port);	
extern void AD_enable(void);		// AD“ü—Í‹–‰Â(ŠJŽn)
extern void AD_disable(void);	// AD“ü—Í‹ÖŽ~(’âŽ~)

#endif /*CORON_AD_H_*/

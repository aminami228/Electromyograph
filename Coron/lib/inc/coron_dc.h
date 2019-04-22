/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_rc.h                         */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :DCmotor PWM control Library Header */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_DC_H_
#define CORON_DC_H_

/* Define ------------------------------------------------------------*/
#define MOT1A_H	GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define MOT1A_L	GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define MOT1B_H	GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define MOT1B_L	GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define MOT2A_H	GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define MOT2A_L	GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define MOT2B_H	GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define MOT2B_L	GPIO_ResetBits(GPIOB, GPIO_Pin_9)

#define MODE_CW 	1	//正転
#define MODE_CCW 	-1	//逆転
#define MODE_BRAKE 0	//ブレーキ
#define MODE_STOP 	2	//停止

/* Extern ------------------------------------------------------------*/
extern s8 	mot1_cw,mot2_cw;		//出力モード選択
extern u8	mot1_duty,mot2_duty;	//PWM出力 Duty比(x10%)
extern void DC_init();
extern void TIM2_DCmotor_pwm();
extern void DC_enable();
extern void DC_disable();

#endif /*CORON_DC_H_*/

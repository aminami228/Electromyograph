/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_rc.h                         */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :RCservo Library Header             */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_RC_H_
#define CORON_RC_H_

/* Define ------------------------------------------------------------*/
#define RC1 0
#define RC2 1

#define RC1_A0_H	GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define RC1_A0_L	GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define RC1_A1_H	GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define RC1_A1_L	GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define RC1_A2_H	GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define RC1_A2_L	GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define RC1_PWM_H	GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define RC1_PWM_L	GPIO_ResetBits(GPIOA, GPIO_Pin_8)

#define RC2_A0_H	GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define RC2_A0_L	GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define RC2_A1_H	GPIO_SetBits(GPIOC, GPIO_Pin_14)
#define RC2_A1_L	GPIO_ResetBits(GPIOC, GPIO_Pin_14)
#define RC2_A2_H	GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define RC2_A2_L	GPIO_ResetBits(GPIOC, GPIO_Pin_15)
#define RC2_PWM_H	GPIO_SetBits(GPIOC, GPIO_Pin_6)
#define RC2_PWM_L	GPIO_ResetBits(GPIOC, GPIO_Pin_6)

/* Extern ------------------------------------------------------------*/
extern u16 rc_mot_ipos[2][8];			//角度目標値
extern u8 	rc_mot_ch[2];				//
extern u8  rc_step_flag;				//速度制御フラグ
extern s16 rc_mot_pos_step[2][8];		//速度制御ステップ角
extern u8 	rc_step_num;				//
extern u8 	rc_step_count;			//

extern u16 rc_mot_pos[2][8];
extern u16 rc_mot_pos_home[2][8];
extern s16 rc_mot_pos_trim[2][8];
extern u16 rc_mot_motion_pos[100][2][8];
extern u8 rc_mot_motion_spd[100];

extern void TIM3_RC1_IRQ();
extern void TIM4_RC2_IRQ();
extern void TIM6_RC_Speed();

extern void RC_exeHomePosition();
extern void RC_init();
extern void RC_enable();
extern void RC_disable();
extern void RC_move(u8 time);

#endif /*CORON_RC_H_*/

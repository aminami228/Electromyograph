/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_wait.c                       */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Wait routine Library Source        */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Global variables ----------------------------------------------------------*/
u8 	wait_timer_flag=0;
u32 wait_timer_count=0;

/* Prototype -----------------------------------------------------------------*/
void wait_loop(vu32 loop){while(loop--);}

//==============================================================================
// Wait�������֐�
//==============================================================================
void wait_init(void){
    //SysTick������(wait�����p)
	SysTick_Configuration();
}

//==============================================================================
// Wait�֐�(SysTick���荞��)
//==============================================================================
void Handler_SysTick(void){
	if(wait_timer_count==0){
		wait_timer_flag=0;		//�����ݑ҂��t���O���N���A		
	}
	else{
		wait_timer_count--;		//�c�芄���݉񐔂��|1
	}
}

//==============================================================================
// SysTick ������
//==============================================================================
void SysTick_Configuration(void){
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//SysTick�̃N���b�N�\�[�X��HCLK/8(9MHz)�ɃZ�b�g
  SysTick_SetReload(900);								//�����[�h����J�E���^�l��ݒ�(100[us])
  SysTick_CounterCmd(SysTick_Counter_Disable);			//SysTick�J�E���^���֎~
  SysTick_ITConfig(ENABLE);								//SysTick���荞�݂�����
}

//==============================================================================
// SysTick Handler���g����wait�֐�(���� x100us)
//==============================================================================
void wait_timer(u32 time_x100us){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTick�J�E���^���֎~
	SysTick_SetReload(900);								//�����[�h����J�E���^�l��ݒ�(100[us])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTick�J�E���^���N���A
	wait_timer_count= time_x100us-1;					//�J�E���^�l��ݒ�
	wait_timer_flag	= 1;								//�����ݑ҂��t���O���Z�b�g		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTick�J�E���^���J�n
	while(wait_timer_flag);								//SysTick���荞�݂�����̂�҂�
}

//==============================================================================
// SysTick Handler���g����wait�֐� �P��[sec]
//==============================================================================
void wait_timer_sec(u32 time_sec){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTick�J�E���^���֎~
	SysTick_SetReload(9000000);							//�����[�h����J�E���^�l��ݒ�(1[msec])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTick�J�E���^���N���A
	wait_timer_count= time_sec-1;						//�J�E���^�l��ݒ�
	wait_timer_flag	= 1;								//�����ݑ҂��t���O���Z�b�g		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTick�J�E���^���J�n
	while(wait_timer_flag);								//SysTick���荞�݂�����̂�҂�
}

//==============================================================================
// SysTick Handler���g����wait�֐� �P��[msec]
//==============================================================================
void wait_timer_msec(u32 time_msec){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTick�J�E���^���֎~
	SysTick_SetReload(9000);							//�����[�h����J�E���^�l��ݒ�(1[msec])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTick�J�E���^���N���A
	wait_timer_count= time_msec-1;						//�J�E���^�l��ݒ�
	wait_timer_flag	= 1;								//�����ݑ҂��t���O���Z�b�g		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTick�J�E���^���J�n
	while(wait_timer_flag);								//SysTick���荞�݂�����̂�҂�
}

//==============================================================================
// SysTick Handler���g����wait�֐� �P��[usec]
//==============================================================================
void wait_timer_usec(u32 time_usec){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTick�J�E���^���֎~
	SysTick_SetReload(9);								//�����[�h����J�E���^�l��ݒ�(1[usec])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTick�J�E���^���N���A
	wait_timer_count= time_usec-1;						//�J�E���^�l��ݒ�
	wait_timer_flag	= 1;								//�����ݑ҂��t���O���Z�b�g		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTick�J�E���^���J�n
	while(wait_timer_flag);								//SysTick���荞�݂�����̂�҂�
}
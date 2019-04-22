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
// Wait初期化関数
//==============================================================================
void wait_init(void){
    //SysTick初期化(wait処理用)
	SysTick_Configuration();
}

//==============================================================================
// Wait関数(SysTick割り込み)
//==============================================================================
void Handler_SysTick(void){
	if(wait_timer_count==0){
		wait_timer_flag=0;		//割込み待ちフラグをクリア		
	}
	else{
		wait_timer_count--;		//残り割込み回数を－1
	}
}

//==============================================================================
// SysTick 初期化
//==============================================================================
void SysTick_Configuration(void){
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//SysTickのクロックソースをHCLK/8(9MHz)にセット
  SysTick_SetReload(900);								//リロードするカウンタ値を設定(100[us])
  SysTick_CounterCmd(SysTick_Counter_Disable);			//SysTickカウンタを禁止
  SysTick_ITConfig(ENABLE);								//SysTick割り込みを許可
}

//==============================================================================
// SysTick Handlerを使ったwait関数(引数 x100us)
//==============================================================================
void wait_timer(u32 time_x100us){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTickカウンタを禁止
	SysTick_SetReload(900);								//リロードするカウンタ値を設定(100[us])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTickカウンタをクリア
	wait_timer_count= time_x100us-1;					//カウンタ値を設定
	wait_timer_flag	= 1;								//割込み待ちフラグをセット		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTickカウンタを開始
	while(wait_timer_flag);								//SysTick割り込みが入るのを待つ
}

//==============================================================================
// SysTick Handlerを使ったwait関数 単位[sec]
//==============================================================================
void wait_timer_sec(u32 time_sec){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTickカウンタを禁止
	SysTick_SetReload(9000000);							//リロードするカウンタ値を設定(1[msec])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTickカウンタをクリア
	wait_timer_count= time_sec-1;						//カウンタ値を設定
	wait_timer_flag	= 1;								//割込み待ちフラグをセット		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTickカウンタを開始
	while(wait_timer_flag);								//SysTick割り込みが入るのを待つ
}

//==============================================================================
// SysTick Handlerを使ったwait関数 単位[msec]
//==============================================================================
void wait_timer_msec(u32 time_msec){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTickカウンタを禁止
	SysTick_SetReload(9000);							//リロードするカウンタ値を設定(1[msec])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTickカウンタをクリア
	wait_timer_count= time_msec-1;						//カウンタ値を設定
	wait_timer_flag	= 1;								//割込み待ちフラグをセット		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTickカウンタを開始
	while(wait_timer_flag);								//SysTick割り込みが入るのを待つ
}

//==============================================================================
// SysTick Handlerを使ったwait関数 単位[usec]
//==============================================================================
void wait_timer_usec(u32 time_usec){
	SysTick_CounterCmd(SysTick_Counter_Disable);		//SysTickカウンタを禁止
	SysTick_SetReload(9);								//リロードするカウンタ値を設定(1[usec])
	SysTick_CounterCmd(SysTick_Counter_Clear);			//SysTickカウンタをクリア
	wait_timer_count= time_usec-1;						//カウンタ値を設定
	wait_timer_flag	= 1;								//割込み待ちフラグをセット		
	SysTick_CounterCmd(SysTick_Counter_Enable);			//SysTickカウンタを開始
	while(wait_timer_flag);								//SysTick割り込みが入るのを待つ
}
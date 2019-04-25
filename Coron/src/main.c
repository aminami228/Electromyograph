
// This is for System Engineering Lab Tutorial 2019


/*********************---< TECHNO ROAD.inc >---*********************/
/*                                                                 */
/*                    [Coron sample programs]                      */
/*                            Ex_ALL                               */
/*                                                                 */
/*        File        :main.c                                      */
/*        Version     :v2.1.0                                      */
/*        Date        :2010/05/18                                  */
/*        Author      :Norio Sakagami                              */
/*        Description :Main protocol                               */
/*                                                                 */
/*            Copyright(C) TECHNOROAD.inc                          */
/*                          http://techno-road.com/                */
/*******************************************************************/
/*-------------------------------------------------------------------
  このサンプルプログラム(プロジェクト)は，Coron専用ライブラリを全て
  include及び初期化しています．
  自作でプログラミングする際の土台としてご利用ください．
  また，機能の設定は[inc]フォルダ内の[coron_conf.h]を編集してください．
    ※_CORON_UART使用時はLD2&LD3はUART通信モニタ用になります
-------------------------------------------------------------------*/

//===================================================================
// Includes
//===================================================================
#include "stm32f10x_lib.h"	//STマイクロライブラリ
#include "coron_lib.h"		//Coron専用ライブラリ
#include <stdlib.h>			// to use abs() function

//===================================================================
// main関数
//===================================================================

int main(void){
	coron_init();				//Coron初期化(※機能はcoron_conf.hで指定)
	int i;
						
	// LED
	wait_timer_msec(500);	//500msec待機
   	LD1_ON;					//LD1を点灯
   	wait_timer_msec(500);	//500msec待機
   	LD1_OFF;				//LD1を消灯
   	LD2_ON;					//LD2を点灯
   	wait_timer_msec(500);	//500msec待機
   	LD2_OFF;				//LD2を消灯
   	LD3_ON;					//LD3を点灯
   	wait_timer_msec(500);	//500msec待機
   	LD3_OFF;				//LD3を消灯
   	LD1_ON;
   	LD2_ON;
   	LD3_ON;
   	
   	// starts when SW is pressed
   	while (!SW_USER);		// wait for SW being pushed
   	wait_timer_msec(500);	// wait for 500msec
   	
   	// prints message on PC using USB
   	USB_puts("\r\n\n**** EMG_AD_GET ****\r\n\n");
   	
	wait_timer_msec(500);	//500msec待機
   	LD1_OFF;				//LD1を消灯
   	LD2_OFF;				//LD2を消灯
   	LD3_OFF;				//LD3を消灯
   	wait_timer_msec(1000);
   	LD1_ON;
   	LD2_ON;
   	LD3_ON;
   	wait_timer_msec(1000);

   	// lets AD converter input
   	AD_enable();
   	
   	// control RC servo at RC1-0, RC1-1
   	rc_mot_pos[RC1][0] = 1500;				// set central angle to 0[deg] = 1500[us]
   	rc_mot_pos_trim[RC1][0] = 0;			// calibration 0[us]
   	rc_mot_pos[RC1][1] = 1500;				// set central angle to 0[deg] = 1500[us]
   	rc_mot_pos_trim[RC1][1] = 0;			// calibration 0[us]
   	
   	RC_enable();							// approve of PMW signal output (initial output PWM->1500us)
   	wait_timer_msec(500);
   	
   	// NOW LET'S START SERVO WITH MYOELECTRICITY
   	
   	// check if AD conversion is working
   	// print AD value at IOA0
   	for (i=1;i<10000;i++){								// infinite loop
   		int x,y;
   		LD1_ON;
   		USB_puts("\r\n   IOA0_AD = ");		// send message to ptrint it on PC
   		USB_putn(coron_IOA_ADValue[0],4);	// print AD value of IOA0 (12bits)
   		
   		y = coron_IOA_ADValue[0];
   		USB_puts("   substitution_OK");
   		x = abs(y - 2047);
   		USB_puts("   RMS_cal_OK");
   		USB_puts("   RMS = ");
   		USB_putn(x,4);
   		USB_puts("   \r");
   		
   		/*
   		if (x > 500){
   			rc_mot_pos[RC1][0] = 2300;		// +90[deg]
   			wait_timer_msec(500);
   		} else {
   			rc_mot_pos[RC1][0] = 1900;		// +45[deg]
   			wait_timer_msec(500);
   		}
   		
   		
   		LD1_OFF;
   		wait_timer_msec(10);
   		
   		*/
   		
   	}
   	
   	USB_puts("\r\n\n\n   *** DONE ***");
   	LD1_OFF;
   	
	return 0;
}


/* main method example
int main(void){
	coron_init();				//Coron初期化(※機能はcoron_conf.hで指定)
						
	//User Programs
	while(1){
	   	wait_timer_msec(500);	//500msec待機
   	   	LD1_ON;					//LD1を点灯
   	   	wait_timer_msec(500);	//500msec待機
   	    LD1_OFF;				//LD1を消灯
   	}
	return 0;
}
*/


/**********************************************************************/
/* <アナログ入力(& USB_CDC)の使い方例>                                */
/**********************************************************************/
/*
int main(void){
	//アナログ入力ポートとして設定されるIOAはcoron_conf.hで指定
	coron_init();
				       	
    AD_enable();		//アナログ入力の許可(開始)
    
   	//無限ループ
   	while(1){
		LD1_ON;								//LD1を点灯
		USB_puts("  IOA0_AD =");			//文字列送信		
	    USB_putn(coron_IOA_ADValue[0],4);	//IOA0のAD値(12bit)を表示
		USB_puts("  IOA1_AD =");			//文字列送信		
	    USB_putn(coron_IOA_ADValue[1],4);	//IOA1のAD値(12bit)を表示
		USB_puts("  IOA2_AD =");			//文字列送信		
	    USB_putn(coron_IOA_ADValue[2],4);	//IOA2のAD値(12bit)を表示
       	USB_puts("  \r");					//カーソルを先頭に戻す
		LD1_OFF;							//LD2を消灯
		wait_timer(100);					//0.1sec待機   		
   	}
}
*/
/**********************************************************************/
	

/**********************************************************************/
/* <DCモータの使い方例>                                               */
/**********************************************************************/
/*
int main(void){
	int i;	
	
	coron_init();		//Coron初期化(※機能はcoron_conf.hで指定)
				       	
   	//無限ループ
   	while(1){
   		if(SW_USER==1){	//SW_USERが押されたら…(押す=1)
   			LD1_ON;		//	LD1を点灯
   			mot1_cw=MODE_CW;		//MOT1の回転モードをセット(正転)
			mot2_cw=MODE_CCW;		//MOT2の回転モードをセット(逆転)
			DC_enable();			//DCモータ制御用PWM出力許可

			for(i=0;i<101;i++){		//MOT1->徐々に加速  MOT2->徐々に減速
				mot1_duty=i;		//	MOT1のDuty比を設定(%)
				mot2_duty=(100-i);	//	MOT2のDuty比を設定(%)
				wait_timer(100);
			}
			for(i=0;i<101;i++){		//MOT1->徐々に減速  MOT2->徐々に加速
				mot1_duty=(100-i);	//	MOT1のDuty比を設定(%)
				mot2_duty=i;		//	MOT2のDuty比を設定(%)
				wait_timer(100);
			}
			LD1_OFF;
			DC_disable();			//DCモータ制御用PWM出力禁止
   		}
   		else{			//SW_USERが押されていなかったら…(押さない=0)
   			LD1_OFF;	//	LD2を消灯
   		}	   		
   	}
}
*/
/**********************************************************************/

 
/**********************************************************************/
/* <RCサーボの使い方例>                                               */
/**********************************************************************/
/*
int main(void){
	coron_init();		//Coron初期化(※機能はcoron_conf.hで指定)
				        
   	//RC1-0に接続さているRCサーボを動かす
   	rc_mot_pos[RC1][0]		=1500;	//初期出力値1500[us]
   	rc_mot_pos_trim[RC1][0]	=	0;	//トリム(誤差修正) 0[us]
    RC_enable();					//PWM信号の出力許可(初期出力 PWM->1500us)
   	
   	//無限ループ
   	while(1){
   		if(SW_USER==1){	//SW_USERが押されたら…(押す=1)
   			LD1_ON;		//LD1を点灯
   			//時間制御有りで動かす
   			rc_mot_ipos[RC1][0]=1000;	//RC1-0に1000us幅のPWMを出力する
   		    RC_move(100);				// 20msec x (100) = 2sec
   		    while(rc_step_flag);		//動作終了まで待つ
   		    
   			rc_mot_ipos[RC1][0]=2000;	//RC1-0に2000us幅のPWMを出力する
   		    RC_move(200);				// 20msec x (200) = 4sec
   		    while(rc_step_flag);		//動作終了まで待つ
   		}
   		
   		else{			//SW_USERが押されていなかったら…(押さない=0)
   			LD1_OFF;	//LD1を消灯
   			//時間制御無しで動かす
   			rc_mot_pos[RC1][0]=1300;	//RC1-0に1300us幅のPWMを出力する
   			wait_timer(5000);			//0.5sec待機
   			rc_mot_pos[RC1][0]=1700;	//RC1-0に1700us幅のPWMを出力する
   			wait_timer(5000);			//0.5sec待機
   		}	
   	}
 	return 0;
}
*/
/**********************************************************************/


/**********************************************************************/
/* <SDカード(WAVファイル再生)の使い方例>                              */
/**********************************************************************/
/*
int main(void){
	int i,n=0;
	coron_init();			//Coron初期化(※機能はcoron_conf.hで指定)

	while(!SW_USER);		//SW_USERが押されるまで待機

	//SDカード "SoundData"ファルダ内WAVファイル名を表示
	//	wav_count      :フォルダ内のWAVファイル数
	//	wav_name[50][8]:フォルダ内のWAVファイル名
	USB_puts("SD WAV_File List...\r\n");
	for(i=0;i<wav_count;i++){
		USB_putd(&wav_name[i][0],8);
		USB_puts("\r\n");
	}		       

   	//無限ループ
   	while(1){
  		if(SW_USER==1){		//SW_USERが押されたら…(押す=1)
   			LD1_ON;			//	LD1を点灯
   			SD_play_wav(n);	//	n番目のWAVファイルを再生する
   			n++;			//  nを一つ加算
   			if(n==wav_count){n=0;}
   		}
   		else{				//SW_USERが押されていなかったら…(押さない=0)
   			LD1_OFF;		//	LD2を消灯
   		}
   	}
 	return 0;
}
*/
/**********************************************************************/


/**********************************************************************/
/* <UART送受信の使い方例>                                             */
/**********************************************************************/
/*
int main(void){
	char buf=0;
	coron_init();			//Coron初期化
							//ボーレートなどの設定はcoron_conf.hで指定
   	//無限ループ
   	while(1){
   		buf=UART_getc(1);	//１文字受信(0:受信待ち無し 1:受信待ち有り)
   		UART_putc(buf);		//１文字送信
   	}
 	return 0;
}
*/
/**********************************************************************/


/**********************************************************************/
/* <SD TXTファイルRead&Writeの使い方例>                                     */
/**********************************************************************/
/*
int main(void){
	int n=0;
	coron_init();					//Coron初期化

   	//無限ループ
   	while(1){
   		if(SW_USER==1){				//SW_USERが押されたら…(押す=1)
   			LD1_ON;					//LD1を点灯
   			SD_txt_write_c(n,0,'A');//n番目のTXTファイルの０文字目に'A'を書込む
			SD_txt_USBput(n,1);		//USB CDCで"TextData"フォルダ内のTXTファイルを表示する
									//(0番目のTXTファイル、ヘッダ表示有り(=1))
			SD_txt_UARTput(n,1);	//UART(XBee)で"TextData"フォルダ内のTXTファイルを表示する
   			n++;					//nを一つ加算
   			if(n==txt_count){n=0;}
   		}
   		else{						//SW_USERが押されていなかったら…(押さない=0)
   			LD1_OFF;				//	LD2を消灯
   		}
   	}
 	return 0;
}
*/
/**********************************************************************/

//===================================================================
// End of Program
//===================================================================


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
  ���̃T���v���v���O����(�v���W�F�N�g)�́CCoron��p���C�u������S��
  include�y�я��������Ă��܂��D
  ����Ńv���O���~���O����ۂ̓y��Ƃ��Ă����p���������D
  �܂��C�@�\�̐ݒ��[inc]�t�H���_����[coron_conf.h]��ҏW���Ă��������D
    ��_CORON_UART�g�p����LD2&LD3��UART�ʐM���j�^�p�ɂȂ�܂�
-------------------------------------------------------------------*/

//===================================================================
// Includes
//===================================================================
#include "stm32f10x_lib.h"	//ST�}�C�N�����C�u����
#include "coron_lib.h"		//Coron��p���C�u����
#include <stdlib.h>			// to use abs() function

//===================================================================
// main�֐�
//===================================================================

int main(void){
	coron_init();				//Coron������(���@�\��coron_conf.h�Ŏw��)
	int i;
						
	// LED
	wait_timer_msec(500);	//500msec�ҋ@
   	LD1_ON;					//LD1��_��
   	wait_timer_msec(500);	//500msec�ҋ@
   	LD1_OFF;				//LD1������
   	LD2_ON;					//LD2��_��
   	wait_timer_msec(500);	//500msec�ҋ@
   	LD2_OFF;				//LD2������
   	LD3_ON;					//LD3��_��
   	wait_timer_msec(500);	//500msec�ҋ@
   	LD3_OFF;				//LD3������
   	LD1_ON;
   	LD2_ON;
   	LD3_ON;
   	
   	// starts when SW is pressed
   	while (!SW_USER);		// wait for SW being pushed
   	wait_timer_msec(500);	// wait for 500msec
   	
   	// prints message on PC using USB
   	USB_puts("\r\n\n**** EMG_AD_GET ****\r\n\n");
   	
	wait_timer_msec(500);	//500msec�ҋ@
   	LD1_OFF;				//LD1������
   	LD2_OFF;				//LD2������
   	LD3_OFF;				//LD3������
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
	coron_init();				//Coron������(���@�\��coron_conf.h�Ŏw��)
						
	//User Programs
	while(1){
	   	wait_timer_msec(500);	//500msec�ҋ@
   	   	LD1_ON;					//LD1��_��
   	   	wait_timer_msec(500);	//500msec�ҋ@
   	    LD1_OFF;				//LD1������
   	}
	return 0;
}
*/


/**********************************************************************/
/* <�A�i���O����(& USB_CDC)�̎g������>                                */
/**********************************************************************/
/*
int main(void){
	//�A�i���O���̓|�[�g�Ƃ��Đݒ肳���IOA��coron_conf.h�Ŏw��
	coron_init();
				       	
    AD_enable();		//�A�i���O���͂̋���(�J�n)
    
   	//�������[�v
   	while(1){
		LD1_ON;								//LD1��_��
		USB_puts("  IOA0_AD =");			//�����񑗐M		
	    USB_putn(coron_IOA_ADValue[0],4);	//IOA0��AD�l(12bit)��\��
		USB_puts("  IOA1_AD =");			//�����񑗐M		
	    USB_putn(coron_IOA_ADValue[1],4);	//IOA1��AD�l(12bit)��\��
		USB_puts("  IOA2_AD =");			//�����񑗐M		
	    USB_putn(coron_IOA_ADValue[2],4);	//IOA2��AD�l(12bit)��\��
       	USB_puts("  \r");					//�J�[�\����擪�ɖ߂�
		LD1_OFF;							//LD2������
		wait_timer(100);					//0.1sec�ҋ@   		
   	}
}
*/
/**********************************************************************/
	

/**********************************************************************/
/* <DC���[�^�̎g������>                                               */
/**********************************************************************/
/*
int main(void){
	int i;	
	
	coron_init();		//Coron������(���@�\��coron_conf.h�Ŏw��)
				       	
   	//�������[�v
   	while(1){
   		if(SW_USER==1){	//SW_USER�������ꂽ��c(����=1)
   			LD1_ON;		//	LD1��_��
   			mot1_cw=MODE_CW;		//MOT1�̉�]���[�h���Z�b�g(���])
			mot2_cw=MODE_CCW;		//MOT2�̉�]���[�h���Z�b�g(�t�])
			DC_enable();			//DC���[�^����pPWM�o�͋���

			for(i=0;i<101;i++){		//MOT1->���X�ɉ���  MOT2->���X�Ɍ���
				mot1_duty=i;		//	MOT1��Duty���ݒ�(%)
				mot2_duty=(100-i);	//	MOT2��Duty���ݒ�(%)
				wait_timer(100);
			}
			for(i=0;i<101;i++){		//MOT1->���X�Ɍ���  MOT2->���X�ɉ���
				mot1_duty=(100-i);	//	MOT1��Duty���ݒ�(%)
				mot2_duty=i;		//	MOT2��Duty���ݒ�(%)
				wait_timer(100);
			}
			LD1_OFF;
			DC_disable();			//DC���[�^����pPWM�o�͋֎~
   		}
   		else{			//SW_USER��������Ă��Ȃ�������c(�����Ȃ�=0)
   			LD1_OFF;	//	LD2������
   		}	   		
   	}
}
*/
/**********************************************************************/

 
/**********************************************************************/
/* <RC�T�[�{�̎g������>                                               */
/**********************************************************************/
/*
int main(void){
	coron_init();		//Coron������(���@�\��coron_conf.h�Ŏw��)
				        
   	//RC1-0�ɐڑ����Ă���RC�T�[�{�𓮂���
   	rc_mot_pos[RC1][0]		=1500;	//�����o�͒l1500[us]
   	rc_mot_pos_trim[RC1][0]	=	0;	//�g����(�덷�C��) 0[us]
    RC_enable();					//PWM�M���̏o�͋���(�����o�� PWM->1500us)
   	
   	//�������[�v
   	while(1){
   		if(SW_USER==1){	//SW_USER�������ꂽ��c(����=1)
   			LD1_ON;		//LD1��_��
   			//���Ԑ���L��œ�����
   			rc_mot_ipos[RC1][0]=1000;	//RC1-0��1000us����PWM���o�͂���
   		    RC_move(100);				// 20msec x (100) = 2sec
   		    while(rc_step_flag);		//����I���܂ő҂�
   		    
   			rc_mot_ipos[RC1][0]=2000;	//RC1-0��2000us����PWM���o�͂���
   		    RC_move(200);				// 20msec x (200) = 4sec
   		    while(rc_step_flag);		//����I���܂ő҂�
   		}
   		
   		else{			//SW_USER��������Ă��Ȃ�������c(�����Ȃ�=0)
   			LD1_OFF;	//LD1������
   			//���Ԑ��䖳���œ�����
   			rc_mot_pos[RC1][0]=1300;	//RC1-0��1300us����PWM���o�͂���
   			wait_timer(5000);			//0.5sec�ҋ@
   			rc_mot_pos[RC1][0]=1700;	//RC1-0��1700us����PWM���o�͂���
   			wait_timer(5000);			//0.5sec�ҋ@
   		}	
   	}
 	return 0;
}
*/
/**********************************************************************/


/**********************************************************************/
/* <SD�J�[�h(WAV�t�@�C���Đ�)�̎g������>                              */
/**********************************************************************/
/*
int main(void){
	int i,n=0;
	coron_init();			//Coron������(���@�\��coron_conf.h�Ŏw��)

	while(!SW_USER);		//SW_USER���������܂őҋ@

	//SD�J�[�h "SoundData"�t�@���_��WAV�t�@�C������\��
	//	wav_count      :�t�H���_����WAV�t�@�C����
	//	wav_name[50][8]:�t�H���_����WAV�t�@�C����
	USB_puts("SD WAV_File List...\r\n");
	for(i=0;i<wav_count;i++){
		USB_putd(&wav_name[i][0],8);
		USB_puts("\r\n");
	}		       

   	//�������[�v
   	while(1){
  		if(SW_USER==1){		//SW_USER�������ꂽ��c(����=1)
   			LD1_ON;			//	LD1��_��
   			SD_play_wav(n);	//	n�Ԗڂ�WAV�t�@�C�����Đ�����
   			n++;			//  n������Z
   			if(n==wav_count){n=0;}
   		}
   		else{				//SW_USER��������Ă��Ȃ�������c(�����Ȃ�=0)
   			LD1_OFF;		//	LD2������
   		}
   	}
 	return 0;
}
*/
/**********************************************************************/


/**********************************************************************/
/* <UART����M�̎g������>                                             */
/**********************************************************************/
/*
int main(void){
	char buf=0;
	coron_init();			//Coron������
							//�{�[���[�g�Ȃǂ̐ݒ��coron_conf.h�Ŏw��
   	//�������[�v
   	while(1){
   		buf=UART_getc(1);	//�P������M(0:��M�҂����� 1:��M�҂��L��)
   		UART_putc(buf);		//�P�������M
   	}
 	return 0;
}
*/
/**********************************************************************/


/**********************************************************************/
/* <SD TXT�t�@�C��Read&Write�̎g������>                                     */
/**********************************************************************/
/*
int main(void){
	int n=0;
	coron_init();					//Coron������

   	//�������[�v
   	while(1){
   		if(SW_USER==1){				//SW_USER�������ꂽ��c(����=1)
   			LD1_ON;					//LD1��_��
   			SD_txt_write_c(n,0,'A');//n�Ԗڂ�TXT�t�@�C���̂O�����ڂ�'A'��������
			SD_txt_USBput(n,1);		//USB CDC��"TextData"�t�H���_����TXT�t�@�C����\������
									//(0�Ԗڂ�TXT�t�@�C���A�w�b�_�\���L��(=1))
			SD_txt_UARTput(n,1);	//UART(XBee)��"TextData"�t�H���_����TXT�t�@�C����\������
   			n++;					//n������Z
   			if(n==txt_count){n=0;}
   		}
   		else{						//SW_USER��������Ă��Ȃ�������c(�����Ȃ�=0)
   			LD1_OFF;				//	LD2������
   		}
   	}
 	return 0;
}
*/
/**********************************************************************/

//===================================================================
// End of Program
//===================================================================

/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_usbprint.c                   */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron UART Library Source          */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_UART
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

//==============================================================================
// Coron�V���A���|�[�g�������֐�
//==============================================================================
void UART_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	//CN-UART(XBee)�|�[�g��񓯊��V���A���ʐM�|�[�g�Ƃ��Đݒ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CN_UART, ENABLE);
	/* Configure USARTx_Tx as alternate function push-pull */
    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = CN_UART_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USARTx_Rx as input floating */
    GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = CN_UART_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART�̐ݒ�
	USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate = UART_BAUDRATE;			//�{�[���[�g
    USART_InitStructure.USART_WordLength = UART_LENGTH;			//�f�[�^��
    USART_InitStructure.USART_StopBits = UART_STOP;				//�X�g�b�v�r�b�g
    USART_InitStructure.USART_Parity = UART_PARITY;				//�p���e�B
    USART_InitStructure.USART_HardwareFlowControl = UART_Flow;	//�t���[����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(CN_UART, &USART_InitStructure);
    /* Enable the USARTx */
    USART_Cmd(CN_UART, ENABLE);
}

//==============================================================================
// UART �P�����o��
//==============================================================================
void UART_putc(char data){
	while( USART_GetFlagStatus(CN_UART, USART_FLAG_TXE ) == RESET );
	USART_SendData(CN_UART,data);
}

//==============================================================================
// UART ������o��
//==============================================================================
void UART_puts(char* buf){
	u16 cnt = 0;
	while(buf[cnt]!='\0'){
		UART_putc(buf[cnt]);
		cnt++;
	}
}

//==============================================================================
// UART �w�萔������o��(������A������)
//==============================================================================
void UART_putd(char* buf,char len){
	u16 cnt = 0;
	while(len){
		UART_putc(buf[cnt]);
		cnt++;
		len--;
	}
}

//==============================================================================
// UART �P��������(0:��M�҂����� 1:��M�҂��L��)
//==============================================================================
char UART_getc(char wf){
	if(wf){
		// ��M����܂őҋ@
		while( USART_GetFlagStatus(CN_UART, USART_FLAG_RXNE ) == RESET );
	}
   	return USART_ReceiveData(CN_UART);	// CMD or ACK	
}

//==============================================================================
// UART ���������
//==============================================================================
u16 UART_gets(char* buf){
	u16 cnt = 0;
	char c;
	while(1){
		c = (UART_getc(1));
		if(((c == '\n')||(c == '\r'))||(c == '\0')){
			buf[cnt]='\0';
		    break;
		}
	    else{
	    	buf[cnt] = c;
	    	cnt++;
	    }
	}
	return cnt;
}

//==============================================================================
// UART �o�C�i��10�i����ASCII16�i���ϊ�
//==============================================================================
char UART_put_x16(char num){
	if(num<10){
		return ('0'+num);
	}
	else{
		return ('A'+(num-10));
	}
}

//==============================================================================
// UART 16�i���o��(���l�A�\������)
//==============================================================================
void UART_putx(u32 num,char len){
	u8 s[12],n=2;
	s[0]='0';
	s[1]='x';
	switch(len){
		case  8:s[n]=UART_put_x16( num/0x10000000);n++;
		case  7:s[n]=UART_put_x16((num%0x10000000)/0x1000000);n++;
		case  6:s[n]=UART_put_x16((num%0x1000000)/0x100000);n++;
		case  5:s[n]=UART_put_x16((num%0x100000)/0x10000);n++;
		case  4:s[n]=UART_put_x16((num%0x10000)/0x1000);n++;
		case  3:s[n]=UART_put_x16((num%0x1000)/0x100);n++;
		case  2:s[n]=UART_put_x16((num%0x100)/0x10);n++;
		case  1:s[n]=UART_put_x16((num%0x10));n++;
	}
	UART_putd((char*)s,n);
}

//==============================================================================
// UART 10�i���o��(���l�A�\������)
//==============================================================================
void UART_putn(s32 num,char len){
	u8 s[10],n=1;
	if(num<0){s[0]='-';num=-num;}
	else{s[0]=' ';}
	switch(len){
		case  9:s[n]=(char)('0'+((num%1000000000)/100000000));n++;
		case  8:s[n]=(char)('0'+((num%100000000)/10000000));n++;
		case  7:s[n]=(char)('0'+((num%10000000)/1000000));n++;
		case  6:s[n]=(char)('0'+((num%1000000)/100000));n++;
		case  5:s[n]=(char)('0'+((num%100000)/10000));n++;
		case  4:s[n]=(char)('0'+((num%10000)/1000));n++;
		case  3:s[n]=(char)('0'+((num%1000)/100));n++;
		case  2:s[n]=(char)('0'+((num%100)/10));n++;
		case  1:s[n]=(char)('0'+((num%10)/1));n++;
	}
	UART_putd((char*)s,n);
}

#endif
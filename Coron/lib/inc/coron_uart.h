/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_usbprint.h                   */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron UART Library Header          */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_UART_H_
#define CORON_UART_H_

/* Define ------------------------------------------------------------*/
#define CN_UART	  USART2
#define CN_UART_TX   GPIO_Pin_2
#define CN_UART_RX	  GPIO_Pin_3
#define CN_UART_GPIO GPIOA
#define RCC_APB1Periph_CN_UART RCC_APB1Periph_USART2

/* Extern ------------------------------------------------------------*/
extern void UART_init(void);					// UART ������
extern void UART_putc(char data);			// UART �P�����o��
extern void UART_puts(char* buf);			// UART ������o��
extern void UART_putd(char* buf,char len);	// UART �w�萔������o��(������A������)
extern char UART_getc(char wf);				// UART �P��������(0:��M�҂����� 1:��M�҂��L��)
extern u16 UART_gets(char* buf);				// UART ���������
extern char UART_put_x16(char num);			// UART �o�C�i��10�i����ASCII16�i���ϊ�
extern void UART_putx(u32 num,char len);		// UART 16�i���o��(���l�A�\������)
extern void UART_putn(s32 num,char len);		// UART 10�i���o��(���l�A�\������)

#endif /*CORON_UART_H_*/

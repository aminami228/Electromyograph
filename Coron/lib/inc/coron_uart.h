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
extern void UART_init(void);					// UART 初期化
extern void UART_putc(char data);			// UART １文字出力
extern void UART_puts(char* buf);			// UART 文字列出力
extern void UART_putd(char* buf,char len);	// UART 指定数文字列出力(文字列、文字数)
extern char UART_getc(char wf);				// UART １文字入力(0:受信待ち無し 1:受信待ち有り)
extern u16 UART_gets(char* buf);				// UART 文字列入力
extern char UART_put_x16(char num);			// UART バイナリ10進数→ASCII16進数変換
extern void UART_putx(u32 num,char len);		// UART 16進数出力(数値、表示桁数)
extern void UART_putn(s32 num,char len);		// UART 10進数出力(数値、表示桁数)

#endif /*CORON_UART_H_*/

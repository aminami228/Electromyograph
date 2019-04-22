/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_usbprint.h                   */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron USB print Library Header     */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_USBPRINT_H_
#define CORON_USBPRINT_H_

// USBCDC バイナリ10進数→ASCII16進数変換
extern char put_x16(char num);

// USBCDC 16進数出力(数値、表示桁数)
extern void USB_putx(u32 num,char len);
// USBCDC 10進数出力(数値、表示桁数)
extern void USB_putn(s32 num,char len);
// USBCDC １文字出力
extern void USB_putc(char data);
// USBCDC 文字列出力
extern void USB_puts(char* buf);
// USBCDC 指定数文字列出力(文字列、文字数)
extern void USB_putd(char* buf,char len);

// USBCDC １文字入力(0:受信待ち無し 1:受信待ち有り)
extern char USB_getc(char wf);
// USBCDC 文字列入力
extern char USB_gets(char *buf);
// USBCDC 指定数文字列入力(文字列、文字数)
extern char USB_getd(char *buf);
// USBCDC 文字列入力
extern void USB_getr(char *buf,char len);

#endif /*CORON_USBPRINT_H_*/

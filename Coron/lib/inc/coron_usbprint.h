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

// USBCDC �o�C�i��10�i����ASCII16�i���ϊ�
extern char put_x16(char num);

// USBCDC 16�i���o��(���l�A�\������)
extern void USB_putx(u32 num,char len);
// USBCDC 10�i���o��(���l�A�\������)
extern void USB_putn(s32 num,char len);
// USBCDC �P�����o��
extern void USB_putc(char data);
// USBCDC ������o��
extern void USB_puts(char* buf);
// USBCDC �w�萔������o��(������A������)
extern void USB_putd(char* buf,char len);

// USBCDC �P��������(0:��M�҂����� 1:��M�҂��L��)
extern char USB_getc(char wf);
// USBCDC ���������
extern char USB_gets(char *buf);
// USBCDC �w�萔���������(������A������)
extern char USB_getd(char *buf);
// USBCDC ���������
extern void USB_getr(char *buf,char len);

#endif /*CORON_USBPRINT_H_*/

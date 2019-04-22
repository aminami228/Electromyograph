/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_usbcdc.h                     */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron USB CDC Library Header       */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/

#ifndef CORON_USBCDC_H_
#define CORON_USBCDC_H_

#define MASS_MEMORY_START     0x04002000
#define BULK_MAX_PACKET_SIZE  0x00000040

extern u8 buffer_out[];
extern u8 buffer_in[];

extern u32 count_out;
extern u32 count_in;

extern void Set_USBClock(void);
extern void Enter_LowPowerMode(void);
extern void Leave_LowPowerMode(void);
extern void USB_Interrupts_Config(void);
extern void USB_Cable_Config (FunctionalState NewState);

extern void Get_SerialNum(void);

#define USB_DISCONNECT            GPIOB  
#define USB_DISCONNECT_PIN        GPIO_Pin_14
#define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOB

#endif /*CORON_USBCDC_H_*/
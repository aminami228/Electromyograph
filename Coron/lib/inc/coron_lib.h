/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_lib.h                        */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron Library include Header       */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_LIB_H_
#define CORON_LIB_H_

#include "coron_conf.h"
#include "coron_init.h"
#include "coron_wait.h"
/****************************/
#ifdef _CORON_AD
  #include "coron_ad.h"
#endif
/****************************/
/****************************/
#ifdef _CORON_RC
  #include "coron_rc.h"
#endif
/****************************/
/****************************/
#ifdef _CORON_DC
  #include "coron_dc.h"
#endif
/****************************/
/****************************/
#ifdef _CORON_SD
  #include "sdcard.h"
  #include "coron_sdfat.h"
#ifdef _CORON_SOUND
  #include "coron_sdwav.h"
  #include "coron_sound.h"
#endif
#ifdef _CORON_SDTXT
  #include "coron_sdtxt.h"
#endif
#endif
/****************************/
/****************************/
#ifdef _CORON_USBCDC
  #include "coron_usbcdc.h"
  #include "coron_usbprint.h"

  #include "usb_lib.h"
  #include "usb_prop.h"
  #include "usb_desc.h"
  #include "usb_pwr.h"
  #include "usb_istr.h"
#endif
/****************************/
/****************************/
#ifdef _CORON_UART
  #include "coron_uart.h"
#endif
/****************************/

#endif /*CORON_LIB_H_*/

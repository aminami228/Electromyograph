/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_usbprint.c                   */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron USB print Library Source     */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_USBCDC
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Global variables ----------------------------------------------------------*/
u32 timeout_cnt=0;

//==============================================================================
// USBCDC バイナリ10進数→ASCII16進数変換
//==============================================================================
char put_x16(char num){
	if(num<10){
		return ('0'+num);
	}
	else{
		return ('A'+(num-10));
	}
}

//==============================================================================
// USBCDC 16進数出力(数値、表示桁数)
//==============================================================================
void USB_putx(u32 num,char len){
	u8 s[12],n=2;
	s[0]='0';
	s[1]='x';
	switch(len){
		case  8:s[n]=put_x16( num/0x10000000);n++;
		case  7:s[n]=put_x16((num%0x10000000)/0x1000000);n++;
		case  6:s[n]=put_x16((num%0x1000000)/0x100000);n++;
		case  5:s[n]=put_x16((num%0x100000)/0x10000);n++;
		case  4:s[n]=put_x16((num%0x10000)/0x1000);n++;
		case  3:s[n]=put_x16((num%0x1000)/0x100);n++;
		case  2:s[n]=put_x16((num%0x100)/0x10);n++;
		case  1:s[n]=put_x16((num%0x10));n++;
	}
	USB_putd((char*)s,n);
}

//==============================================================================
// USBCDC 10進数出力(数値、表示桁数)
//==============================================================================
void USB_putn(s32 num,char len){
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
	USB_putd((char*)s,n);
}

//==============================================================================
// USBCDC １文字出力
//==============================================================================
void USB_putc(char data){
  if((bDeviceState == CONFIGURED)&&(usbConnectFlag==1)){
	  count_in=1;
	  UserToPMABufferCopy((u8 *)&data, ENDP1_TXADDR, count_in);
	  SetEPTxCount(ENDP1,count_in);
	  SetEPTxValid(ENDP1);
	  while(count_in!=0){
		  timeout_cnt++;
		  if(timeout_cnt==10000){count_in=0;}
	  }
	  timeout_cnt=0;
  }
}

//==============================================================================
// USBCDC 文字列出力
//==============================================================================
void USB_puts(char* buf){
  if((bDeviceState == CONFIGURED)&&(usbConnectFlag==1)){
	  count_in=0;
	  while(buf[count_in]!='\0'){count_in++;}
	  UserToPMABufferCopy((u8 *)buf, ENDP1_TXADDR, count_in);
	  SetEPTxCount(ENDP1, count_in);
	  SetEPTxValid(ENDP1);
	  while(count_in!=0){
		  timeout_cnt++;
		  if(timeout_cnt==10000){count_in=0;}
	  }
	  timeout_cnt=0;
  }
}
	
//==============================================================================
// USBCDC 指定数文字列出力(文字列、文字数)
//==============================================================================
void USB_putd(char* buf,char len){
  if((bDeviceState == CONFIGURED)&&(usbConnectFlag==1)){
	  count_in=len;
	  UserToPMABufferCopy((u8 *)buf, ENDP1_TXADDR, count_in);
	  SetEPTxCount(ENDP1, count_in);
	  SetEPTxValid(ENDP1);
	  while(count_in!=0){
		  timeout_cnt++;
		  if(timeout_cnt==10000){count_in=0;}
	  }
	  timeout_cnt=0;
  }
}

//==============================================================================
// USBCDC １文字入力(0:受信待ち無し 1:受信待ち有り)
//==============================================================================
char USB_getc(char wf){
  char buf;
  if(bDeviceState == CONFIGURED){
	  if(wf){while(count_out==0);}
	  if (count_out != 0){
		  buf=buffer_out[0];
		  count_out--;
		  return buf;
	  }
  }
  return 0;
}

//==============================================================================
// USBCDC 文字列入力
//==============================================================================
char USB_gets(char *buf){
  int n=0;
  if(bDeviceState == CONFIGURED){
	  while(count_out != 0){
		  buf[n]=buffer_out[n];
		  count_out--;
		  n++;
	  }
  }
  return n;
}

//==============================================================================
// USBCDC 指定数文字列入力(文字列、文字数)
//==============================================================================
void USB_getr(char *buf,char len){
  int n=0,i;
  if(bDeviceState == CONFIGURED){
	  for(i=0;i<len;i++){
		while(count_out==0);
	    buf[n]=buffer_out[n];
	    count_out--;
	    n++;
	  }
  }
}

//==============================================================================
// USBCDC 文字列入力
//==============================================================================
char USB_getd(char *buf){
  return USB_gets(buf);
}

#endif
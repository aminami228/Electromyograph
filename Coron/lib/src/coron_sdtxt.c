/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sdtxt.c                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :SD Text File R&W Library Source    */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_SD
#ifdef _CORON_SDTXT
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Global variables ----------------------------------------------------------*/
u32	txt_dir_sector=0;			//txtファイルディレクトリのセクタ番号
u32 txt_sector_num[50];		//各txtファイルのセクタ番号
u32 txt_size[50];			//txtファイルのサイズ
char txt_name[50][8];		//txtファイルの名前
u8 txt_count;				//"TextData"フォルダ内のtxtファイルの数

//==============================================================================
// SDカードtxtファイル検索
//==============================================================================
void SD_search_txt(void){
	txt_dir_sector=SD_serchDirectory("TEXTDA");
	txt_count=SD_getFileList(txt_dir_sector,"TXT",txt_name,txt_sector_num,txt_size);
}

//==============================================================================
// SDカードTXTファイルUSBCDC再生(ファイル番号)
//==============================================================================
#ifdef _CORON_USBCDC       			
void SD_txt_USBput(u8 txt_num,u8 header_flag){
	u32 size;
	u32 sct,sec_num,n,i;
	u32 last_byte_num;
	size =txt_size[txt_num];
	sct  =txt_sector_num[txt_num];
		
	//TXTファイルデータがあるセクタ数－1
	sec_num=(size/512);
	//最後のセクタのバイト数－1
	last_byte_num=(size%512)-1;
	//ヘッダ情報の表示
	if(header_flag){
		USB_puts("\r\n\n");	
		USB_puts("*******************************\r\n");
		USB_puts("*   [SD Card Text File Put]   *\r\n");
		USB_puts("*******************************\r\n");
		USB_puts("  File Number =");	
		USB_putn(txt_num,3);
		USB_puts("\r\n");	
		USB_puts("  File Name   = ");	
		USB_putd(&txt_name[txt_num][0],8);
		USB_puts("\r\n");	
		USB_puts("  File Size   =");	
		USB_putn(txt_size[txt_num],8); 				
		USB_puts("[Byte]\r\n");
		USB_puts("  File Sector =");	
		USB_putn(txt_sector_num[txt_num],8); 				
		USB_puts("\r\n");
		USB_puts("*******************************\r\n");
		USB_puts("Text Start...\r\n");
		USB_puts("*******************************\r\n");
	}
	//ファイルの中身を表示する
    for(n=0;n<(sec_num);n++){
    	SD_read(512*(n + sct));
        for(i=0;i<512;i++){
        	USB_putc(buf512[i]);
        }
    }
	//最後のセクタを読み込む(データが無い部分を飛ばす)
    SD_read(512*(sct+sec_num));
    for(i=0;i<=last_byte_num;i++){
    	USB_putc(buf512[i]);
    }    
    
	if(header_flag){
	    USB_puts("\r\n*******************************\r\n");
		USB_puts("Text End...\r\n");
		USB_puts("*******************************\r\n\n");
	}
}
#endif

//==============================================================================
// SDカードTXTファイルUART(XBee)再生(ファイル番号)
//==============================================================================
#ifdef _CORON_UART       			
void SD_txt_UARTput(u8 txt_num,u8 header_flag){
	u32 size;
	u32 sct,sec_num,n,i;
	u32 last_byte_num;
	size =txt_size[txt_num];
	sct  =txt_sector_num[txt_num];
		
	//TXTファイルデータがあるセクタ数－1
	sec_num=(size/512);
	//最後のセクタのバイト数－1
	last_byte_num=(size%512)-1;
	
	if(header_flag){
		UART_puts("\r\n\n");	
		UART_puts("*******************************\r\n");
		UART_puts("*   [SD Card Text File Put]   *\r\n");
		UART_puts("*******************************\r\n");
		UART_puts("  File Number =");	
		UART_putn(txt_num,3);
		UART_puts("\r\n");	
		UART_puts("  File Name   = ");	
		UART_putd(&txt_name[txt_num][0],8);
		UART_puts("\r\n");	
		UART_puts("  File Size   =");	
		UART_putn(txt_size[txt_num],8); 				
		UART_puts("[Byte]\r\n");
		UART_puts("  File Sector =");	
		UART_putn(txt_sector_num[txt_num],8); 				
		UART_puts("\r\n");
		UART_puts("*******************************\r\n");
		UART_puts("Text Start...\r\n");
		UART_puts("*******************************\r\n");
	}
	
    for(n=0;n<(sec_num);n++){
    	SD_read(512*(n + sct));
        for(i=0;i<512;i++){
        	UART_putc(buf512[i]);
        }
    }
	//最後のセクタを読み込む(データが無い部分を飛ばす)
    SD_read(512*(sct+sec_num));
    for(i=0;i<=last_byte_num;i++){
    	UART_putc(buf512[i]);
    }    
    
	if(header_flag){
	    UART_puts("\r\n*******************************\r\n");
		UART_puts("Text End...\r\n");
		UART_puts("*******************************\r\n\n");
	}
}
#endif

//==============================================================================
// SDカードTXTファイル 1文字読込み(ファイル番号、文字番号)
//==============================================================================
char SD_txt_read_c(u8 txt_num,u32 s_num){		
	u16 buf_num=0; 
	u32 sct;

	buf_num = (s_num%512);						  		//指定の文字が保存されているバイト番号
	sct		= txt_sector_num[txt_num]+(s_num/512);		//指定の文字が保存されているセクタ番号			
    SD_read(512*sct);									//読込みたいバイトがあるセクタを読込む
        
    return buf512[buf_num];	
}

//==============================================================================
// SDカードTXTファイル 1文字書き込み(ファイル番号、文字番号、書込む文字)
//==============================================================================
void SD_txt_write_c(u8 txt_num,u32 s_num,char wbuf){		
	u16 buf_num=0; 
	u32 sct;

	if(s_num <= txt_size[txt_num]){
		buf_num = (s_num%512);						  	//指定の文字が保存されているバイト番号
		sct		= txt_sector_num[txt_num]+(s_num/512);	//指定の文字が保存されているセクタ番号			
		SD_read(512*sct);								//書込みたいバイトがあるセクタを読込む
		buf512[buf_num]=wbuf;							//１文字だけバッファを入れ替える
		SD_write(512*sct);								//書込みたいバイトがあるセクタを書込む
	}
}

//==============================================================================
// SDカードTXTファイル 文字列読込み(ファイル番号、文字番号、文字列、読込む文字数)
//==============================================================================
void SD_txt_read_s(u8 txt_num,u32 s_num,char* buf,u16 len){		
	u16 buf_num=0,i=0;
	u16 buf_bit=0;
	u32 sct;

	for(i=0;i<len;i++){
		buf_num = ((s_num+i)%512);						  //指定の文字が保存されているバイト番号
		sct		= txt_sector_num[txt_num]+((s_num+i)/512);//指定の文字が保存されているセクタ番号			

		//セクタをまたぐ場合
		if((buf_num+len)>512){
			buf_bit = (buf_num+len)-512;	//１セクタから漏れる分
			//前半部
			SD_read(512*sct);				//セクタを読込む
			for(i=0;i<(len-buf_bit);i++){	//データを格納
				buf[i]=buf512[buf_num+i];
			}

			//後半部
			SD_read(512*(sct+1));			//セクタを読込む
			for(i=0;i<buf_bit;i++){			//データを格納
				buf[(len-buf_bit)+i]=buf512[i];
			}
		}
		//セクタをまたがない場合
		else{
			SD_read(512*sct);
			for(i=0;i<len;i++){
				buf[i]=buf512[buf_num+i];
			}
		}		
	}    
}

//==============================================================================
// SDカードTXTファイル 文字列書込み(ファイル番号、文字番号、文字列、読込む文字数)
//==============================================================================
void SD_txt_write_s(u8 txt_num,u32 s_num,char* buf,u16 len){		
	u16 buf_num=0,i=0;
	u16 buf_bit=0;
	u32 sct;

	if((s_num+len) <= txt_size[txt_num]){
		buf_num = (s_num%512);						  //指定の文字が保存されているバイト番号
		sct		= txt_sector_num[txt_num]+(s_num/512);//指定の文字が保存されているセクタ番号			

		//セクタをまたぐ場合
		if((buf_num+len)>512){
			buf_bit = (buf_num+len)-512;	//１セクタから漏れる分
			//前半部
			SD_read(512*sct);				//セクタを読込む
			for(i=0;i<(len-buf_bit);i++){	//データを格納
				buf512[buf_num+i]=buf[i];
			}
			SD_write(512*sct);				//セクタを書込む

			//後半部
			SD_read(512*(sct+1));			//セクタを読込む
			for(i=0;i<buf_bit;i++){			//データを格納
				buf512[i]=buf[(len-buf_bit)+i];
			}
			SD_write(512*(sct+1));			//セクタを書込む
		}
		//セクタをまたがない場合
		else{
			SD_read(512*sct);
			for(i=0;i<len;i++){
				buf512[buf_num+i]=buf[i];
			}
			SD_write(512*sct);			
		}		
	}
}

#endif
#endif

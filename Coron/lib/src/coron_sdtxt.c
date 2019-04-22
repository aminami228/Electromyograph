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
u32	txt_dir_sector=0;			//txt�t�@�C���f�B���N�g���̃Z�N�^�ԍ�
u32 txt_sector_num[50];		//�etxt�t�@�C���̃Z�N�^�ԍ�
u32 txt_size[50];			//txt�t�@�C���̃T�C�Y
char txt_name[50][8];		//txt�t�@�C���̖��O
u8 txt_count;				//"TextData"�t�H���_����txt�t�@�C���̐�

//==============================================================================
// SD�J�[�htxt�t�@�C������
//==============================================================================
void SD_search_txt(void){
	txt_dir_sector=SD_serchDirectory("TEXTDA");
	txt_count=SD_getFileList(txt_dir_sector,"TXT",txt_name,txt_sector_num,txt_size);
}

//==============================================================================
// SD�J�[�hTXT�t�@�C��USBCDC�Đ�(�t�@�C���ԍ�)
//==============================================================================
#ifdef _CORON_USBCDC       			
void SD_txt_USBput(u8 txt_num,u8 header_flag){
	u32 size;
	u32 sct,sec_num,n,i;
	u32 last_byte_num;
	size =txt_size[txt_num];
	sct  =txt_sector_num[txt_num];
		
	//TXT�t�@�C���f�[�^������Z�N�^���|1
	sec_num=(size/512);
	//�Ō�̃Z�N�^�̃o�C�g���|1
	last_byte_num=(size%512)-1;
	//�w�b�_���̕\��
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
	//�t�@�C���̒��g��\������
    for(n=0;n<(sec_num);n++){
    	SD_read(512*(n + sct));
        for(i=0;i<512;i++){
        	USB_putc(buf512[i]);
        }
    }
	//�Ō�̃Z�N�^��ǂݍ���(�f�[�^�������������΂�)
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
// SD�J�[�hTXT�t�@�C��UART(XBee)�Đ�(�t�@�C���ԍ�)
//==============================================================================
#ifdef _CORON_UART       			
void SD_txt_UARTput(u8 txt_num,u8 header_flag){
	u32 size;
	u32 sct,sec_num,n,i;
	u32 last_byte_num;
	size =txt_size[txt_num];
	sct  =txt_sector_num[txt_num];
		
	//TXT�t�@�C���f�[�^������Z�N�^���|1
	sec_num=(size/512);
	//�Ō�̃Z�N�^�̃o�C�g���|1
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
	//�Ō�̃Z�N�^��ǂݍ���(�f�[�^�������������΂�)
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
// SD�J�[�hTXT�t�@�C�� 1�����Ǎ���(�t�@�C���ԍ��A�����ԍ�)
//==============================================================================
char SD_txt_read_c(u8 txt_num,u32 s_num){		
	u16 buf_num=0; 
	u32 sct;

	buf_num = (s_num%512);						  		//�w��̕������ۑ�����Ă���o�C�g�ԍ�
	sct		= txt_sector_num[txt_num]+(s_num/512);		//�w��̕������ۑ�����Ă���Z�N�^�ԍ�			
    SD_read(512*sct);									//�Ǎ��݂����o�C�g������Z�N�^��Ǎ���
        
    return buf512[buf_num];	
}

//==============================================================================
// SD�J�[�hTXT�t�@�C�� 1������������(�t�@�C���ԍ��A�����ԍ��A�����ޕ���)
//==============================================================================
void SD_txt_write_c(u8 txt_num,u32 s_num,char wbuf){		
	u16 buf_num=0; 
	u32 sct;

	if(s_num <= txt_size[txt_num]){
		buf_num = (s_num%512);						  	//�w��̕������ۑ�����Ă���o�C�g�ԍ�
		sct		= txt_sector_num[txt_num]+(s_num/512);	//�w��̕������ۑ�����Ă���Z�N�^�ԍ�			
		SD_read(512*sct);								//�����݂����o�C�g������Z�N�^��Ǎ���
		buf512[buf_num]=wbuf;							//�P���������o�b�t�@�����ւ���
		SD_write(512*sct);								//�����݂����o�C�g������Z�N�^��������
	}
}

//==============================================================================
// SD�J�[�hTXT�t�@�C�� ������Ǎ���(�t�@�C���ԍ��A�����ԍ��A������A�Ǎ��ޕ�����)
//==============================================================================
void SD_txt_read_s(u8 txt_num,u32 s_num,char* buf,u16 len){		
	u16 buf_num=0,i=0;
	u16 buf_bit=0;
	u32 sct;

	for(i=0;i<len;i++){
		buf_num = ((s_num+i)%512);						  //�w��̕������ۑ�����Ă���o�C�g�ԍ�
		sct		= txt_sector_num[txt_num]+((s_num+i)/512);//�w��̕������ۑ�����Ă���Z�N�^�ԍ�			

		//�Z�N�^���܂����ꍇ
		if((buf_num+len)>512){
			buf_bit = (buf_num+len)-512;	//�P�Z�N�^����R��镪
			//�O����
			SD_read(512*sct);				//�Z�N�^��Ǎ���
			for(i=0;i<(len-buf_bit);i++){	//�f�[�^���i�[
				buf[i]=buf512[buf_num+i];
			}

			//�㔼��
			SD_read(512*(sct+1));			//�Z�N�^��Ǎ���
			for(i=0;i<buf_bit;i++){			//�f�[�^���i�[
				buf[(len-buf_bit)+i]=buf512[i];
			}
		}
		//�Z�N�^���܂����Ȃ��ꍇ
		else{
			SD_read(512*sct);
			for(i=0;i<len;i++){
				buf[i]=buf512[buf_num+i];
			}
		}		
	}    
}

//==============================================================================
// SD�J�[�hTXT�t�@�C�� �����񏑍���(�t�@�C���ԍ��A�����ԍ��A������A�Ǎ��ޕ�����)
//==============================================================================
void SD_txt_write_s(u8 txt_num,u32 s_num,char* buf,u16 len){		
	u16 buf_num=0,i=0;
	u16 buf_bit=0;
	u32 sct;

	if((s_num+len) <= txt_size[txt_num]){
		buf_num = (s_num%512);						  //�w��̕������ۑ�����Ă���o�C�g�ԍ�
		sct		= txt_sector_num[txt_num]+(s_num/512);//�w��̕������ۑ�����Ă���Z�N�^�ԍ�			

		//�Z�N�^���܂����ꍇ
		if((buf_num+len)>512){
			buf_bit = (buf_num+len)-512;	//�P�Z�N�^����R��镪
			//�O����
			SD_read(512*sct);				//�Z�N�^��Ǎ���
			for(i=0;i<(len-buf_bit);i++){	//�f�[�^���i�[
				buf512[buf_num+i]=buf[i];
			}
			SD_write(512*sct);				//�Z�N�^��������

			//�㔼��
			SD_read(512*(sct+1));			//�Z�N�^��Ǎ���
			for(i=0;i<buf_bit;i++){			//�f�[�^���i�[
				buf512[i]=buf[(len-buf_bit)+i];
			}
			SD_write(512*(sct+1));			//�Z�N�^��������
		}
		//�Z�N�^���܂����Ȃ��ꍇ
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

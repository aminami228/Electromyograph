/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_sdfat.c                      */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :SD FAT16system Library Source      */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#include "coron_conf.h"
#ifdef _CORON_SD
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Private define ------------------------------------------------------------*/
//#define UDB	//SDカードErrorCode出力

/* Global variables ----------------------------------------------------------*/
u32	hidden_sector=0;						//Hiddenセクタ番号
u32	fat_sector=0,dir_sector=0,dat_sector=0;	//FATセクタ番号
u8 	sectors_per_cluster=0;					//1クラスタ当たりのセクタ数
u32 buf512[512];							//1セクタ格納バッファ
SD_CardInfo SDCardInfo;
u32 Buffer_Block_Tx[BufferWordsSize], Buffer_Block_Rx[BufferWordsSize];
u32 Buffer_MultiBlock_Tx[MultiBufferWordsSize], Buffer_MultiBlock_Rx[MultiBufferWordsSize];
//volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
SD_Error Status = SD_OK;

const u8 s_fat16[5]={'F','A','T','1','6'};

//==============================================================================
// SDカード FATシステム初期化
//==============================================================================
int SD_FATinit(){
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Enable SDIO clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);
    /* Enable DMA1 clocks */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* Enable the SDIO_IRQ Interrupt */
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_StructInit(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //SDカード初期化
    /*-------------------------- SD Init ----------------------------- */
    Status = SD_Init();
    /*----------------- Read CSD/CID MSD registers ------------------*/
    if (Status == SD_OK){Status = SD_GetCardInfo(&SDCardInfo);}
    /*----------------- Select Card --------------------------------*/
    if (Status == SD_OK){Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));}
    if (Status == SD_OK){Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);}
    /* Set Device Transfer Mode to DMA */
    if (Status == SD_OK){Status = SD_SetDeviceMode(SD_DMA_MODE);}
    if(Status == SD_OK){//初期化完了
        SD_getDirSector();
        return 1;
    }
    else{//初期化失敗
    	return 0;
    }
}

//==============================================================================
// SDカード 1ブロック読み込み
//==============================================================================
void SD_read(u32 adr){
	int wcnt=0,bcnt=0;
	if (Status == SD_OK){
#if UDB
	   	wait_timer(500);
		USB_puts("SD_ReadBlock...");
	   	wait_timer(500);
#endif
		/* Read block of 512 bytes from address 0 */
	    Status = SD_ReadBlock(adr, Buffer_Block_Rx, BlockSize);
	    for(wcnt=0;wcnt<128;wcnt++){
	    	buf512[bcnt]   =  (Buffer_Block_Rx[wcnt]&0x000000ff);
	    	buf512[bcnt+1] = ((Buffer_Block_Rx[wcnt]&0x0000ff00)>>8);
	    	buf512[bcnt+2] = ((Buffer_Block_Rx[wcnt]&0x00ff0000)>>16);
	    	buf512[bcnt+3] = ((Buffer_Block_Rx[wcnt]&0xff000000)>>24);
	    	bcnt+=4;
	    }	   	
	}
#if UDB
	switch(Status){
		case SD_INVALID_PARAMETER:	USB_puts("SD_INVALID_PARAMETER");break;
		case SD_LOCK_UNLOCK_FAILED:	USB_puts("SD_LOCK_UNLOCK_FAILED");break;
		case SD_DATA_TIMEOUT:		USB_puts("SD_DATA_TIMEOUT");break;
		case SD_DATA_CRC_FAIL:		USB_puts("SD_DATA_CRC_FAIL");break;
		case SD_RX_OVERRUN:  		USB_puts("SD_RX_OVERRUN");break;
		case SD_START_BIT_ERR:		USB_puts("SD_START_BIT_ERR");break;
		case SD_ERROR:				USB_puts("SD_ERROR");break;
		case SD_OK:					USB_puts("SD_OK");break;
		default:USB_puts("???");
	}
   	wait_timer(500);
	USB_puts("\r\n");
   	wait_timer(500);
#endif
}

//==============================================================================
// SDカード 1ブロック書き込み
//==============================================================================
void SD_write(u32 adr){
	int wcnt=0,bcnt=0;
	if (Status == SD_OK){
#if UDB
	   	wait_timer(500);
		USB_puts("SD_WriteBlock...");
	   	wait_timer(500);
#endif

	    /* Write block of 512 bytes on address 0 */
	    for(wcnt=0;wcnt<128;wcnt++){
	    	Buffer_Block_Tx[wcnt]=((buf512[bcnt+3]<<24)|(buf512[bcnt+2]<<16)|(buf512[bcnt+1]<<8)|(buf512[bcnt]));
	    	bcnt+=4;
	    }	    
	    Status = SD_WriteBlock(adr, Buffer_Block_Tx, BlockSize);
	}
#if UDB
	switch(Status){
		case SD_INVALID_PARAMETER:	USB_puts("SD_INVALID_PARAMETER");break;
		case SD_LOCK_UNLOCK_FAILED:	USB_puts("SD_LOCK_UNLOCK_FAILED");break;
		case SD_DATA_TIMEOUT:		USB_puts("SD_DATA_TIMEOUT");break;
		case SD_DATA_CRC_FAIL:		USB_puts("SD_DATA_CRC_FAIL");break;
		case SD_RX_OVERRUN:  		USB_puts("SD_RX_OVERRUN");break;
		case SD_START_BIT_ERR:		USB_puts("SD_START_BIT_ERR");break;
		case SD_ERROR:				USB_puts("SD_ERROR");break;
		case SD_OK:					USB_puts("SD_OK");break;
		default:USB_puts("???");
	}
   	wait_timer(500);
	USB_puts("\r\n");
   	wait_timer(500);
#endif
}

//==============================================================================
// ASCII数値→バイナリ数値変換
//==============================================================================
s16 SD_char_to_num(char *s,char len){
	s16 num=0;
		
	if(s[0]=='-'){
		switch(len){
			case 6:num+=(s[len-5]-'0')*10000;
			case 5:num+=(s[len-4]-'0')*1000;
			case 4:num+=(s[len-3]-'0')*100;
			case 3:num+=(s[len-2]-'0')*10;
			case 2:num+=(s[len-1]-'0');
		}
		num = -num;
	}
	else if(s[0]=='+'){
		switch(len){
			case 6:num+=(s[len-5]-'0')*10000;
			case 5:num+=(s[len-4]-'0')*1000;
			case 4:num+=(s[len-3]-'0')*100;
			case 3:num+=(s[len-2]-'0')*10;
			case 2:num+=(s[len-1]-'0');
		}
	}
	else{
		switch(len){
			case 5:num+=(s[len-5]-'0')*10000;
			case 4:num+=(s[len-4]-'0')*1000;
			case 3:num+=(s[len-3]-'0')*100;
			case 2:num+=(s[len-2]-'0')*10;
			case 1:num+=(s[len-1]-'0');
		}
	}
	return num;
}

//==============================================================================
// バイナリ数値→ASCII数値変換
//==============================================================================
void SD_num_to_char(long num,u8 len,char *s){
	u8 cnt=0;
	if(num<0){
		s[cnt]='-';num=-num;cnt++;
		switch(len){
			case 5:s[cnt]='0'+((num%10000)/1000);cnt++;
			case 4:s[cnt]='0'+((num%1000)/100);cnt++;
			case 3:s[cnt]='0'+((num%100)/10);cnt++;
			case 2:s[cnt]='0'+((num%10));
		}
	}
	else{
		switch(len){
			case 5:s[cnt]='0'+((num%100000)/10000);cnt++;
			case 4:s[cnt]='0'+((num%10000)/1000);cnt++;
			case 3:s[cnt]='0'+((num%1000)/100);cnt++;
			case 2:s[cnt]='0'+((num%100)/10);cnt++;
			case 1:s[cnt]='0'+((num%10));
		}		
	}
}

//==============================================================================
// SDカード ルートディレクトリ取得
//==============================================================================
void SD_getDirSector(void){
	int i;
	u8 bpb_flag=0;
	SD_read(0);
	for(i=0;i<5;i++){
		if(buf512[54+i]==s_fat16[i]){bpb_flag++;}
	}
	if(bpb_flag!=5){
		hidden_sector=((buf512[454])+(buf512[455]<<8)+(buf512[456]<<16)+(buf512[457]<<24));
		SD_read(hidden_sector*512);
	}
	fat_sector = (buf512[0x1c]+(buf512[0x1d]<<8)+(buf512[0x1e]<<16)+(buf512[0x1f]<<24)) + ((buf512[0x0e])+(buf512[0x0f]<<8));
	dir_sector = fat_sector + ((buf512[0x16]+(buf512[0x17]<<8))*buf512[0x10]);
	dat_sector = dir_sector+32;
	sectors_per_cluster=(buf512[0x0d]);		
}

//==============================================================================
// SDカード ディレクトリ内ファイル取得
//==============================================================================
u16 SD_getFileList(u32 sec,char *sn,char (*file_name)[8],u32 *sct_num,u32 *size){
	u16 i,j,k,file_num=0;
		
	for(i=0;i<16;i++){
		SD_read((sec+i)*512);
		for(j=0;j<16;j++){
			if((buf512[(32*j)]>0x20)&&(buf512[(32*j)]!=0xe5)){
				if(((buf512[(32*j)+8]==sn[0])&&(buf512[(32*j)+9]==sn[1]))&&(buf512[(32*j)+10]==sn[2])){
					for(k=0;k<8;k++){
						file_name[file_num][k] = buf512[(32*j)+k];
					}						
					sct_num[file_num]	=dat_sector + ((buf512[0x1a+(32*j)]+(buf512[0x1b+(32*j)]<<8)-2) * sectors_per_cluster);
					size[file_num]	=0;
					size[file_num]	+=buf512[(32*j)+0x1c];
					size[file_num]	+=buf512[(32*j)+0x1d]<<8;
					size[file_num]	+=buf512[(32*j)+0x1e]<<16;
					size[file_num]	+=buf512[(32*j)+0x1f]<<24;
					file_num++;						
				}
			}
		}
	}
	return file_num;
}

//==============================================================================
// SDカード 指定文字列ディレクトリ検索
//==============================================================================
u32 SD_serchDirectory(const char* s){
	int i,j,k,mf=0;
	u32 sec=0;
		
	for(i=0;i<32;i++){
		SD_read((dir_sector+i)*512);
		for(j=0;j<16;j++){
			if(((buf512[(32*j)]>0x20)&&(buf512[(32*j)]!=0xe5)) && ((buf512[(32*j)+11]&0x10)>>4)){
				for(k=0;k<6;k++){
					if(buf512[(32*j)+k]==s[k]){mf++;}
				}
				if(mf>5){
					sec = dat_sector + ((buf512[0x1a+(32*j)]+(buf512[0x1b+(32*j)]<<8)-2) * sectors_per_cluster);
				}
			}
			mf=0;
		}
	}
	return sec;	
}

#endif

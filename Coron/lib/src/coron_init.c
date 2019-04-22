/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_init.c                       */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Coron initialize Library Source    */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "coron_lib.h"

/* Private define ------------------------------------------------------------*/
#define WAIT_POWER 1000000	//�d�������肷��܂ő҂���

/* Prototype -----------------------------------------------------------------*/
void coron_GPIO_Configuration(void);
void coron_NVIC_Configuration(void);
void coron_RCC_Configuration(void);

//==============================================================================
// �d������҂�Wait�֐�
//==============================================================================
void wait_power(void){
	volatile long loop=WAIT_POWER;
	while(loop--);
}

//==============================================================================
// Coron �������֐�
//==============================================================================
void coron_init(){
    
    //�V�X�e���N���b�N������
	coron_RCC_Configuration();
    //NVIC������
	coron_NVIC_Configuration();
    //GPIO������
	coron_GPIO_Configuration();
    //wait������
	wait_init();
    
    LD1_OFF;LD2_OFF;LD3_OFF;	//LD1~3��S����
    wait_power();				//�d�������肷��܂ő҂�
    
    //USB CDC
	#ifdef _CORON_USBCDC
    	Set_USBClock();
    	USB_Interrupts_Config();
    	USB_Init();	
	#endif

    //USB UART
	#ifdef _CORON_UART
    	UART_init();
	#endif
    	
    //SD
    #ifdef _CORON_SD
       	//SD�J�[�h������
       	if(SD_FATinit()){			//SD�J�[�h������������       		
    		#ifdef _CORON_SOUND
       			SD_search_wav();  	//SD�J�[�h��"SoundData"�t�H���_���ɂ���WAV�t�@�C�������擾����
    		#endif
			#ifdef _CORON_SDTXT       			
       			SD_search_txt();	//SD�J�[�h��"TextData"�t�H���_���ɂ���TXT�t�@�C�������擾����
			#endif
       	}
    #endif

    //SPK
    #ifdef _CORON_SOUND
       	//DA�R���o�[�^(�X�s�[�J�o��)������
       	SPK_init();
    #endif     
       	       	
    //DC
	#ifdef _CORON_DC
       	//DC�T�[�{������
       	DC_init();
	#endif

    //RC
	#ifdef _CORON_RC
       	//RC�T�[�{������
       	RC_init();
	#endif

    //AD
	#ifdef _CORON_AD
       	//IOA_AD������
       	IOA_AD_init(IOA_AD_SET_PORT);
	#endif
}

//==============================================================================
// Coron RCC�������֐�
//==============================================================================
void coron_RCC_Configuration(void){
	ErrorStatus HSEStartUpStatus;
    // SYSCLK, HCLK, PCLK2 and PCLK1 configuration
    // RCC system reset(for debug purpose)
    RCC_DeInit();
    // Enable HSE
    RCC_HSEConfig(RCC_HSE_ON);
    // Wait till HSE is ready
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS){
        // Enable Prefetch Buffer
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        // Flash 2 wait state
        FLASH_SetLatency(FLASH_Latency_2);
        // HCLK = SYSCLK
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // PCLK2 = HCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);
        // PCLK1 = HCLK/2
        RCC_PCLK1Config(RCC_HCLK_Div2);
        // ADCCLK = PCLK2/6
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);
        /* PLLCLK = 12MHz * 6 = 72 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
        // Enable PLL
        RCC_PLLCmd(ENABLE);
        // Wait till PLL is ready
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        // Select PLL as system clock source
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        // Wait till PLL is used as system clock source
        while(RCC_GetSYSCLKSource() != 0x08);
      }
      /* GPIOA,GPIOB,GPIOC clock enable */
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
}

//==============================================================================
// Coron GPIO(LD1,LD2,LD3,SW_USER)�������֐�
//==============================================================================
void coron_GPIO_Configuration(void){
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  //LED init
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //Switch(SW_USER) init
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//==============================================================================
// Coron NVIC�������֐�
//==============================================================================
void coron_NVIC_Configuration(void){
	NVIC_DeInit();

    #ifdef  VECT_TAB_RAM
    // Set the Vector Table base location at 0x20000000
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
    #else  // VECT_TAB_FLASH
		#ifdef _DFU_MODE
    		// Set the Vector Table base location at 0x08003000 for DFU
    		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000);
		#else
    		// Set the Vector Table base location at 0x08000000
    		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
		#endif
    #endif

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
}


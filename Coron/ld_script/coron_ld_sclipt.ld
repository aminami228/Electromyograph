/* Linker script for Coron  Date:2009/10/22 */

/*default stack sizes*/
__Stack_Size = 4096 ;
PROVIDE ( _Stack_Size = __Stack_Size ) ;
__Stack_Init = _estack  - __Stack_Size ;

PROVIDE ( _Stack_Init = __Stack_Init ) ;

_Minimum_Stack_Size = 0x400 ;

/*this sends all unreferenced IRQHandlers to reset*/

PROVIDE (   Undefined_Handler = 0 ) ;
PROVIDE (   SWI_Handler = 0 ) ;
PROVIDE (   IRQ_Handler = 0 ) ;
PROVIDE (   Prefetch_Handler = 0 ) ;
PROVIDE (   Abort_Handler = 0 ) ;
PROVIDE (   FIQ_Handler = 0 ) ;

PROVIDE (   NMIException = 0 ) ;
PROVIDE (   HardFaultException = 0 ) ;
PROVIDE (   MemManageException = 0 ) ;
PROVIDE (   BusFaultException = 0 ) ;
PROVIDE (   UsageFaultException = 0 ) ;
PROVIDE (   SVCHandler = 0 ) ;
PROVIDE (   DebugMonitor = 0 ) ;
PROVIDE (   PendSVC = 0 ) ;
PROVIDE (   SysTickHandler = 0 ) ;
PROVIDE (   WWDG_IRQHandler = 0 ) ;
PROVIDE (   PVD_IRQHandler = 0 ) ;
PROVIDE (   TAMPER_IRQHandler = 0 ) ;
PROVIDE (   RTC_IRQHandler = 0 ) ;
PROVIDE (   FLASH_IRQHandler = 0 ) ;
PROVIDE (   RCC_IRQHandler = 0 ) ;
PROVIDE (   EXTI0_IRQHandler = 0 ) ;
PROVIDE (   EXTI1_IRQHandler = 0 ) ;
PROVIDE (   EXTI2_IRQHandler = 0 ) ;
PROVIDE (   EXTI3_IRQHandler = 0 ) ;
PROVIDE (   EXTI4_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel1_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel2_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel3_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel4_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel5_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel6_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel7_IRQHandler = 0 ) ;
PROVIDE (   ADC_IRQHandler = 0 ) ;
PROVIDE (   USB_HP_CAN_TX_IRQHandler = 0 ) ;
PROVIDE (   USB_LP_CAN_RX0_IRQHandler = 0 ) ;
PROVIDE (   CAN_RX1_IRQHandler = 0 ) ;
PROVIDE (   CAN_SCE_IRQHandler = 0 ) ;
PROVIDE (   EXTI9_5_IRQHandler = 0 ) ;
PROVIDE (   TIM1_BRK_IRQHandler = 0 ) ;
PROVIDE (   TIM1_UP_IRQHandler = 0 ) ;
PROVIDE (   TIM1_TRG_COM_IRQHandler = 0 ) ;
PROVIDE (   TIM1_CC_IRQHandler = 0 ) ;
PROVIDE (   TIM2_IRQHandler = 0 ) ;
PROVIDE (   TIM3_IRQHandler = 0 ) ;
PROVIDE (   TIM4_IRQHandler = 0 ) ;
PROVIDE (   I2C1_EV_IRQHandler = 0 ) ;
PROVIDE (   I2C1_ER_IRQHandler = 0 ) ;
PROVIDE (   I2C2_EV_IRQHandler = 0 ) ;
PROVIDE (   I2C2_ER_IRQHandler = 0 ) ;
PROVIDE (   SPI1_IRQHandler = 0 ) ;
PROVIDE (   SPI2_IRQHandler = 0 ) ;
PROVIDE (   USART1_IRQHandler = 0 ) ;
PROVIDE (   USART2_IRQHandler = 0 ) ;
PROVIDE (   USART3_IRQHandler = 0 ) ;
PROVIDE (   EXTI15_10_IRQHandler = 0 ) ;
PROVIDE (   RTCAlarm_IRQHandler = 0 ) ;
PROVIDE (   USBWakeUp_IRQHandler = 0 ) ;

/*Peripheral memory map*/
PERIPH_BASE           = 0x40000000;
SRAM_BASE             = 0x20000000;
PERIPH_BB_BASE        = 0x42000000;
SRAM_BB_BASE          = 0x22000000;
/* Flash registers base address */
PROVIDE ( FLASH_BASE            = 0x40022000);
/* Flash Option Bytes base address */
PROVIDE ( OB_BASE               = 0x1FFFF800);
/* Peripheral memory map */
APB1PERIPH_BASE      = PERIPH_BASE  ;
APB2PERIPH_BASE      = (PERIPH_BASE + 0x10000) ;
AHBPERIPH_BASE       = (PERIPH_BASE + 0x20000) ;

PROVIDE ( TIM2            = (APB1PERIPH_BASE + 0x0000) ) ;
PROVIDE ( TIM3            = (APB1PERIPH_BASE + 0x0400) ) ;
PROVIDE ( TIM4            = (APB1PERIPH_BASE + 0x0800) ) ;
PROVIDE ( TIM5            = (APB1PERIPH_BASE + 0x0C00) ) ;
PROVIDE ( TIM6            = (APB1PERIPH_BASE + 0x1000) ) ;
PROVIDE ( TIM7            = (APB1PERIPH_BASE + 0x1400) ) ;
PROVIDE ( RTC             = (APB1PERIPH_BASE + 0x2800) ) ;
PROVIDE ( WWDG            = (APB1PERIPH_BASE + 0x2C00) ) ;
PROVIDE ( IWDG            = (APB1PERIPH_BASE + 0x3000) ) ;
PROVIDE ( SPI2            = (APB1PERIPH_BASE + 0x3800) ) ;
PROVIDE ( USART2          = (APB1PERIPH_BASE + 0x4400) ) ;
PROVIDE ( USART3          = (APB1PERIPH_BASE + 0x4800) ) ;
PROVIDE ( UART4           = (APB1PERIPH_BASE + 0x4C00) ) ;
PROVIDE ( UART5           = (APB1PERIPH_BASE + 0x5000) ) ;
PROVIDE ( I2C1            = (APB1PERIPH_BASE + 0x5400) ) ;
PROVIDE ( I2C2            = (APB1PERIPH_BASE + 0x5800) ) ;
PROVIDE ( USB             = (APB1PERIPH_BASE + 0x5C00) ) ;
PROVIDE ( CAN             = (APB1PERIPH_BASE + 0x6400) ) ;
PROVIDE ( BKP             = (APB1PERIPH_BASE + 0x6C00) ) ;
PROVIDE ( PWR             = (APB1PERIPH_BASE + 0x7000) ) ;

PROVIDE ( AFIO            = (APB2PERIPH_BASE + 0x0000) ) ;
PROVIDE ( EXTI            = (APB2PERIPH_BASE + 0x0400) ) ;
PROVIDE ( GPIOA           = (APB2PERIPH_BASE + 0x0800) ) ;
PROVIDE ( GPIOB           = (APB2PERIPH_BASE + 0x0C00) ) ;
PROVIDE ( GPIOC           = (APB2PERIPH_BASE + 0x1000) ) ;
PROVIDE ( GPIOD           = (APB2PERIPH_BASE + 0x1400) ) ;
PROVIDE ( GPIOE           = (APB2PERIPH_BASE + 0x1800) ) ;
PROVIDE ( ADC1            = (APB2PERIPH_BASE + 0x2400) ) ;
PROVIDE ( ADC2            = (APB2PERIPH_BASE + 0x2800) ) ;
PROVIDE ( TIM1            = (APB2PERIPH_BASE + 0x2C00) ) ;
PROVIDE ( SPI1            = (APB2PERIPH_BASE + 0x3000) ) ;
PROVIDE ( TIM8            = (APB2PERIPH_BASE + 0x3400) ) ;
PROVIDE ( USART1          = (APB2PERIPH_BASE + 0x3800) ) ;
PROVIDE ( ADC3            = (APB2PERIPH_BASE + 0x3C00) ) ;
PROVIDE ( SDIO            = (APB2PERIPH_BASE + 0x8000) ) ;

PROVIDE ( DMA             = (AHBPERIPH_BASE + 0x0000) ) ;
PROVIDE ( DMA_Channel1    = (AHBPERIPH_BASE + 0x0008) ) ;
PROVIDE ( DMA_Channel2    = (AHBPERIPH_BASE + 0x001C) ) ;
PROVIDE ( DMA_Channel3    = (AHBPERIPH_BASE + 0x0030) ) ;
PROVIDE ( DMA_Channel4    = (AHBPERIPH_BASE + 0x0044) ) ;
PROVIDE ( DMA_Channel5    = (AHBPERIPH_BASE + 0x0058) ) ;
PROVIDE ( DMA_Channel6    = (AHBPERIPH_BASE + 0x006C) ) ;
PROVIDE ( DMA_Channel7    = (AHBPERIPH_BASE + 0x0080) ) ;
PROVIDE ( RCC             = (AHBPERIPH_BASE + 0x1000) ) ;

/* System Control Space memory map */
SCS_BASE              = 0xE000E000;

PROVIDE ( SysTick         = (SCS_BASE + 0x0010) ) ;
PROVIDE ( NVIC            = (SCS_BASE + 0x0100) ) ;
PROVIDE ( SCB             = (SCS_BASE + 0x0D00) ) ;

/* Memory Spaces Definitions */
MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 60K  /* also change _estack below */
  /*↓書込の方法に合わせてコメントアウトする*/
/*FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 512K*/ /* ※JTAGなどを使用する場合 */
  FLASH (rx) : ORIGIN = 0x8003000, LENGTH = 500K   /* ※DfuSeを使用する場合 */
  FLASHB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB0 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB2 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB3 (rx) : ORIGIN = 0x00000000, LENGTH = 0
}

/* highest address of the user mode stack */
_estack = 0x2000f000;

/* Sections Definitions */
SECTIONS
{
    .isr_vector :
    {
	. = ALIGN(4);
        KEEP(*(.isr_vector)) 
	. = ALIGN(4);
    } >FLASH
 
    .flashtext :
    {
	. = ALIGN(4);
        *(.flashtext)
	. = ALIGN(4);
    } >FLASH
     
    .text :
    {
	    . = ALIGN(4);
	    
        ./src/main.o(.text.)
        *(.text) 
        *(.text.*)
        *(.rodata)
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)

	    . = ALIGN(4);
   	 _etext = .;

   	 _sidata = _etext;
    } >FLASH
    
    .data  : AT ( _sidata )
    {
	    . = ALIGN(4);
        _sdata = . ;
        
        *(.data)
        *(.data.*)

	    . = ALIGN(4);
   	 _edata = . ;
    } >RAM
    
    .bss :
    {
	    . = ALIGN(4);
        _sbss = .;
        
        *(.bss)
        *(COMMON)
        
	    . = ALIGN(4);
   	 _ebss = . ;
    } >RAM
    
    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    
    ._usrstack :
    {
	    . = ALIGN(4);
        _susrstack = . ;
        
        . = . + _Minimum_Stack_Size ;
        
	    . = ALIGN(4);
        _eusrstack = . ;
    } >RAM
    
    .b1text :
    {
        *(.b1text)
        *(.b1rodata)
        *(.b1rodata*)
    } >FLASHB1
        
    .eb0text :
    {
        *(.eb0text)
        *(.eb0rodata) 
        *(.eb0rodata*)
    } >EXTMEMB0
    
    .eb1text :
    {
        *(.eb1text)
        *(.eb1rodata)
        *(.eb1rodata*)
    } >EXTMEMB1
    
    .eb2text :
    {
        *(.eb2text)
        *(.eb2rodata)
        *(.eb2rodata*)
    } >EXTMEMB2
    
    /* EXTMEM Bank0 */
    .eb3text :
    {
        *(.eb3text)
        *(.eb3rodata)
        *(.eb3rodata*)
    } >EXTMEMB3
    
    __exidx_start = .;
    __exidx_end = .;
    
/* remove the debugging information from the standard libraries */
/*  /DISCARD/ :
    {
     libc.a ( * )
     libm.a ( * )
     libgcc.a ( * )
     }
*/
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }

    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }

    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }

    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }

    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }

    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}



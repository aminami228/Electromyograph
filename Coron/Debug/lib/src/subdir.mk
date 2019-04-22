################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/coron_ad.c \
../lib/src/coron_dc.c \
../lib/src/coron_init.c \
../lib/src/coron_rc.c \
../lib/src/coron_sdfat.c \
../lib/src/coron_sdtxt.c \
../lib/src/coron_sdwav.c \
../lib/src/coron_sound.c \
../lib/src/coron_uart.c \
../lib/src/coron_usbcdc.c \
../lib/src/coron_usbprint.c \
../lib/src/coron_wait.c \
../lib/src/sdcard.c \
../lib/src/stm32f10x_adc.c \
../lib/src/stm32f10x_dac.c \
../lib/src/stm32f10x_dma.c \
../lib/src/stm32f10x_exti.c \
../lib/src/stm32f10x_flash.c \
../lib/src/stm32f10x_gpio.c \
../lib/src/stm32f10x_i2c.c \
../lib/src/stm32f10x_lib.c \
../lib/src/stm32f10x_nvic.c \
../lib/src/stm32f10x_rcc.c \
../lib/src/stm32f10x_sdio.c \
../lib/src/stm32f10x_spi.c \
../lib/src/stm32f10x_systick.c \
../lib/src/stm32f10x_tim.c \
../lib/src/stm32f10x_usart.c \
../lib/src/stm32f10x_vector.c \
../lib/src/syscalls.c \
../lib/src/usb_core.c \
../lib/src/usb_desc.c \
../lib/src/usb_endp.c \
../lib/src/usb_init.c \
../lib/src/usb_int.c \
../lib/src/usb_istr.c \
../lib/src/usb_mem.c \
../lib/src/usb_prop.c \
../lib/src/usb_pwr.c \
../lib/src/usb_regs.c 

S_SRCS += \
../lib/src/cortexm3_macro.s 

OBJS += \
./lib/src/coron_ad.o \
./lib/src/coron_dc.o \
./lib/src/coron_init.o \
./lib/src/coron_rc.o \
./lib/src/coron_sdfat.o \
./lib/src/coron_sdtxt.o \
./lib/src/coron_sdwav.o \
./lib/src/coron_sound.o \
./lib/src/coron_uart.o \
./lib/src/coron_usbcdc.o \
./lib/src/coron_usbprint.o \
./lib/src/coron_wait.o \
./lib/src/cortexm3_macro.o \
./lib/src/sdcard.o \
./lib/src/stm32f10x_adc.o \
./lib/src/stm32f10x_dac.o \
./lib/src/stm32f10x_dma.o \
./lib/src/stm32f10x_exti.o \
./lib/src/stm32f10x_flash.o \
./lib/src/stm32f10x_gpio.o \
./lib/src/stm32f10x_i2c.o \
./lib/src/stm32f10x_lib.o \
./lib/src/stm32f10x_nvic.o \
./lib/src/stm32f10x_rcc.o \
./lib/src/stm32f10x_sdio.o \
./lib/src/stm32f10x_spi.o \
./lib/src/stm32f10x_systick.o \
./lib/src/stm32f10x_tim.o \
./lib/src/stm32f10x_usart.o \
./lib/src/stm32f10x_vector.o \
./lib/src/syscalls.o \
./lib/src/usb_core.o \
./lib/src/usb_desc.o \
./lib/src/usb_endp.o \
./lib/src/usb_init.o \
./lib/src/usb_int.o \
./lib/src/usb_istr.o \
./lib/src/usb_mem.o \
./lib/src/usb_prop.o \
./lib/src/usb_pwr.o \
./lib/src/usb_regs.o 

C_DEPS += \
./lib/src/coron_ad.d \
./lib/src/coron_dc.d \
./lib/src/coron_init.d \
./lib/src/coron_rc.d \
./lib/src/coron_sdfat.d \
./lib/src/coron_sdtxt.d \
./lib/src/coron_sdwav.d \
./lib/src/coron_sound.d \
./lib/src/coron_uart.d \
./lib/src/coron_usbcdc.d \
./lib/src/coron_usbprint.d \
./lib/src/coron_wait.d \
./lib/src/sdcard.d \
./lib/src/stm32f10x_adc.d \
./lib/src/stm32f10x_dac.d \
./lib/src/stm32f10x_dma.d \
./lib/src/stm32f10x_exti.d \
./lib/src/stm32f10x_flash.d \
./lib/src/stm32f10x_gpio.d \
./lib/src/stm32f10x_i2c.d \
./lib/src/stm32f10x_lib.d \
./lib/src/stm32f10x_nvic.d \
./lib/src/stm32f10x_rcc.d \
./lib/src/stm32f10x_sdio.d \
./lib/src/stm32f10x_spi.d \
./lib/src/stm32f10x_systick.d \
./lib/src/stm32f10x_tim.d \
./lib/src/stm32f10x_usart.d \
./lib/src/stm32f10x_vector.d \
./lib/src/syscalls.d \
./lib/src/usb_core.d \
./lib/src/usb_desc.d \
./lib/src/usb_endp.d \
./lib/src/usb_init.d \
./lib/src/usb_int.d \
./lib/src/usb_istr.d \
./lib/src/usb_mem.d \
./lib/src/usb_prop.d \
./lib/src/usb_pwr.d \
./lib/src/usb_regs.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o: ../lib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-none-eabi-gcc -I../inc -I../lib/inc -O0 -g -Wall -c -fmessage-length=0 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

lib/src/%.o: ../lib/src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	arm-none-eabi-as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



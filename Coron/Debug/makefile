################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include lib/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main.elf

# Tool invocations
main.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C Linker'
	arm-none-eabi-gcc -L"C:\coron\gcc\arm\arm-none-eabi\lib\thumb2" -L"C:\coron\gcc\arm\lib\gcc\arm-none-eabi\4.3.3\thumb2" -Xlinker --wrap -Xlinker malloc -Xlinker --wrap -Xlinker realloc -Xlinker --wrap -Xlinker calloc -Xlinker --wrap -Xlinker free -Xlinker --gc-sections -Xlinker -Map=link.map -Xlinker -cref -Xlinker -u -Xlinker Reset_Handler -Xlinker -T../ld_script/coron_ld_sclipt.ld -o"main.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) main.elf
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -O ihex main.elf main.hex
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

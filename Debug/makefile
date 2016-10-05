################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: blink.elf

dependents:
	-cd C:/Users/Obelisk/Desktop/stm32f4discoworkspace/stm32f411e-disco_hal_lib/Debug && $(MAKE) clean all

# Tool invocations
blink.elf: $(OBJS) $(USER_OBJS) C:/Users/Obelisk/Desktop/stm32f4discoworkspace/stm32f411e-disco_hal_lib/Debug/libstm32f411e-disco_hal_lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -L"C:\Users\Obelisk\Desktop\stm32f4discoworkspace\stm32f411e-disco_hal_lib\Debug" -T"C:\Users\Obelisk\Desktop\stm32f4discoworkspace\blink\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "blink.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "blink.elf" "blink.bin"
	arm-none-eabi-size "blink.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/Obelisk/Desktop/stm32f4discoworkspace/stm32f411e-disco_hal_lib/Debug/libstm32f411e-disco_hal_lib.a:

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/App/src/BootLoader.c \
../src/App/src/UDS.c 

OBJS += \
./src/App/src/BootLoader.o \
./src/App/src/UDS.o 

C_DEPS += \
./src/App/src/BootLoader.d \
./src/App/src/UDS.d 


# Each subdirectory must supply rules for building sources it contributes
src/App/src/%.o: ../src/App/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\LIB" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\App\include" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\Driver\include" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\HAL\include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



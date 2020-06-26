################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Driver/src/DGPIO.c \
../src/Driver/src/DMA.c \
../src/Driver/src/DMA_Cfg.c \
../src/Driver/src/DNVIC.c \
../src/Driver/src/DRCC.c \
../src/Driver/src/FLITF.c \
../src/Driver/src/UART.c 

OBJS += \
./src/Driver/src/DGPIO.o \
./src/Driver/src/DMA.o \
./src/Driver/src/DMA_Cfg.o \
./src/Driver/src/DNVIC.o \
./src/Driver/src/DRCC.o \
./src/Driver/src/FLITF.o \
./src/Driver/src/UART.o 

C_DEPS += \
./src/Driver/src/DGPIO.d \
./src/Driver/src/DMA.d \
./src/Driver/src/DMA_Cfg.d \
./src/Driver/src/DNVIC.d \
./src/Driver/src/DRCC.d \
./src/Driver/src/FLITF.d \
./src/Driver/src/UART.d 


# Each subdirectory must supply rules for building sources it contributes
src/Driver/src/%.o: ../src/Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\LIB" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\App\include" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\Driver\include" -I"C:\Users\toshiba\Downloads\ITI\Turkey\Turkey WS\UDS\src\HAL\include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DGPIO.c \
../src/DNVIC.c \
../src/DRCC.c \
../src/DSYSTICK.c \
../src/EXT_INT.c \
../src/EXT_INT_cfg.c \
../src/Sched.c \
../src/Sched_config.c \
../src/main.c 

OBJS += \
./src/DGPIO.o \
./src/DNVIC.o \
./src/DRCC.o \
./src/DSYSTICK.o \
./src/EXT_INT.o \
./src/EXT_INT_cfg.o \
./src/Sched.o \
./src/Sched_config.o \
./src/main.o 

C_DEPS += \
./src/DGPIO.d \
./src/DNVIC.d \
./src/DRCC.d \
./src/DSYSTICK.d \
./src/EXT_INT.d \
./src/EXT_INT_cfg.d \
./src/Sched.d \
./src/Sched_config.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



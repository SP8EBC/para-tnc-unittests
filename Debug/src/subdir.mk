################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/analog_anemometer.c \
../src/tx20.c \
../src/wx_handler.c 

OBJS += \
./src/analog_anemometer.o \
./src/tx20.o \
./src/wx_handler.o 

C_DEPS += \
./src/analog_anemometer.d \
./src/tx20.d \
./src/wx_handler.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_HD_VL -D_ANEMOMETER_ANALOGUE -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/include" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/stm32f1-stdperiph" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/inc" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/drivers" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/stubs" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



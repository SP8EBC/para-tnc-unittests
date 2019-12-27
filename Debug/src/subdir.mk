################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TX20_test.cpp 

C_SRCS += \
../src/analog_anemometer.c \
../src/main_subs.c \
../src/rte_wx_stubs.c \
../src/stdperiph_stubs.c \
../src/tx20.c \
../src/wx_handler_stubs.c 

OBJS += \
./src/TX20_test.o \
./src/analog_anemometer.o \
./src/main_subs.o \
./src/rte_wx_stubs.o \
./src/stdperiph_stubs.o \
./src/tx20.o \
./src/wx_handler_stubs.o 

CPP_DEPS += \
./src/TX20_test.d 

C_DEPS += \
./src/analog_anemometer.d \
./src/main_subs.d \
./src/rte_wx_stubs.d \
./src/stdperiph_stubs.d \
./src/tx20.d \
./src/wx_handler_stubs.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DSTM32F10X_HD_VL -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/stm32f1-stdperiph" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_HD_VL -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/include" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/stm32f1-stdperiph" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



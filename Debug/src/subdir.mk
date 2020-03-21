################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/analoganemometer_test.cpp 

C_SRCS += \
../src/_dht22_stubs.c \
../src/analog_anemometer.c \
../src/dallas_stubs.c \
../src/main_subs.c \
../src/ms5611_stubs.c \
../src/other_stubs.c \
../src/rte_wx_stubs.c \
../src/serial_stubs.c \
../src/stdperiph_stubs.c \
../src/tx20.c \
../src/wx_handler.c \
../src/wx_handler_stubs.c 

OBJS += \
./src/_dht22_stubs.o \
./src/analog_anemometer.o \
./src/analoganemometer_test.o \
./src/dallas_stubs.o \
./src/main_subs.o \
./src/ms5611_stubs.o \
./src/other_stubs.o \
./src/rte_wx_stubs.o \
./src/serial_stubs.o \
./src/stdperiph_stubs.o \
./src/tx20.o \
./src/wx_handler.o \
./src/wx_handler_stubs.o 

CPP_DEPS += \
./src/analoganemometer_test.d 

C_DEPS += \
./src/_dht22_stubs.d \
./src/analog_anemometer.d \
./src/dallas_stubs.d \
./src/main_subs.d \
./src/ms5611_stubs.d \
./src/other_stubs.d \
./src/rte_wx_stubs.d \
./src/serial_stubs.d \
./src/stdperiph_stubs.d \
./src/tx20.d \
./src/wx_handler.d \
./src/wx_handler_stubs.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_HD_VL -D_ANEMOMETER_ANALOGUE -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/include" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/inc" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/drivers" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/stm32f1-stdperiph" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DSTM32F10X_HD_VL -D_ANEMOMETER_ANALOGUE -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/drivers" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC_unit_tests/src/inc" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC/system/include/stm32f1-stdperiph" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TX20_test.cpp 

C_SRCS += \
../src/stdperiph_stubs.c \
../src/tx20.c 

OBJS += \
./src/TX20_test.o \
./src/stdperiph_stubs.o \
./src/tx20.o 

CPP_DEPS += \
./src/TX20_test.d 

C_DEPS += \
./src/stdperiph_stubs.d \
./src/tx20.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DSTM32F10X_HD_VL -I"/home/mateusz/Dokumenty/___STM32/ParaTNC-ARM-lite/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC-ARM-lite/system/include/stm32f1-stdperiph" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_HD_VL -I"/home/mateusz/Dokumenty/___STM32/ParaTNC-ARM-lite/include" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC-ARM-lite/system/include/stm32f1-stdperiph" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC-ARM-lite/system/include/cmsis" -I"/home/mateusz/Dokumenty/___STM32/ParaTNC-ARM-lite/system/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



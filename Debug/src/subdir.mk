################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/analog_anemometer.c \
../src/davis_parsers.c \
../src/io.c 

OBJS += \
./src/analog_anemometer.o \
./src/davis_parsers.o \
./src/io.o 

C_DEPS += \
./src/analog_anemometer.d \
./src/davis_parsers.d \
./src/io.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_MD_VL -D_ANEMOMETER_ANALOGUE -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/drivers" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/stubs" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



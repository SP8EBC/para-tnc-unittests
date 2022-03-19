################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/analog_anemometer.c \
../src/davis_parsers.c \
../src/http_client_rx_callback.c \
../src/io.c \
../src/sim800c.c \
../src/sim800c_engineering.c \
../src/sim800c_gprs.c \
../src/sim800c_poolers.c 

OBJS += \
./src/analog_anemometer.o \
./src/davis_parsers.o \
./src/http_client_rx_callback.o \
./src/io.o \
./src/sim800c.o \
./src/sim800c_engineering.o \
./src/sim800c_gprs.o \
./src/sim800c_poolers.o 

C_DEPS += \
./src/analog_anemometer.d \
./src/davis_parsers.d \
./src/http_client_rx_callback.d \
./src/io.d \
./src/sim800c.d \
./src/sim800c_engineering.d \
./src/sim800c_gprs.d \
./src/sim800c_poolers.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_MD_VL -D_ANEMOMETER_ANALOGUE -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/drivers" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/stubs" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



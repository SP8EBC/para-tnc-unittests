################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/analog_anemometer.c \
../src/aprsis.c \
../src/davis_parsers.c \
../src/float_to_string.c \
../src/io.c \
../src/kiss_communication_aprsmsg.c \
../src/sim800c.c \
../src/sim800c_engineering.c \
../src/sim800c_gprs.c \
../src/sim800c_poolers.c 

C_DEPS += \
./src/analog_anemometer.d \
./src/aprsis.d \
./src/davis_parsers.d \
./src/float_to_string.d \
./src/io.d \
./src/kiss_communication_aprsmsg.d \
./src/sim800c.d \
./src/sim800c_engineering.d \
./src/sim800c_gprs.d \
./src/sim800c_poolers.d 

OBJS += \
./src/analog_anemometer.o \
./src/aprsis.o \
./src/davis_parsers.o \
./src/float_to_string.o \
./src/io.o \
./src/kiss_communication_aprsmsg.o \
./src/sim800c.o \
./src/sim800c_engineering.o \
./src/sim800c_gprs.o \
./src/sim800c_poolers.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DSTM32F10X_MD_VL -DUNIT_TEST -D_ANEMOMETER_ANALOGUE -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/drivers" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/___stubs___" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/___memory_map___" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/inc" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/etc" -I"/home/mateusz/Documents/___STM32/ParaTNC_unit_tests/src/aprs" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/analog_anemometer.d ./src/analog_anemometer.o ./src/aprsis.d ./src/aprsis.o ./src/davis_parsers.d ./src/davis_parsers.o ./src/float_to_string.d ./src/float_to_string.o ./src/io.d ./src/io.o ./src/kiss_communication_aprsmsg.d ./src/kiss_communication_aprsmsg.o ./src/sim800c.d ./src/sim800c.o ./src/sim800c_engineering.d ./src/sim800c_engineering.o ./src/sim800c_gprs.d ./src/sim800c_gprs.o ./src/sim800c_poolers.d ./src/sim800c_poolers.o

.PHONY: clean-src


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/gpio.cpp \
../source/main.cpp \
../source/render.cpp 

C_SRCS += \
../source/SimpleGPIO.c 

OBJS += \
./source/SimpleGPIO.o \
./source/gpio.o \
./source/main.o \
./source/render.o 

C_DEPS += \
./source/SimpleGPIO.d 

CPP_DEPS += \
./source/gpio.d \
./source/main.d \
./source/render.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-linux-gnueabihf-gcc-4.6 -I/usr/arm-linux-gnueabihf/include/xenomai/include -I/usr/arm-gcc/arm-linux-gnueabihf/include -I/usr/arm-linux-gnueabihf/include/ne10 -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include/xenomai/include -O2 -g3 -Wall -c -fmessage-length=0 -Wpointer-arith -Wunused-result  -D_GNU_SOURCE -D_REENTRANT -D__XENO__ -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-gnueabihf-g++ -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include/xenomai/include -I/usr/arm-linux-gnueabihf/include/xenomai/include -I/usr/arm-linux-gnueabihf/include -I/usr/arm-linux-gnueabihf/include/ne10 -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include -O2 -g3 -Wall -c -fmessage-length=0 -Wpointer-arith -Wunused-result -D_GNU_SOURCE -D_REENTRANT -D__XENO__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



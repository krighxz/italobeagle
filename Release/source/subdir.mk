################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/gpio.cpp \
../source/main.cpp \
../source/render.cpp 

C_SRCS += \
../source/ControlBinop.c \
../source/ControlCast.c \
../source/ControlDelay.c \
../source/ControlIf.c \
../source/ControlRandom.c \
../source/ControlSlice.c \
../source/ControlSystem.c \
../source/ControlUnop.c \
../source/ControlVar.c \
../source/Heavy.c \
../source/HvBase.c \
../source/HvContext_beagleSequencer.c \
../source/HvMessage.c \
../source/HvTable.c \
../source/MessagePool.c \
../source/MessageQueue.c \
../source/SignalBiquad.c \
../source/SignalLine.c \
../source/SignalPhasor.c \
../source/SignalTabread.c \
../source/SignalVar.c \
../source/SimpleGPIO.c \
../source/Utils_mac.c \
../source/Utils_unix.c \
../source/Utils_windows.c 

OBJS += \
./source/ControlBinop.o \
./source/ControlCast.o \
./source/ControlDelay.o \
./source/ControlIf.o \
./source/ControlRandom.o \
./source/ControlSlice.o \
./source/ControlSystem.o \
./source/ControlUnop.o \
./source/ControlVar.o \
./source/Heavy.o \
./source/HvBase.o \
./source/HvContext_beagleSequencer.o \
./source/HvMessage.o \
./source/HvTable.o \
./source/MessagePool.o \
./source/MessageQueue.o \
./source/SignalBiquad.o \
./source/SignalLine.o \
./source/SignalPhasor.o \
./source/SignalTabread.o \
./source/SignalVar.o \
./source/SimpleGPIO.o \
./source/Utils_mac.o \
./source/Utils_unix.o \
./source/Utils_windows.o \
./source/gpio.o \
./source/main.o \
./source/render.o 

C_DEPS += \
./source/ControlBinop.d \
./source/ControlCast.d \
./source/ControlDelay.d \
./source/ControlIf.d \
./source/ControlRandom.d \
./source/ControlSlice.d \
./source/ControlSystem.d \
./source/ControlUnop.d \
./source/ControlVar.d \
./source/Heavy.d \
./source/HvBase.d \
./source/HvContext_beagleSequencer.d \
./source/HvMessage.d \
./source/HvTable.d \
./source/MessagePool.d \
./source/MessageQueue.d \
./source/SignalBiquad.d \
./source/SignalLine.d \
./source/SignalPhasor.d \
./source/SignalTabread.d \
./source/SignalVar.d \
./source/SimpleGPIO.d \
./source/Utils_mac.d \
./source/Utils_unix.d \
./source/Utils_windows.d 

CPP_DEPS += \
./source/gpio.d \
./source/main.d \
./source/render.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	arm-linux-gnueabihf-gcc -DHV_SIMD_NONE -I/usr/arm-linux-gnueabihf/include -I/usr/arm-linux-gnueabihf/include/xenomai/include -I/usr/arm-gcc/arm-linux-gnueabihf/include -I/usr/arm-linux-gnueabihf/include/ne10 -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include/xenomai/include -I/usr/arm-linux-gnueabihf/include/xenomai/include -O2 -Wall -c -fmessage-length=0 -std=c99 -D_POSIX_C_SOURCE=199309L -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-linux-gnueabihf-g++ -DHV_SIMD_NONE -I/usr/arm-linux-gnueabihf/include/xenomai/include -I/usr/arm-linux-gnueabihf/include -I/usr/arm-linux-gnueabihf/include/ne10 -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include/xenomai/include -I/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/include -O2 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir.mk
-include core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: assignment2_drums

# Tool invocations
assignment2_drums: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	arm-linux-gnueabihf-g++ -L/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/lib -L/usr/arm-linux-gnueabihf/lib -L/usr/arm-linux-gnueabihf/lib/xenomai -L/import/teaching/ECS732/arm-gcc/arm-linux-gnueabihf/lib/xenomai -pthread -rdynamics -o "assignment2_drums" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) assignment2_drums
	-@echo ' '

post-build:
	-@echo 'Kills the process running on the BeagleBone (if any) and copies the new binary to the BeagleBone in beaglert/'
	-ssh -t root@192.168.7.2 "kill -s 2 \`pidof assignment2_drums\` 2>/dev/null"; scp assignment2_drums root@192.168.7.2:~/beaglert/
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

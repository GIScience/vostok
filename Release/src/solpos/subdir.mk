################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/solpos/solpos.cpp 

OBJS += \
./src/solpos/solpos.o 

CPP_DEPS += \
./src/solpos/solpos.d 


# Each subdirectory must supply rules for building sources it contributes
src/solpos/%.o: ../src/solpos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



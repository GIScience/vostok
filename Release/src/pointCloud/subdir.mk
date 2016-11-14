################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/pointCloud/AbstractPointCloud.cpp \
../src/pointCloud/SimpleTextPointCloud.cpp 

OBJS += \
./src/pointCloud/AbstractPointCloud.o \
./src/pointCloud/SimpleTextPointCloud.o 

CPP_DEPS += \
./src/pointCloud/AbstractPointCloud.d \
./src/pointCloud/SimpleTextPointCloud.d 


# Each subdirectory must supply rules for building sources it contributes
src/pointCloud/%.o: ../src/pointCloud/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



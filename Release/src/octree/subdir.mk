################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/octree/Octree.cpp \
../src/octree/OctreeNode.cpp \
../src/octree/OctreeNodeInfo.cpp 

OBJS += \
./src/octree/Octree.o \
./src/octree/OctreeNode.o \
./src/octree/OctreeNodeInfo.o 

CPP_DEPS += \
./src/octree/Octree.d \
./src/octree/OctreeNode.d \
./src/octree/OctreeNodeInfo.d 


# Each subdirectory must supply rules for building sources it contributes
src/octree/%.o: ../src/octree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



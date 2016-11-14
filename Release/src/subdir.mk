################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IrradianceCalc.cpp \
../src/OctreeRaycaster.cpp \
../src/ProjectConfig.cpp \
../src/ShadowCalc.cpp \
../src/Vec3d.cpp \
../src/main.cpp 

OBJS += \
./src/IrradianceCalc.o \
./src/OctreeRaycaster.o \
./src/ProjectConfig.o \
./src/ShadowCalc.o \
./src/Vec3d.o \
./src/main.o 

CPP_DEPS += \
./src/IrradianceCalc.d \
./src/OctreeRaycaster.d \
./src/ProjectConfig.d \
./src/ShadowCalc.d \
./src/Vec3d.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



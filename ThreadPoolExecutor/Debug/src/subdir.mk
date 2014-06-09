################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CThread.cpp \
../src/CThreadFactory.cpp \
../src/Driver.cpp \
../src/ThreadDirector.cpp \
../src/ThreadPoolExecutor.cpp \
../src/Threader.cpp \
../src/main.cpp 

OBJS += \
./src/CThread.o \
./src/CThreadFactory.o \
./src/Driver.o \
./src/ThreadDirector.o \
./src/ThreadPoolExecutor.o \
./src/Threader.o \
./src/main.o 

CPP_DEPS += \
./src/CThread.d \
./src/CThreadFactory.d \
./src/Driver.d \
./src/ThreadDirector.d \
./src/ThreadPoolExecutor.d \
./src/Threader.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -pthread -std=c++0x -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



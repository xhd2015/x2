################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AssociatedMemoryManager.cpp \
../src/Cache.cpp \
../src/Descriptor.cpp \
../src/IOProgramer.cpp \
../src/Kernel.cpp \
../src/List.cpp \
../src/Locator.cpp \
../src/MemoryManager.cpp \
../src/PMLoader.cpp \
../src/Process.cpp \
../src/TSS.cpp \
../src/UserProcess.cpp \
../src/VirtualMemory.cpp \
../src/idleProcess.cpp \
../src/interrupts.cpp \
../src/libx2.cpp \
../src/main.cpp \
../src/protected_main.cpp \
../src/test.cpp 

OBJS += \
./src/AssociatedMemoryManager.o \
./src/Cache.o \
./src/Descriptor.o \
./src/IOProgramer.o \
./src/Kernel.o \
./src/List.o \
./src/Locator.o \
./src/MemoryManager.o \
./src/PMLoader.o \
./src/Process.o \
./src/TSS.o \
./src/UserProcess.o \
./src/VirtualMemory.o \
./src/idleProcess.o \
./src/interrupts.o \
./src/libx2.o \
./src/main.o \
./src/protected_main.o \
./src/test.o 

CPP_DEPS += \
./src/AssociatedMemoryManager.d \
./src/Cache.d \
./src/Descriptor.d \
./src/IOProgramer.d \
./src/Kernel.d \
./src/List.d \
./src/Locator.d \
./src/MemoryManager.d \
./src/PMLoader.d \
./src/Process.d \
./src/TSS.d \
./src/UserProcess.d \
./src/VirtualMemory.d \
./src/idleProcess.d \
./src/interrupts.d \
./src/libx2.d \
./src/main.d \
./src/protected_main.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++11 -nostdinc -DCODE32 -DIDE_MODE -I"C:\Users\13774\Desktop\old_desktop\bochs\devel\x2 system\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



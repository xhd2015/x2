################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/64/MallocToSimple.cpp 

OBJS += \
./src/64/MallocToSimple.o 

CPP_DEPS += \
./src/64/MallocToSimple.d 


# Each subdirectory must supply rules for building sources it contributes
src/64/%.o: ../src/64/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++11 -nostdinc -DCODE32 -DIDE_MODE -I"C:\Users\13774\Desktop\old_desktop\bochs\devel\x2 system\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



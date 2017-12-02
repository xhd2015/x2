################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test_inc.cpp \
../src/test_multiple_file_instantiate.cpp 

OBJS += \
./src/test_inc.o \
./src/test_multiple_file_instantiate.o 

CPP_DEPS += \
./src/test_inc.d \
./src/test_multiple_file_instantiate.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++17 -DIDE_MODE -O0 -g3 -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test_functor_push_stack.cpp 

O_SRCS += \
../src/test_new_no_stdlib.o 

OBJS += \
./src/test_functor_push_stack.o 

CPP_DEPS += \
./src/test_functor_push_stack.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Werror -Wall -fno-exceptions -std=c++17 -DIDE_MODE -DCODE64 -I"C:\Users\13774\Desktop\old_desktop\bochs\devel\x2-system\include" -O3 -g3 -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



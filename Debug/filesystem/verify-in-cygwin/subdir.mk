################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../filesystem/verify-in-cygwin/CMDUtil.cpp \
../filesystem/verify-in-cygwin/File.cpp \
../filesystem/verify-in-cygwin/listFile.cpp \
../filesystem/verify-in-cygwin/mkfs.x2fs.cpp \
../filesystem/verify-in-cygwin/newFile.cpp 

OBJS += \
./filesystem/verify-in-cygwin/CMDUtil.o \
./filesystem/verify-in-cygwin/File.o \
./filesystem/verify-in-cygwin/listFile.o \
./filesystem/verify-in-cygwin/mkfs.x2fs.o \
./filesystem/verify-in-cygwin/newFile.o 

CPP_DEPS += \
./filesystem/verify-in-cygwin/CMDUtil.d \
./filesystem/verify-in-cygwin/File.d \
./filesystem/verify-in-cygwin/listFile.d \
./filesystem/verify-in-cygwin/mkfs.x2fs.d \
./filesystem/verify-in-cygwin/newFile.d 


# Each subdirectory must supply rules for building sources it contributes
filesystem/verify-in-cygwin/%.o: ../filesystem/verify-in-cygwin/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++11 -nostdinc -DCODE32 -DIDE_MODE -I"C:\Users\13774\Desktop\old_desktop\bochs\devel\x2 system\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



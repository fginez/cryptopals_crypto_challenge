################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/asc2hex.c \
../tests/fileops.c \
../tests/main.c \
../tests/printbuffer.c 

OBJS += \
./tests/asc2hex.o \
./tests/fileops.o \
./tests/main.o \
./tests/printbuffer.o 

C_DEPS += \
./tests/asc2hex.d \
./tests/fileops.d \
./tests/main.d \
./tests/printbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



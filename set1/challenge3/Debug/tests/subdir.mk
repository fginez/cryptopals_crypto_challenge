################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/sbxor_decode_test.c 

OBJS += \
./tests/sbxor_decode_test.o 

C_DEPS += \
./tests/sbxor_decode_test.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/capitao/Cryptochallenge/set1/challenge3" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



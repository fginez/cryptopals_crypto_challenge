################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testes/fixed_xor_test.c 

OBJS += \
./testes/fixed_xor_test.o 

C_DEPS += \
./testes/fixed_xor_test.d 


# Each subdirectory must supply rules for building sources it contributes
testes/%.o: ../testes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/capitao/cryptopals_crypto_challenge/set1/s1c2_fixedxor_test" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



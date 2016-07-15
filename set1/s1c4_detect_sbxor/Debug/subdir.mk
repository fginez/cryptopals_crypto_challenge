################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../asc2hex.c \
../printbuffer.c \
../sbxor_decode.c 

OBJS += \
./asc2hex.o \
./printbuffer.o \
./sbxor_decode.o 

C_DEPS += \
./asc2hex.d \
./printbuffer.d \
./sbxor_decode.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/capitao/cryptopals_crypto_challenge/set1/s1c4_detect_sbxor" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../break_repkxor.c \
../hamming_dist.c \
../hextob64.c \
../printbuffer.c \
../sbxor_decode.c 

OBJS += \
./break_repkxor.o \
./hamming_dist.o \
./hextob64.o \
./printbuffer.o \
./sbxor_decode.o 

C_DEPS += \
./break_repkxor.d \
./hamming_dist.d \
./hextob64.d \
./printbuffer.d \
./sbxor_decode.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/capitao/cryptopals_crypto_challenge/set1/s1c6_breakrepxor_hamming_test" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tests/break_repkxor_test.c \
../tests/fileops.c \
../tests/hamming_dist_test.c \
../tests/main.c 

OBJS += \
./tests/break_repkxor_test.o \
./tests/fileops.o \
./tests/hamming_dist_test.o \
./tests/main.o 

C_DEPS += \
./tests/break_repkxor_test.d \
./tests/fileops.d \
./tests/hamming_dist_test.d \
./tests/main.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/capitao/cryptopals_crypto_challenge/set1/s1c6_breakrepxor_hamming_test" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


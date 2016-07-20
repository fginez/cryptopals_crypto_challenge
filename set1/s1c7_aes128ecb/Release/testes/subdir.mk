################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../testes/fileops.c \
../testes/hextob64.c \
../testes/main.c \
../testes/printbuffer.c 

OBJS += \
./testes/fileops.o \
./testes/hextob64.o \
./testes/main.o \
./testes/printbuffer.o 

C_DEPS += \
./testes/fileops.d \
./testes/hextob64.d \
./testes/main.d \
./testes/printbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
testes/%.o: ../testes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



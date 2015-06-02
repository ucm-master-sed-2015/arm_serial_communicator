################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../44blib.c \
../button.c \
../main.c \
../timer.c \
../uart.c 

ASM_SRCS += \
../44binit.asm 

OBJS += \
./44binit.o \
./44blib.o \
./button.o \
./main.o \
./timer.o \
./uart.o 

C_DEPS += \
./44blib.d \
./button.d \
./main.d \
./timer.d \
./uart.d 

ASM_DEPS += \
./44binit.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -Os -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



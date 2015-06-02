################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../44blib.c \
../8led.c \
../button.c \
../keyboard.c \
../lcd.c \
../led.c \
../main.c \
../timer.c \
../uart.c 

ASM_SRCS += \
../44binit.asm 

OBJS += \
./44binit.o \
./44blib.o \
./8led.o \
./button.o \
./keyboard.o \
./lcd.o \
./led.o \
./main.o \
./timer.o \
./uart.o 

C_DEPS += \
./44blib.d \
./8led.d \
./button.d \
./keyboard.d \
./lcd.d \
./led.d \
./main.d \
./timer.d \
./uart.d 

ASM_DEPS += \
./44binit.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"C:\hlocal\EclipseARMwspace\proyectoARM\commonEclipse" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\hlocal\EclipseARMwspace\proyectoARM\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



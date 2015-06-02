################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../commonEclipse/44blib.c 

OBJS += \
./commonEclipse/44blib.o 

C_DEPS += \
./commonEclipse/44blib.d 


# Each subdirectory must supply rules for building sources it contributes
commonEclipse/%.o: ../commonEclipse/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\hlocal\EclipseARMwspace\practica4\commonEclipse" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../apps/UDP-app.c \
../apps/uip-app.c 

OBJS += \
./apps/UDP-app.o \
./apps/uip-app.o 

C_DEPS += \
./apps/UDP-app.d \
./apps/uip-app.d 


# Each subdirectory must supply rules for building sources it contributes
apps/%.o: ../apps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



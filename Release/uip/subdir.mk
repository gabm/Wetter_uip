################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uip/timer.c \
../uip/uip.c \
../uip/uip_arp.c 

OBJS += \
./uip/timer.o \
./uip/uip.o \
./uip/uip_arp.o 

C_DEPS += \
./uip/timer.d \
./uip/uip.d \
./uip/uip_arp.d 


# Each subdirectory must supply rules for building sources it contributes
uip/%.o: ../uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



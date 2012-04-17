################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/enc28j60.c \
../hardware/spi.c 

OBJS += \
./hardware/enc28j60.o \
./hardware/spi.o 

C_DEPS += \
./hardware/enc28j60.d \
./hardware/spi.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/%.o: ../hardware/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



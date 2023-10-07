################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Timer1.c \
../application.c \
../gpio.c \
../hmi_mc1_main.c \
../keypad.c \
../lcd.c \
../uart.c 

OBJS += \
./Timer1.o \
./application.o \
./gpio.o \
./hmi_mc1_main.o \
./keypad.o \
./lcd.o \
./uart.o 

C_DEPS += \
./Timer1.d \
./application.d \
./gpio.d \
./hmi_mc1_main.d \
./keypad.d \
./lcd.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



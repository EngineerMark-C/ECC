################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/encoder.c \
../code/flash.c \
../code/gps.c \
../code/imu.c \
../code/init.c \
../code/ipsShow.c \
../code/menu.c \
../code/motor.c \
../code/pid.c \
../code/sreer.c \
../code/uartReceiver.c 

C_DEPS += \
./code/encoder.d \
./code/flash.d \
./code/gps.d \
./code/imu.d \
./code/init.d \
./code/ipsShow.d \
./code/menu.d \
./code/motor.d \
./code/pid.d \
./code/sreer.d \
./code/uartReceiver.d 

OBJS += \
./code/encoder.o \
./code/flash.o \
./code/gps.o \
./code/imu.o \
./code/init.o \
./code/ipsShow.o \
./code/menu.o \
./code/motor.o \
./code/pid.o \
./code/sreer.o \
./code/uartReceiver.o 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-gcc -std=c99 "@D:/code/20/TC264_Library/Example/ECC/External GCC - Debug/AURIX_GCC_Compiler-Include_paths__-I_.opt" -O0 -g3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code

clean-code:
	-$(RM) ./code/encoder.d ./code/encoder.o ./code/flash.d ./code/flash.o ./code/gps.d ./code/gps.o ./code/imu.d ./code/imu.o ./code/init.d ./code/init.o ./code/ipsShow.d ./code/ipsShow.o ./code/menu.d ./code/menu.o ./code/motor.d ./code/motor.o ./code/pid.d ./code/pid.o ./code/sreer.d ./code/sreer.o ./code/uartReceiver.d ./code/uartReceiver.o

.PHONY: clean-code


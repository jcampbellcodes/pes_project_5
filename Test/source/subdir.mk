################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/circular_buffer.c \
../source/delay.c \
../source/handle_led.c \
../source/logger.c \
../source/mtb.c \
../source/post.c \
../source/semihost_hardfault.c \
../source/setup_teardown.c \
../source/uart.c 

OBJS += \
./source/circular_buffer.o \
./source/delay.o \
./source/handle_led.o \
./source/logger.o \
./source/mtb.o \
./source/post.o \
./source/semihost_hardfault.o \
./source/setup_teardown.o \
./source/uart.o 

C_DEPS += \
./source/circular_buffer.d \
./source/delay.d \
./source/handle_led.d \
./source/logger.d \
./source/mtb.d \
./source/post.d \
./source/semihost_hardfault.d \
./source/setup_teardown.d \
./source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=1 -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I../board -I../uCUnit -I../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../CMSIS_driver -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



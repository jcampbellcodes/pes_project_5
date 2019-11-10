################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/handle_led.c \
../source/logger.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/setup_teardown.c 

OBJS += \
./source/handle_led.o \
./source/logger.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/setup_teardown.o 

C_DEPS += \
./source/handle_led.d \
./source/logger.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/setup_teardown.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I../board -I../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../CMSIS_driver -I../startup -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



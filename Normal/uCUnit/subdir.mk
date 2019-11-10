################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uCUnit/System.c 

OBJS += \
./uCUnit/System.o 

C_DEPS += \
./uCUnit/System.d 


# Each subdirectory must supply rules for building sources it contributes
uCUnit/%.o: ../uCUnit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I../board -I../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../CMSIS_driver -I../startup -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



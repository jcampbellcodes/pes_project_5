################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DPRINTF_FLOAT_ENABLE=1 -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I../board -I../include -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../CMSIS_driver -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



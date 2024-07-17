################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/alt_Src/alt_GPIO.cpp \
../Core/Src/alt_Src/alt_UART.cpp 

OBJS += \
./Core/Src/alt_Src/alt_GPIO.o \
./Core/Src/alt_Src/alt_UART.o 

CPP_DEPS += \
./Core/Src/alt_Src/alt_GPIO.d \
./Core/Src/alt_Src/alt_UART.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/alt_Src/%.o Core/Src/alt_Src/%.su: ../Core/Src/alt_Src/%.cpp Core/Src/alt_Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DSTM32F407xx -DUSE_FULL_LL_DRIVER -DHSE_VALUE=25000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-alt_Src

clean-Core-2f-Src-2f-alt_Src:
	-$(RM) ./Core/Src/alt_Src/alt_GPIO.d ./Core/Src/alt_Src/alt_GPIO.o ./Core/Src/alt_Src/alt_GPIO.su ./Core/Src/alt_Src/alt_UART.d ./Core/Src/alt_Src/alt_UART.o ./Core/Src/alt_Src/alt_UART.su

.PHONY: clean-Core-2f-Src-2f-alt_Src


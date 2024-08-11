################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/hw/device/BT_Receiver.c \
../App/hw/device/dcMotor.c \
../App/hw/device/mobileRemoteCar.c \
../App/hw/device/ultrasonic.c 

OBJS += \
./App/hw/device/BT_Receiver.o \
./App/hw/device/dcMotor.o \
./App/hw/device/mobileRemoteCar.o \
./App/hw/device/ultrasonic.o 

C_DEPS += \
./App/hw/device/BT_Receiver.d \
./App/hw/device/dcMotor.d \
./App/hw/device/mobileRemoteCar.d \
./App/hw/device/ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
App/hw/device/%.o App/hw/device/%.su App/hw/device/%.cyclo: ../App/hw/device/%.c App/hw/device/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/work/Harman_4_LJP/ARM/workSpace/mobileRemoteCar/App" -I"C:/work/Harman_4_LJP/ARM/workSpace/mobileRemoteCar/App/common" -I"C:/work/Harman_4_LJP/ARM/workSpace/mobileRemoteCar/App/hw" -I"C:/work/Harman_4_LJP/ARM/workSpace/mobileRemoteCar/App/hw/device" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-hw-2f-device

clean-App-2f-hw-2f-device:
	-$(RM) ./App/hw/device/BT_Receiver.cyclo ./App/hw/device/BT_Receiver.d ./App/hw/device/BT_Receiver.o ./App/hw/device/BT_Receiver.su ./App/hw/device/dcMotor.cyclo ./App/hw/device/dcMotor.d ./App/hw/device/dcMotor.o ./App/hw/device/dcMotor.su ./App/hw/device/mobileRemoteCar.cyclo ./App/hw/device/mobileRemoteCar.d ./App/hw/device/mobileRemoteCar.o ./App/hw/device/mobileRemoteCar.su ./App/hw/device/ultrasonic.cyclo ./App/hw/device/ultrasonic.d ./App/hw/device/ultrasonic.o ./App/hw/device/ultrasonic.su

.PHONY: clean-App-2f-hw-2f-device


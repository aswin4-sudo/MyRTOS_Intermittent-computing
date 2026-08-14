################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/MyRTOS/Source/croutine.c \
../Middlewares/Third_Party/MyRTOS/Source/event_groups.c \
../Middlewares/Third_Party/MyRTOS/Source/list.c \
../Middlewares/Third_Party/MyRTOS/Source/queue.c \
../Middlewares/Third_Party/MyRTOS/Source/stream_buffer.c \
../Middlewares/Third_Party/MyRTOS/Source/tasks.c \
../Middlewares/Third_Party/MyRTOS/Source/timers.c 

OBJS += \
./Middlewares/Third_Party/MyRTOS/Source/croutine.o \
./Middlewares/Third_Party/MyRTOS/Source/event_groups.o \
./Middlewares/Third_Party/MyRTOS/Source/list.o \
./Middlewares/Third_Party/MyRTOS/Source/queue.o \
./Middlewares/Third_Party/MyRTOS/Source/stream_buffer.o \
./Middlewares/Third_Party/MyRTOS/Source/tasks.o \
./Middlewares/Third_Party/MyRTOS/Source/timers.o 

C_DEPS += \
./Middlewares/Third_Party/MyRTOS/Source/croutine.d \
./Middlewares/Third_Party/MyRTOS/Source/event_groups.d \
./Middlewares/Third_Party/MyRTOS/Source/list.d \
./Middlewares/Third_Party/MyRTOS/Source/queue.d \
./Middlewares/Third_Party/MyRTOS/Source/stream_buffer.d \
./Middlewares/Third_Party/MyRTOS/Source/tasks.d \
./Middlewares/Third_Party/MyRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/MyRTOS/Source/%.o Middlewares/Third_Party/MyRTOS/Source/%.su Middlewares/Third_Party/MyRTOS/Source/%.cyclo: ../Middlewares/Third_Party/MyRTOS/Source/%.c Middlewares/Third_Party/MyRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/MyRTOS/Source/include -I../Middlewares/Third_Party/MyRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/MyRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-MyRTOS-2f-Source

clean-Middlewares-2f-Third_Party-2f-MyRTOS-2f-Source:
	-$(RM) ./Middlewares/Third_Party/MyRTOS/Source/croutine.cyclo ./Middlewares/Third_Party/MyRTOS/Source/croutine.d ./Middlewares/Third_Party/MyRTOS/Source/croutine.o ./Middlewares/Third_Party/MyRTOS/Source/croutine.su ./Middlewares/Third_Party/MyRTOS/Source/event_groups.cyclo ./Middlewares/Third_Party/MyRTOS/Source/event_groups.d ./Middlewares/Third_Party/MyRTOS/Source/event_groups.o ./Middlewares/Third_Party/MyRTOS/Source/event_groups.su ./Middlewares/Third_Party/MyRTOS/Source/list.cyclo ./Middlewares/Third_Party/MyRTOS/Source/list.d ./Middlewares/Third_Party/MyRTOS/Source/list.o ./Middlewares/Third_Party/MyRTOS/Source/list.su ./Middlewares/Third_Party/MyRTOS/Source/queue.cyclo ./Middlewares/Third_Party/MyRTOS/Source/queue.d ./Middlewares/Third_Party/MyRTOS/Source/queue.o ./Middlewares/Third_Party/MyRTOS/Source/queue.su ./Middlewares/Third_Party/MyRTOS/Source/stream_buffer.cyclo ./Middlewares/Third_Party/MyRTOS/Source/stream_buffer.d ./Middlewares/Third_Party/MyRTOS/Source/stream_buffer.o ./Middlewares/Third_Party/MyRTOS/Source/stream_buffer.su ./Middlewares/Third_Party/MyRTOS/Source/tasks.cyclo ./Middlewares/Third_Party/MyRTOS/Source/tasks.d ./Middlewares/Third_Party/MyRTOS/Source/tasks.o ./Middlewares/Third_Party/MyRTOS/Source/tasks.su ./Middlewares/Third_Party/MyRTOS/Source/timers.cyclo ./Middlewares/Third_Party/MyRTOS/Source/timers.d ./Middlewares/Third_Party/MyRTOS/Source/timers.o ./Middlewares/Third_Party/MyRTOS/Source/timers.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-MyRTOS-2f-Source


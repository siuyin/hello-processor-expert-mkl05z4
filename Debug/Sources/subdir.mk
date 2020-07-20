################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/main.c \
../Sources/mySysTick.c 

OBJS += \
./Sources/Events.o \
./Sources/main.o \
./Sources/mySysTick.o 

C_DEPS += \
./Sources/Events.d \
./Sources/main.d \
./Sources/mySysTick.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/siuyin/workspace.kds/hello-processor-expert-mkl05z4/Static_Code/PDD" -I"/home/siuyin/workspace.kds/hello-processor-expert-mkl05z4/Static_Code/IO_Map" -I"/home/siuyin/workspace.kds/hello-processor-expert-mkl05z4/Sources" -I"/home/siuyin/workspace.kds/hello-processor-expert-mkl05z4/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chat_test.c \
../chating_test.c \
../encode.c \
../get_random.c \
../hide_data.c \
../inet_connect.c \
../lencode.c \
../main.c \
../main_func.c \
../open_data.c \
../send_once.c \
../time.c 

OBJS += \
./chat_test.o \
./chating_test.o \
./encode.o \
./get_random.o \
./hide_data.o \
./inet_connect.o \
./lencode.o \
./main.o \
./main_func.o \
./open_data.o \
./send_once.o \
./time.o 

C_DEPS += \
./chat_test.d \
./chating_test.d \
./encode.d \
./get_random.d \
./hide_data.d \
./inet_connect.d \
./lencode.d \
./main.d \
./main_func.d \
./open_data.d \
./send_once.d \
./time.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



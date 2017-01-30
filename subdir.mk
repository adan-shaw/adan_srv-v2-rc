################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../array_queue.c \
../array_stack.c \
../encode.c \
../get_random.c \
../hide_data.c \
../if_event.c \
../inet_listen.c \
../lencode.c \
../main.c \
../main_func.c \
../open_data.c \
../pickup_data.c \
../pthread_listen.c \
../pthread_recv.c \
../redis_test.c \
../x3_details.c 

OBJS += \
./array_queue.o \
./array_stack.o \
./encode.o \
./get_random.o \
./hide_data.o \
./if_event.o \
./inet_listen.o \
./lencode.o \
./main.o \
./main_func.o \
./open_data.o \
./pickup_data.o \
./pthread_listen.o \
./pthread_recv.o \
./redis_test.o \
./x3_details.o 

C_DEPS += \
./array_queue.d \
./array_stack.d \
./encode.d \
./get_random.d \
./hide_data.d \
./if_event.d \
./inet_listen.d \
./lencode.d \
./main.d \
./main_func.d \
./open_data.d \
./pickup_data.d \
./pthread_listen.d \
./pthread_recv.d \
./redis_test.d \
./x3_details.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



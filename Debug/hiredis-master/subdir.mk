################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hiredis-master/async.c \
../hiredis-master/dict.c \
../hiredis-master/hiredis.c \
../hiredis-master/net.c \
../hiredis-master/read.c \
../hiredis-master/sds.c 

OBJS += \
./hiredis-master/async.o \
./hiredis-master/dict.o \
./hiredis-master/hiredis.o \
./hiredis-master/net.o \
./hiredis-master/read.o \
./hiredis-master/sds.o 

C_DEPS += \
./hiredis-master/async.d \
./hiredis-master/dict.d \
./hiredis-master/hiredis.d \
./hiredis-master/net.d \
./hiredis-master/read.d \
./hiredis-master/sds.d 


# Each subdirectory must supply rules for building sources it contributes
hiredis-master/%.o: ../hiredis-master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



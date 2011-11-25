################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConnectDialog.cpp \
../src/DashDialog.cpp \
../src/DataProvider.cpp \
../src/MainFrame.cpp \
../src/TEWBClient.cpp \
../src/Utility.cpp \
../src/WB4Lin.cpp \
../src/main.cpp \
../src/wbDigit.cpp \
../src/wbGauge.cpp \
../src/wbGaugeDialog.cpp \
../src/wbGraph.cpp 

OBJS += \
./src/ConnectDialog.o \
./src/DashDialog.o \
./src/DataProvider.o \
./src/MainFrame.o \
./src/TEWBClient.o \
./src/Utility.o \
./src/WB4Lin.o \
./src/main.o \
./src/wbDigit.o \
./src/wbGauge.o \
./src/wbGaugeDialog.o \
./src/wbGraph.o 

CPP_DEPS += \
./src/ConnectDialog.d \
./src/DashDialog.d \
./src/DataProvider.d \
./src/MainFrame.d \
./src/TEWBClient.d \
./src/Utility.d \
./src/WB4Lin.d \
./src/main.d \
./src/wbDigit.d \
./src/wbGauge.d \
./src/wbGaugeDialog.d \
./src/wbGraph.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DWX_PRECOMP -I../include -O0 -g3 -Wall -c -fmessage-length=0 `wx-config --cxxflags` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



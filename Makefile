# Toolchain
CXX = arm-none-eabi-g++
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size


BUILD_DIR = build

MCU_FLAGS = -mcpu=cortex-m0plus -mthumb 
CFLAGS = $(MCU_FLAGS) -O0 -std=c11 -g -gdwarf-2 $(INCLUDES)
CXXFLAGS = $(MCU_FLAGS) -O0 -std=c++20 -g -gdwarf-2 -fno-exceptions -fno-rtti $(INCLUDES)
LDFLAGS = $(MCU_FLAGS) -Wl,--gc-sections -specs=nano.specs -T STM32G070RBTx_FLASH.ld -lc -lnosys 

INCLUDES = -ICMSIS/Device/ST/STM32G0xx/Include -ICMSIS/Include -Iinc

# Files
SOURCES = startup_stm32g070xx.s src/system_stm32g0xx.c src/main.cpp src/led.cpp src/uart.cpp src/mcal.cpp src/log.cpp src/stub.cpp src/pwm_controller.cpp
TARGET = $(BUILD_DIR)/output.elf

all: $(TARGET)

$(TARGET): $(SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) $^ -o $@
	$(OBJCOPY) -O binary $@ $(BUILD_DIR)/output.bin
	$(SIZE) --format=berkeley $(TARGET)

clean:
	rm -f *.o $(TARGET) output.bin

.PHONY: all clean

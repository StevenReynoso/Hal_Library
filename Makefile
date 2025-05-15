# Makefile - Bare-metal STM32F4 build system

# Toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Project
TARGET  = main

# Paths
SRC = ../core/main.c \
      ../platform/stm32f4/startup.s \
      ../src/hal_gpio.c \
      ../src/hal_rcc.c

INCLUDES = -I../include -I../include/registers

# Flags
CFLAGS  = -mcpu=cortex-m4 -mthumb -Wall -O0 -g -ffreestanding -nostdlib -Isrc -I$(INCLUDES)
LDFLAGS = -T ../platform/stm32f4/linker.ld

# Build rules
all: $(TARGET).bin

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.o *.elf *.bin

flash:
	st-flash write $(TARGET).bin 0x08000000

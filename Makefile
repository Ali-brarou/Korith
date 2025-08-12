SRC_DIRS := lib kernel 
BUILD_DIR :=  build
INCLUDE_DIRS := -Iinclude

CROSS_COMPILE := i686-elf-

CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld

CFLAGS := -O2 -ffreestanding -fno-stack-protector -Wall -Wextra -g $(INCLUDE_DIRS) 
LDFLAGS := -nostdlib -T kernel/linker.ld 

C_SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS))

ASM_SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.S))
ASM_OBJS := $(patsubst %.S,$(BUILD_DIR)/%.o,$(ASM_SRCS))

KERNEL_ELF := $(BUILD_DIR)/kernel.elf

all:  $(KERNEL_ELF)

#linking
$(KERNEL_ELF): $(OBJ_FILES) $(ASM_OBJS)
	mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean: 
	rm -rf $(BUILD_DIR)/* 

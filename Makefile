SRC_DIRS := lib kernel 
BUILD_DIR :=  build
INCLUDE_DIRS := -Iinclude

CROSS_COMPILE := i686-elf-

CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld

QEMU := qemu-system-i386 

CFLAGS := -O2 -ffreestanding -fno-stack-protector -Wall -Wextra -Werror -g $(INCLUDE_DIRS) 
LDFLAGS := -nostdlib -T kernel/kernel.ld 

C_SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS))

ASM_SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.S))
ASM_OBJS := $(patsubst %.S,$(BUILD_DIR)/%.o,$(ASM_SRCS))

KERNEL_ELF := $(BUILD_DIR)/korith.elf

ISO_DIR	   := $(BUILD_DIR)/isodir
ISO		   := $(ISO_DIR)/korith.iso

all:  $(KERNEL_ELF)

iso: $(ISO)

#linking
$(KERNEL_ELF): $(OBJ_FILES) $(ASM_OBJS)
	mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(ISO): $(KERNEL_ELF)
	mkdir -p $(ISO_DIR)/boot/grub
	echo 'menuentry "korith" {multiboot /boot/korith.elf}' > $(ISO_DIR)/boot/grub/grub.cfg
	cp $(KERNEL_ELF) $(ISO_DIR)/boot/
	grub-mkrescue -o $(ISO) $(ISO_DIR)

clean: 
	rm -rf $(BUILD_DIR)/* 

run: $(KERNEL_ELF) 
	$(QEMU) -kernel $(KERNEL_ELF) #-d int,cpu_reset 

debug: $(KERNEL_ELF)
	$(QEMU) -kernel $(KERNEL_ELF) -d int,cpu_reset -S -s

gdb: $(KERNEL_ELF)
	gdb $(KERNEL) -x scripts/gdb_cmds.txt

.PHONY : all iso clean run debug

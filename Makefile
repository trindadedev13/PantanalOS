CC      = g++
AS      = nasm
LD      = ld.lld

CFLAGS  = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
          -nostartfiles -nodefaultlibs -fno-rtti -fno-exceptions -Wall -Wextra -c \
          -target i386-unknown-none -I$(INCLUDE_DIR)

ASFLAGS = -f elf

SRC_DIR      = src
INCLUDE_DIR  = include
BUILD_DIR    = build

BOOT_SRC         = $(SRC_DIR)/Boot/boot.asm
KERNEL_SRC       = $(SRC_DIR)/Kernel/Kernel.cpp
KERNEL_ENTRY_SRC = $(SRC_DIR)/Kernel/Kernel.asm
GRAPHICS_SRC     = $(SRC_DIR)/Graphics/Graphics.cpp
TERMINAL_SRC     = $(SRC_DIR)/Terminal/Terminal.cpp

BOOT_BIN         = $(BUILD_DIR)/boot.bin
KERNEL_OBJ       = $(BUILD_DIR)/kernel.o
KERNEL_ENTRY_OBJ = $(BUILD_DIR)/kernel_entry.o
GRAPHICS_OBJ     = $(BUILD_DIR)/graphics.o
TERMINAL_OBJ     = $(BUILD_DIR)/terminal.o
ALL_OBJS         = $(KERNEL_ENTRY_OBJ) $(KERNEL_OBJ) $(GRAPHICS_OBJ) $(TERMINAL_OBJ)

KERNEL_BIN   = $(BUILD_DIR)/kernel.bin
OS_IMG       = $(BUILD_DIR)/os.img

all: $(OS_IMG)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BOOT_BIN): $(BOOT_SRC) | $(BUILD_DIR)
	$(AS) -f bin $< -o $@

$(KERNEL_ENTRY_OBJ): $(KERNEL_ENTRY_SRC) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(GRAPHICS_OBJ): $(GRAPHICS_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(TERMINAL_OBJ): $(TERMINAL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_BIN): $(ALL_OBJS)
	$(LD) -Ttext 0x7E00 --oformat binary $(ALL_OBJS) -o $@

$(OS_IMG): $(BOOT_BIN) $(KERNEL_BIN)
	cat $(BOOT_BIN) $(KERNEL_BIN) > $(OS_IMG)

run: $(OS_IMG)
	qemu-system-x86_64 -drive file=$(OS_IMG),format=raw -m 32M

debug: $(OS_IMG)
	qemu-system-x86_64 -drive file=$(OS_IMG),format=raw -m 32M -serial stdio -d int

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run debug clean
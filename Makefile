CC      = g++
AS      = nasm
LD      = ld.lld

CFLAGS  = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
-nodefaultlibs -fno-rtti -fno-exceptions -Wall -Wextra -c \
-target i386-unknown-none -I$(INCLUDE_DIR)

ASFLAGS = -f elf
LDFLAGS = -T linker.ld

SRC_DIR      = src
INCLUDE_DIR  = include
BUILD_DIR    = build

# sources
BOOT_SRC         = $(SRC_DIR)/Boot/boot.asm

# kernel folder
KERNEL_SRC       = $(SRC_DIR)/Kernel/Kernel.cpp
KERNEL_ENTRY_SRC = $(SRC_DIR)/Kernel/Kernel.asm
KERNEL_ALLOCATOR_SRC    = $(SRC_DIR)/Kernel/Allocator/Allocator.cpp

GRAPHICS_SRC     = $(SRC_DIR)/Graphics/Graphics.cpp
TERMINAL_SRC     = $(SRC_DIR)/Terminal/Terminal.cpp
STRING_SRC       = $(SRC_DIR)/String.cpp

# shell folder
SHELL_LANG_LEXER_SRC = $(SRC_DIR)/Shell/Lang/Lexer.cpp

# bins
BOOT_BIN         = $(BUILD_DIR)/boot.bin

# kernel folder
KERNEL_OBJ       = $(BUILD_DIR)/kernel.o
KERNEL_ENTRY_OBJ = $(BUILD_DIR)/kernel_entry.o
KERNEL_ALLOCATOR_OBJ    = $(BUILD_DIR)/allocator.o

GRAPHICS_OBJ     = $(BUILD_DIR)/graphics.o
TERMINAL_OBJ     = $(BUILD_DIR)/terminal.o
STRING_OBJ       = $(BUILD_DIR)/string.o

# shell folder
SHELL_LANG_LEXER_OBJ = $(BUILD_DIR)/shell_lexer.o

ALL_OBJS         = $(KERNEL_ENTRY_OBJ) $(KERNEL_OBJ) $(KERNEL_ALLOCATOR_OBJ) $(GRAPHICS_OBJ) \
                   $(TERMINAL_OBJ) $(STRING_OBJ) $(SHELL_LANG_LEXER_OBJ)

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

$(KERNEL_ALLOCATOR_OBJ): $(KERNEL_ALLOCATOR_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(GRAPHICS_OBJ): $(GRAPHICS_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(TERMINAL_OBJ): $(TERMINAL_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(STRING_OBJ): $(STRING_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(SHELL_LANG_LEXER_OBJ): $(SHELL_LANG_LEXER_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(KERNEL_BIN): $(ALL_OBJS)
	$(LD) $(LDFLAGS) $(ALL_OBJS) -o $@

$(OS_IMG): $(BOOT_BIN) $(KERNEL_BIN)
	cat $(BOOT_BIN) $(KERNEL_BIN) > $(OS_IMG)

run: $(OS_IMG)
	qemu-system-x86_64 -drive file=$(OS_IMG),format=raw -m 32M

debug: $(OS_IMG)
	qemu-system-x86_64 -drive file=$(OS_IMG),format=raw -m 32M -serial stdio -d int

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run debug clean
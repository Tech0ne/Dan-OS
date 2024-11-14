SRCS =	src/bootloader/header.asm 	\
		src/bootloader/main.asm
ASM_PATH = src/bootloader/%.asm
OBJ_PATH = obj/%.o
OBJS = $(patsubst $(ASM_PATH), $(OBJ_PATH), $(SRCS))

BIN = target/x86_64/iso/boot/kernel.bin
LINKER = src/linker/linker.ld
ISO = build/x86_64/kernel.iso
ISO_TARGET = target/x86_64/iso
BUILD = build/x86_64
TRASH = obj build $(BIN)

MK = mkdir -p
NASM = nasm -f elf64
LD = x86_64-elf-ld -n -o $(BIN) -T $(LINKER) $(OBJS)
GRUB = grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO) $(ISO_TARGET)
RM = rm -rf

$(OBJS): $(OBJ_PATH): $(ASM_PATH)
	@ $(MK) $(dir $@) && \
	$(NASM) $(patsubst $(OBJ_PATH), $(ASM_PATH), $@) -o $@

.PHONY: build
build: $(OBJS)
	@ $(MK) $(BUILD) && \
	$(LD) && \
	$(GRUB)

.PHONY: clean
clean:
	@ $(RM) $(TRASH)

.PHONY: re
re: clean build

.PHONY: run
run:
	@ qemu-system-x86_64 -cdrom $(ISO)

.PHONY: help
help:
	@ echo "Usage: make [target]"
	@ echo "Targets:"
	@ echo "  build: Build the kernel"
	@ echo "  clean: Clean the build"
	@ echo "  run: Run the kernel"
	@ echo "  help: Show this message"


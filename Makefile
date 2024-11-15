ASM_SRCS 	=	$(wildcard src/bootloader/*.asm)

KERNEL_SRCS =	$(wildcard src/kernel/*.c)
PRINT_SRCS 	=	$(wildcard src/kernel/print/*.c)

ASM_PATH 	= 	src/bootloader/%.asm
KERNEL_PATH = 	src/kernel/%.c
PRINT_PATH 	= 	src/kernel/print/%.c
OBJ_PATH 	= 	obj/%.o
ASM_OBJS 	= 	$(patsubst $(ASM_PATH), $(OBJ_PATH), $(ASM_SRCS))
KERNEL_OBJS = 	$(patsubst $(KERNEL_PATH), $(OBJ_PATH), $(KERNEL_SRCS))
PRINT_OBJS 	= 	$(patsubst $(PRINT_PATH), $(OBJ_PATH), $(PRINT_SRCS))

OBJS 		= 	$(ASM_OBJS) $(KERNEL_OBJS) $(PRINT_OBJS)

BIN 		= 	target/x86_64/iso/boot/kernel.bin
LINKER 		= 	src/linker/linker.ld
ISO 		= 	build/x86_64/kernel.iso
ISO_TARGET 	= 	target/x86_64/iso
BUILD 		= 	build/x86_64
TRASH 		= 	obj build $(BIN)
INCLUDE 	= 	src/kernel/includes

MK 			= 	mkdir -p
CC 			= 	x86_64-elf-gcc -ffreestanding -I $(INCLUDE)
NASM 		= 	nasm -f elf64
LD 			= 	x86_64-elf-ld -n -o $(BIN) -T $(LINKER) $(OBJS)
GRUB 		= 	grub-mkrescue /usr/lib/grub/i386-pc -o $(ISO) $(ISO_TARGET)
RM 			= 	rm -rf

$(KERNEL_OBJS): $(OBJ_PATH): $(KERNEL_PATH)
	@ $(MK) $(dir $@) && \
	$(CC) -c $(patsubst $(OBJ_PATH), $(KERNEL_PATH), $@) -o $@

$(PRINT_OBJS): $(OBJ_PATH): $(PRINT_PATH)
	@ $(MK) $(dir $@) && \
	$(CC) -c $(patsubst $(OBJ_PATH), $(PRINT_PATH), $@) -o $@

$(ASM_OBJS): $(OBJ_PATH): $(ASM_PATH)
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
	@ echo "  re: Clean and build the kernel"
	@ echo "  run: Run the kernel"
	@ echo "  help: Show this message"


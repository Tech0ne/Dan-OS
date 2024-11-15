section .header

boot_start:
    dd 0xe85250d6                                                   ; multiboot2 magic number
    dd 0                                                            ; protected mode
    dd boot_end - boot_start                                        ; header length
    dd 0x100000000 - (0xe85250d6 + 0 + (boot_end - boot_start))     ; checksum
    dw 0
    dw 0
    dd 8                                                            ; header address
boot_end:
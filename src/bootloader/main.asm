global start
section .text
bits 32

start:
    mov dword [0xb8000], 0x2f4b2f4f         ; print "OK" to the top left corner of the screen
    hlt                                     ; halt the CPU
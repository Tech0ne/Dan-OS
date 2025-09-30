//
// Created by dan13615 on 11/15/24.
//

#include "tty.h"
#include "idt.h"
#include "timer.h"

extern void enable_interrupts();

void kernel_main(void) {
    tty_init();
    init_pit(1000);
    tty_middle_screen("Welcome to the DanOS kernel!\n", 29);
    init_idt();
    init_keyboard();
    enable_interrupts();
    while(1){}
}
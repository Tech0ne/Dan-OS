//
// Created by dan13615 on 11/15/24.
//

#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "shell.h"
#include "timer.h"

extern void enable_interrupts();

void welcome_message(void) {
   tty_putstr_endl("    ____                    ____  _____");
   tty_putstr_endl("   / __ \\____ _____        / __ \\/ ___/");
   tty_putstr_endl("  / / / / __ `/ __ \\______/ / / /\\__ \\");
   tty_putstr_endl(" / /_/ / /_/ / / / /_____/ /_/ /___/ /");
   tty_putstr_endl("/_____/\\__,_/_/ /_/      \\____//____/");
   tty_putstr_endl("");
}

void kernel_main(void) {
    tty_init();
    init_pit(1000);
    welcome_message();
    init_idt();
    init_keyboard();
    init_shell();
    enable_interrupts();
    while(1){}
}
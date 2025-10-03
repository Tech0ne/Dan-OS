/**========================================================================
 *                             commands.c
 *  description: This file contains the implementation of shell commands.
 *  author: Daniil Stepanov
 *  date: 2025-10-02
 *========================================================================**/

#include "shell.h"
#include "string.h"
#include "tty.h"

void cmd_echo(const char* args) {
    tty_putstr(args);
}

void cmd_clear(void) {
    tty_clear();
    tty_set_cursor(0, 0);
}

void cmd_help(void) {
    tty_putstr_endl("Available commands:");
    tty_putstr_endl("  echo [text]  - Echo the text");
    tty_putstr_endl("  clear        - Clear the screen");
    tty_putstr_endl("  help         - Show help message");
    tty_putstr_endl("  flex         - Display the welcome message");
}

void cmd_flex(void) {
    cmd_clear();
    welcome_message();
}

int process_command(const char* input, size_t length) {
    if (strncmp(input, "echo", length) == 0) {
        cmd_echo(input);
        return 0;
    } else if (strncmp(input, "clear", length) == 0) {
        cmd_clear();
        return 1;
    } else if (strncmp(input, "help", length) == 0) {
        cmd_help();
        return 0;
    } else if (strncmp(input, "flex", length) == 0) {
        cmd_flex();
        return 0;
    } else {
        tty_putstr("Unknown command: ");
        tty_putstr(input);
        tty_end_line();
        cmd_help();
        return -1; // Command not found
    }
    return 0;
}

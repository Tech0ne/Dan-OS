/**========================================================================
 *                             commands.c
 *  description: This file contains the implementation of shell commands.
 *  author: Daniil Stepanov
 *  date: 2025-10-02
 *========================================================================**/

#include "shell.h"
#include "string.h"
#include "tty.h"

int cmd_echo(const char* args) {
    tty_putstr(args);
    return 0;
}

int cmd_clear(const char* args) {
    UNUSED(args);
    tty_clear();
    tty_set_cursor(0, 0);
    return 1;
}

int cmd_help(const char* args) {
    UNUSED(args);
    tty_putstr_endl("Available commands:");
    tty_putstr_endl("  echo [text]  - Echo the text");
    tty_putstr_endl("  clear        - Clear the screen");
    tty_putstr_endl("  help         - Show help message");
    tty_putstr_endl("  flex         - Display the welcome message");
    return 0;
}

int cmd_flex(const char* args) {
    cmd_clear(args);
    welcome_message();
    return 0;
}

int (*commands[])(const char*) = {
    cmd_echo,
    cmd_clear,
    cmd_help,
    cmd_flex,
    NULL
};

const char *command_names[] = {
    "echo",
    "clear",
    "help",
    "flex",
    NULL
};

int process_command(const char* input, size_t length) {
    for (size_t i = 0; commands[i] != NULL; i++) {
        if (strncmp(input, command_names[i], length) == 0) {
            return ((int (*)(const char*))commands[i])(input);
        }
    }
    tty_putstr("Unknown command: ");
    tty_putstr(input);
    tty_end_line();
    cmd_help(input);
    return -1;
}

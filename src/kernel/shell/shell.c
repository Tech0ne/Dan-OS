/**========================================================================
 *                             SHELL MODULE
 *  description: This module implements a simple shell interface for the OS.
 *  It provides basic functionalities such as command execution, input
 *  handling, and output display.
 *  author: Daniil Stepanov
 *  date: 2025-10-02
 *========================================================================**/

#include "shell.h"
#include "tty.h"
#include "string.h"

static char input_buffer[SHELL_MAX_INPUT_LENGTH];
static size_t buffer_index = 0;

void add_to_buffer(char c) {
    if (c == '\b') { // Handle backspace
        if (buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';
            tty_cursor_backspace(1);
        }
    } else if (c == '\n') { // Handle enter key
        input_buffer[buffer_index] = '\0';
        tty_putchar('\n');

        // process command here (for now, just echo it back)
        if (buffer_index > 0) {
            print_buffer();
        }

        clear_buffer();
        print_prompt(); // Display prompt again
    } else if (buffer_index < SHELL_MAX_INPUT_LENGTH - 1) { // Regular character
        input_buffer[buffer_index++] = c;
        input_buffer[buffer_index] = '\0'; // Null-terminate the string
    }
}

void print_buffer(void) {
    tty_putstr(input_buffer);
}

void print_prompt(void) {
    tty_putstr(SHELL_PROMPT);
}

void clear_buffer(void) {
    memset(input_buffer, 0, sizeof(input_buffer));
    buffer_index = 0;
}
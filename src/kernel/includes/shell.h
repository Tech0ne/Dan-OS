/**========================================================================
 *                             SHELL MODULE
 *  description: This module implements a simple shell interface for the OS.
 *  It provides basic functionalities such as command execution, input
 *  handling, and output display.
 *  author: Daniil Stepanov
 *  date: 2025-10-02
 *========================================================================**/

#ifndef SHELL_H
  #define SHELL_H

    #include <stdint.h>

    #define SHELL_MAX_INPUT_LENGTH 128
    // #define SHELL_MAX_ARGS 16
    #define SHELL_PROMPT "Dan-OS &> "

    void add_to_buffer(char c);
    void print_buffer(void);
    void print_prompt(void);
    void clear_buffer(void);

#endif //SHELL_H
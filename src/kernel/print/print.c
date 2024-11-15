//
// Created by dan13615 on 11/15/24.
//

#include "print.h"

const static size_t VGA_WIDTH = 80;
const static size_t VGA_HEIGHT = 25;

struct Character {
    char c;
    uint8_t color;
};

struct Character* buffer = (struct Character*) 0xB8000;
size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = PRINT_COLOR_YELLOW | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Character empty = (struct Character) {
        .c = ' ',
        .color = terminal_color,
    };

    for (size_t x = 0; x < VGA_WIDTH; x++)
        buffer[x + VGA_WIDTH * row] = empty;
}

void print_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++)
        clear_row(y);
}

void print_newline(void) {
    terminal_column = 0;
    if (terminal_row < VGA_HEIGHT - 1) {
        terminal_row++;
        return;
    }
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            struct Character character = buffer[x + VGA_WIDTH * y];
            buffer[x + VGA_WIDTH * (y - 1)] = character;
        }
    }
    clear_row(VGA_HEIGHT - 1);
}

void print_char(char c) {
    if (c == '\n') {
        print_newline();
        return;
    }
    if (terminal_column > VGA_WIDTH) {
        print_newline();
    }
    buffer[terminal_column + VGA_WIDTH * terminal_row] = (struct Character) {
        .c = (uint8_t)c,
        .color = terminal_color,
    };
    terminal_column++;
}

void print_str(char* str) {
    char c = 0;

    for (size_t i = 0; 1; i++) {
        c = (uint8_t)str[i];

        if (c == '\0') return;
        print_char(c);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    terminal_color = foreground + (background << 4);
}
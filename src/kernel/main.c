//
// Created by dan13615 on 11/15/24.
//

#include "print.h"

void kernel_main(void) {
  print_clear();
  print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
  print_str("Welcome to the DanOS kernel!\n");
}
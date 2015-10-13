#include "editor.h"

// TODO - check if the noreturn attribute needs to be here as well
void finish() {
  endwin();
  exit(0);
}

void dummy_editor() {
  while (1) {
    int ch = getch();
    if (ch == 'q') finish();
  }
}


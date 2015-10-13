#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>
#include "udplib.h"

#ifndef BUILD_SERVER

__attribute__((noreturn)) void finish() {
  endwin();
  exit(0);
}

int main() {
  /* udp_bcast(3000, "hello"); */
  /* udp_bcast(3000, "worldddd"); */

  signal(SIGINT, finish);

  initscr();
  keypad(stdscr, TRUE);
  raw();
  nonl();
  noecho();

  scrollok(stdscr, TRUE);
  refresh();

  while (1) {
    int ch = getch();
    if (ch == 'q') finish();
  }

  finish();
}

#endif

#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>
#include "udplib.h"
#include "editor.h"

#ifndef BUILD_SERVER

int main() {
  // udp_bcast(3000, "hello");
  // udp_bcast(3000, "worldddd");

  signal(SIGINT, finish);

  initscr();
  keypad(stdscr, TRUE);
  raw();
  nonl();
  noecho();

  scrollok(stdscr, TRUE);
  refresh();

  dummy_editor();

  finish();
}

#endif

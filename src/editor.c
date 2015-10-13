#include <assert.h>
#include <string.h>
#include "editor.h"
#include "udplib.h"

static void log_msg(const char* str) {
  udp_bcast(3000, str);

}

// TODO - check if the noreturn attribute needs to be here as well
void finish() {
  endwin();
  exit(0);
}

#define M 25
#define N 80

static char buffer[25][80];
// current cursor position
static int x = 0;
static int y = 0;

static void update(int ch) {
  assert(x < 80);

  switch (ch) {
    case KEY_UP:
      --y;
      return;

    case KEY_DOWN:
      ++y;
      return;

    case KEY_LEFT:
      --x;
      return;

    case KEY_RIGHT:
      ++x;
      return;

  }

  buffer[y][x] = ch;

  if (x+1 == 80) {
    x = 0;
    ++y;
  } else {
    ++x;
  }

}

static void render() {
  char buf[100];
  memset(buf, 0, strlen(buf));

  sprintf(buf, "%d %d %c", x, y, buffer[0][0]);

  log_msg(buf);
  wmove(stdscr, 0, 0);

  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      addch(buffer[i][j]);
    }
    addch('\n');
  }

  wmove(stdscr, y, x);
}

void dummy_editor() {
  memset(buffer, '.', M*N);

  render();
  while (1) {
    int ch = getch();
    if (ch == 'q') finish();

    update(ch);
    render();
  }
}


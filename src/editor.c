#include <assert.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "editor.h"
#include "udplib.h"

#define M 25
#define N 80

static char buffer[25][81];
// current cursor position
static int x = 0;
static int y = 0;

static void fix_trailing_cursor() {
  for (int j = 0; j < 81; ++j) {
    if (!buffer[y][j]) {
      x = j;
      break;
    }
  }

}

static void log_msg(const char* str) {
  fprintf(stderr, "%s\n", str);
}

static void log_char(char c) {
  fprintf(stderr, "%c\n", c);
}

// TODO - check if the noreturn attribute needs to be here as well
void finish() {
  endwin();
  exit(0);
}

static void update(int ch) {
  assert(x < 80);

  switch (ch) {
    case 13: // TODO
    case KEY_ENTER:
      ++y;
      x = 0;
      return;

    case KEY_DC:
    case 127: // TODO - check this
    case KEY_BACKSPACE:
      --x;

      // TODO - should be 0 if there are no characters afterward
      buffer[y][x] = ' ';
      return;

    case KEY_UP:
      --y;
      fix_trailing_cursor();
      return;

    case KEY_DOWN:
      ++y;
      fix_trailing_cursor();
      return;

    case KEY_LEFT:
      --x;
      fix_trailing_cursor();
      return;

    case KEY_RIGHT:
      ++x;
      fix_trailing_cursor();
      return;

  }

  fix_trailing_cursor();

  buffer[y][x] = ch;

  if (x+1 == 80) {
    x = 0;
    ++y;
  } else {
    ++x;
  }
}

static void render() {
  wmove(stdscr, 0, 0);

  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      if (buffer[i][j])
        addch(buffer[i][j]);
      else
        addch(' ');
    }
    addch('\n');
  }

  wmove(stdscr, y, x);
}

void dummy_editor() {
  memset(buffer, '\0', M*N);

  render();
  while (1) {
    int ch = getch();
    if (ch == 'q') finish();

    update(ch);
    render();
  }
}


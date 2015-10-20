#include <assert.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <menu.h>
#include <ncurses.h>

#include "editor.h"
#include "udplib.h"

/* #define M 25 */
/* #define N 80 */
#define M 5
#define N 8

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static char buffer[M][N + 1];
// current cursor position
static int x = 0;
static int y = 0;

static void fix_trailing_cursor() {
  for (int j = 0; j < N; ++j) {
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
  assert(x < N);

  switch (ch) {
    case 13:  // TODO
    case KEY_ENTER:
      y = MIN(y + 1, M);
      x = 0;
      fprintf(stderr, "(%d %d)\n", x, y);
      return;

    case KEY_DC:
    case 127:
    case KEY_BACKSPACE:
      if (x) {
        x--;
      } else if (y) {
        y--;
        // TODO - this should be the position of the last non-zero character
        x = N - 1;
      } else {
        fprintf(stderr, "(%d %d)\n", x, y);
        return;  // backspacing at 0,0
      }

      // TODO - should be 0 if there are no characters afterward
      buffer[y][x] = '\0';
      fprintf(stderr, "(%d %d)\n", x, y);
      return;

    case KEY_UP:
      y = MAX(y - 1, 0);
      fix_trailing_cursor();
      fprintf(stderr, "(%d %d)\n", x, y);
      return;

    case KEY_DOWN:
      y = MIN(y + 1, M);
      fix_trailing_cursor();
      fprintf(stderr, "(%d %d)\n", x, y);
      return;

    case KEY_LEFT:
      x = MAX(x - 1, 0);
      fix_trailing_cursor();
      fprintf(stderr, "(%d %d)\n", x, y);
      return;

    case KEY_RIGHT:
      x = MIN(x + 1, M);
      fix_trailing_cursor();
      fprintf(stderr, "(%d %d)\n", x, y);
      return;
  }

  buffer[y][x] = ch;

  if (x + 1 == N) {
    x = 0;
    ++y;
  } else {
    ++x;
  }

  fprintf(stderr, "(%d %d)\n", x, y);

  fix_trailing_cursor();
}

static void render() {
  wmove(stdscr, 0, 0);

  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      if (buffer[i][j])
        addch(buffer[i][j]);
      else
        addch('.');
    }
    addch('\n');
  }

  wmove(stdscr, y, x);
}

void dummy_editor() {
  memset(buffer, '\0', M * N);

  render();
  while (1) {
    int ch = getch();
    if (ch == 'q') finish();

    update(ch);
    render();
  }
}

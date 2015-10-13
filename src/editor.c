#include <assert.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "editor.h"
#include "udplib.h"

static void log_msg(const char* str) {
  fprintf(stderr, "%s", str);
  /* udp_bcast(3000, str); */
  /* int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND); */
  /* if (fd == -1) { */
  /*   failed("log_msg() -> open()"); */
  /* } */
  /*  */
  /* if (dprintf(fd, "log: %s", str) != strlen(str)) { */
  /*   failed("log_msg() -> dprintf()"); */
  /* } */
  /*  */
  /* if (!close(fd)) { */
  /*   failed("log_msg() -> close()"); */
  /* } */
}

static void log_char(char c) {
  char buf[2] = { c, '\0' };
  udp_bcast(3000, buf);
}

// TODO - check if the noreturn attribute needs to be here as well
void finish() {
  endwin();
  exit(0);
}

#define M 25
#define N 80

static char buffer[25][81];
// current cursor position
static int x = 0;
static int y = 0;

static void update(int ch) {
  assert(x < 80);

  switch (ch) {
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
  // TODO - figure out a better way of logging
  /* char buf[100]; */
  /* memset(buf, 0, strlen(buf)); */
  /* sprintf(buf, "%d %d %c", x, y, buffer[0][0]); */
  /* log_msg(buf); */

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


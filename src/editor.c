#include <assert.h>
#include <string.h>
#include "editor.h"
#include "udplib.h"

static void log(const char* str) {
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

  buffer[x][y] = ch;

  if (x+1 == 80) {
    x = 0;
  }

  ++y;
}

static void render() {
  char buf[100];
  memset(buf, 0, strlen(buf));

  sprintf(buf, "%d %d %c", x, y, buffer[0][0]);

  log(buf);
  wmove(stdscr, 0, 0);


  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      addch(buffer[i][j]);
    }
    wmove(stdscr, i, 0);
  }
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


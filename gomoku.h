#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <curses.h>
#include <ctype.h>
#include <time.h>

struct placement {
  int row;
  int col;
  int player;
};

struct score {
  char *player_1;
  char *player_2;
  char *winner;
  time_t time;
};

void print_logo();
void print_gomoku();
void play_gomoku();
void print_scoreboard();
void end_gomoku();
void give_up();
void time_out();
void placement(int);

int is_game_end(int);

/* gomoku board. none: 0, black: 1, white: 2 */
int matrix[19][19];

/* placement order */
struct placement placement_order[361];

char player_1[4];
char player_2[4];
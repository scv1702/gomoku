#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

#define BLACK 1
#define WHITE 2

struct score {
  char *player_1;
  char *player_2;
  char *winner;
  time_t time;
};

void print_logo();
void print_scoreboard();
void print_gomoku_board();
void play_gomoku();
void end_gomoku(int);
void give_up();
void time_out();
void placement();
void init_game();
void clear_read_buffer();
void record_game(int);
int is_game_end();
void *print_time();

/* gomoku board. none: 0, black: 1, white: 2 */
int gomoku_board[19][19];

/* initial of player 1 (black) */
char player_1[4];

/* initial of player 2 (white) */
char player_2[4];

/* color of the stone of the player who has the turn. */
int player_now_placement;
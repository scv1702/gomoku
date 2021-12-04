#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <curses.h>

void print_logo();
void print_gomoku();
void play_gomoku();
void print_scoreboard();
void end_gomoku();
void give_up();
void time_out();
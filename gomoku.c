#include "gomoku.h"

int player_1_lose;

int matrix[19][19];

void play_gomoku() {
  while (1) {
    alarm(30);
    print_gomoku(1, 1);
  }
}

void print_scoreboard() {

}

void end_gomoku() {
  signal(SIGINT, SIG_IGN);
  signal(SIGALRM, SIG_IGN);

  puts("---------------------------");
  puts("| GAME OVER! Press enter. |");
  puts("---------------------------");

  while (getchar() != '\n');
  system("clear");

  if (player_1_lose) {
    puts("Player 2 is winner!");
  } else {
    puts("Player 1 is winner!");
  }

  exit(0);
}

void placement(int who) {
  int row;
  int col;
  
}

void print_gomoku() {
  system("clear");
  puts("   A B C D E F G H I J K L M N O P Q R S  ");
  for (int row = 0; row < 19; row++) {
    printf("%2d ", 18 - row);
    for (int col = 0; col < 19; col++) {
      if (matrix[row][col] == 0) {
        printf(". ");
      } else if (matrix[row][col] == 1) {
        printf("● ");
      } else if (matrix[row][col] == 2) {
        printf("○ ");
      }
    }
    printf("%-2d\n", 18 - row);
  }
  puts("   A B C D E F G H I J K L M N O P Q R S  ");
}
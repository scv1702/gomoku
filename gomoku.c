#include "gomoku.h"

void play_gomoku() {
  signal(SIGINT, give_up);
  signal(SIGALRM, time_out);
  alarm(30);
  print_gomoku();
  while (1) {
    /* player 1 placement */
    placement(1);
    print_gomoku();

    if (is_game_end(1)) {
      end_gomoku(1);
      break;
    }

    /* player 2 placement */
    placement(2);
    print_gomoku();

    if (is_game_end(2)) {
      end_gomoku(2);
      break;
    }
  }
}

void print_scoreboard() {
  FILE *scoreboard_fp;
  char player_1[4];
  char player_2[4];
  char winner[4];
  int index;
  time_t t;

  index = 0;
  scoreboard_fp = fopen("scoreboard", "r");

  printf("Index    Player 1    Player 2    Winner    Time\n");
  while (fscanf(scoreboard_fp, "%s %s %s %ld", player_1, player_2, winner, &t) != EOF) {
    printf("%d        %s         %s         %s       %s\n", index++, player_1, player_2, winner, ctime(&t));
  }

  exit(0);
}

void end_gomoku(int player) {
  time_t t;
  FILE *scoreboard_fp;
  signal(SIGINT, SIG_IGN);
  signal(SIGALRM, SIG_IGN);

  printf("Player %d is winner!\n", player);
  puts("------------------------------------------------");
  puts("| GAME OVER! Input your name within 3 letters. |");
  puts("------------------------------------------------");

  printf("Player 1: ");
  scanf("%s", player_1);

  printf("Player 2: ");
  scanf("%s", player_2);

  system("clear");

  scoreboard_fp = fopen("scoreboard", "w");

  if (player == 1) {
    fprintf(scoreboard_fp, "%s %s %s %ld", player_1, player_2, player_1, time(&t));
  } else if (player == 2) {
    fprintf(scoreboard_fp, "%s %s %s %ld", player_1, player_2, player_2, time(&t));
  }
  
  exit(0);
}

void placement(int player) {
  int row;
  char col;

  printf("where: ");

  while (1) {
    row = 0;
    col = 0;

    scanf("%c%d", &col, &row);
    getchar();
  
    col = toupper(col);
    col -= 'A';
    
    if (!matrix[row][col]) { 
      matrix[row][col] = player;
      break;
    }
  }
}

void print_gomoku() {
  system("clear");
  puts("   A B C D E F G H I J K L M N O P Q R S");
  for (int row = 0; row < 19; row++) {
    printf("%2d ", row);
    for (int col = 0; col < 19; col++) {
      if (matrix[row][col] == 0) {
        printf(". ");
      } else if (matrix[row][col] == 1) {
        printf("● ");
      } else if (matrix[row][col] == 2) {
        printf("○ ");
      }
    }
    printf("%-2d\n", row);
  }
  puts("   A B C D E F G H I J K L M N O P Q R S");
}

/* game end: 0, game continue: 1 */
int is_game_end(int player) {
	int row;
  int col;
  int rock;
  int check;

	check = 0;
	
	for (row = 0; row < 19; row++) {
		for (col= 0; col < 19; col++) { 
			if (matrix[row][col] == player) {
				check++;

				for (rock = 1; rock < 5; rock++) {
					if (col + rock >= 19) {
            break;
          } else if (matrix[row][col + rock] == player) {
						check++;
						continue;
					} else {
            check = 1;
						break;
          }
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (col - rock <= -1) {
            break;
          } else if (matrix[row][col - rock] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (row + rock >= 19) {
            break;
          } else if (matrix[row + rock][col] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (row + rock <=-1) {
            break;
          } else if (matrix[row + rock][col] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (row + rock >= 19 || col + rock >= 19) {
            break;
          } else if (matrix[row + rock][col + rock] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (row + rock >= 19 || col - rock <= -1) {
            break;
          } else if (matrix[row + rock][col - rock] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (row - rock <= -1 || col + rock >= 19) {
            break;
          } else if (matrix[row - rock][col + rock] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
					
				for (rock = 1; rock < 5; rock++) {
					if (row - rock <= -1 || col - rock <= -1) {
            break;
          } else if (matrix[row + rock][col] == player) {
						check++;
						continue;
					} else {
						check = 1;
						break;
					}
				}

				if (check == 5) {
          return 1;
        }
			}
		}
	}

	return 0;
}

void give_up() {
  int option;

  alarm(0);
  puts("Do you really want to give up this game?");
  puts("1) yes");
  puts("2) no");
  printf(": ");
  scanf("%d", &option);

  if (option) {
    exit(0);
  }
}

void time_out() {
  puts("30 seconds have passed. Time out!");
  exit(0);
}
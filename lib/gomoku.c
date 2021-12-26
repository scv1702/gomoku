#include "gomoku.h"
#include <pthread.h>

// initialize the game
void init_game() {
  memset(gomoku_board, 0, sizeof(gomoku_board));
  memset(player_1, 0, sizeof(player_1));
  memset(player_2, 0, sizeof(player_2));
}

// start the game
void play_gomoku() {  
  print_gomoku_board();

  while (1) {
    placement();
    print_gomoku_board();
    if (is_game_end()) {
      end_gomoku(player_now_placement);
      break;
    }
    switch (player_now_placement) {
      case BLACK:
        player_now_placement = WHITE;
        break;
      
      case WHITE:
        player_now_placement = BLACK;
        break;
    }
  }
}

// print the scoreboard
void print_scoreboard() {
  FILE *scoreboard_fp;
  char player_1[4];
  char player_2[4];
  char winner[4];
  int index;
  time_t t;

  index = 0;
  scoreboard_fp = fopen("./bin/scoreboard", "r");

  system("clear");

  printf(" Index | Player1 | Player2 | Winner |       Time\n");
  while (fscanf(scoreboard_fp, "%s %s %s %ld", player_1, player_2, winner, &t) != EOF) {
    printf("--------------------------------------------------------------\n");
    printf(" %d     |   %s   |   %s   |   %s  | %s", index++, player_1, player_2, winner, ctime(&t));
  }
  printf("--------------------------------------------------------------\n");
}

// end the game, if want, record the result of the game
void end_gomoku(int winner) {
  int option;

  // the game finish, so ignore the signal
  signal(SIGINT, SIG_IGN);
  signal(SIGALRM, SIG_IGN);

  if (winner == BLACK) {
    printf("Black is winner!\n");
  } else if (winner == WHITE) {
    printf("White is winner!\n");
  }

  puts("Do you want to record the result of this game at the scoreboard?");
  puts("1) yes");
  puts("2) no");
  printf(": ");
  scanf("%d", &option);

  if (option == 2) {
    puts("GG!");
    exit(0);
  }

  puts("-------------------------------------");
  puts("| Input your name within 3 letters. |");
  puts("-------------------------------------");

  printf("Player 1 (Black): ");
  scanf("%s", player_1);

  printf("Player 2 (White): ");
  scanf("%s", player_2);
  
  record_game(winner);

  puts("GG!");
  
  exit(0);
}

// record the result of the game
void record_game(int winner) {
  FILE *scoreboard_fp;
  int thepipe[2];
  char buf[BUFSIZ];

  if (pipe(thepipe) == -1) {
    perror("pipe");
  }

  // parallel processing of the recording using fork() and pipe()
  switch (fork()) {
    case -1:
      perror("fork");
      exit(1);
    // child process records the result
    case 0:
      close(thepipe[1]);
      read(thepipe[0], buf, BUFSIZ);

      scoreboard_fp = fopen("./bin/scoreboard", "a+");

      if (scoreboard_fp == NULL) {
        perror("scoreboard_fp fopen");
        exit(1);
      }

      fprintf(scoreboard_fp, "%s", buf);
      fflush(scoreboard_fp);

      exit(0);
    // parent process sends the result to the child process
    default:
      close(thepipe[0]);

      if (winner == BLACK) {
        sprintf(buf, "%s %s %s %ld\n", player_1, player_2, player_1, time(NULL));
      } else if (winner == WHITE) {
        sprintf(buf, "%s %s %s %ld\n", player_1, player_2, player_2, time(NULL));
      }

      if (write(thepipe[1], buf, strlen(buf)) != strlen(buf)) {
        perror("write");
        exit(1);
      }

      wait(NULL);

      puts("Record completed.");

      break;
  }
}

// place the stone at the gomoku board
void placement() {
  int row;
  char col;
  
  printf("where (%s): ", player_now_placement == BLACK ? "black" : "white");
  fflush(stdout);
  alarm(30);
  
  while (1) {
    row = 0;
    col = 0;

    scanf("%c%d", &col, &row);
    getchar();
  
    col = toupper(col);
    col -= 'A';
    
    if (gomoku_board[row][col] == 0) { 
      gomoku_board[row][col] = player_now_placement;
      alarm(0);
      break;
    }
  }
}

// print the gomoku board
void print_gomoku_board() {
  system("clear");
  puts("   A B C D E F G H I J K L M N O P Q R S");
  for (int row = 0; row < 19; row++) {
    printf("%2d ", row);
    for (int col = 0; col < 19; col++) {
      if (gomoku_board[row][col] == 0) {
        printf(". ");
      } else if (gomoku_board[row][col] == BLACK) {
        printf("● ");
      } else if (gomoku_board[row][col] == WHITE) {
        printf("○ ");
      }
    }
    printf("%-2d\n", row);
  }
  puts("   A B C D E F G H I J K L M N O P Q R S");
}

// if the game ends return 1, or not, return 0
int is_game_end() {
	int row;
  int col;
  int rock;
  int check;

	check = 0;
	
	for (row = 0; row < 19; row++) {
		for (col= 0; col < 19; col++) { 
			if (gomoku_board[row][col] == player_now_placement) {
				check++;

				for (rock = 1; rock < 5; rock++) {
					if (col + rock >= 19) {
            break;
          } else if (gomoku_board[row][col + rock] == player_now_placement) {
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
          } else if (gomoku_board[row][col - rock] == player_now_placement) {
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
          } else if (gomoku_board[row + rock][col] == player_now_placement) {
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
          } else if (gomoku_board[row + rock][col] == player_now_placement) {
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
          } else if (gomoku_board[row + rock][col + rock] == player_now_placement) {
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
          } else if (gomoku_board[row + rock][col - rock] == player_now_placement) {
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
          } else if (gomoku_board[row - rock][col + rock] == player_now_placement) {
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
          } else if (gomoku_board[row + rock][col] == player_now_placement) {
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

// pause the game when the player inputs Ctrl + C
void give_up() {
  int option;

  alarm(0);
  system("clear");

  puts("Do you really want to give up this game?");
  puts("1) yes");
  puts("2) no");
  printf(": ");
  scanf("%d", &option);
  clear_read_buffer();

  if (option == 1) {
    switch (player_now_placement) {
      case BLACK:
        end_gomoku(WHITE);
        break;
      case WHITE:
        end_gomoku(BLACK);
        break;
    }
  } else if (option == 2) {
    play_gomoku();
  }
}

// end the game when the player doesn't input anything during 30 seconds
void time_out() {
  puts("30 seconds have passed.");
  switch (player_now_placement) {
    case BLACK:
      end_gomoku(WHITE);
      break;
    case WHITE:
      end_gomoku(BLACK);
      break;
  }
}

// clear the read buffer
void clear_read_buffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}
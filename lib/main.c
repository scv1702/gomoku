/* file name: gomoku.c
 * author: 2020111854_Shin Chan-Gyu
 * datetime: 2021-12-27 21:19
 * description: main source code for the gomoku 
 */


#include "gomoku.h"

int main() {
  FILE *logo_fp;
  int option = 0;
  char gomoku_logo[BUFSIZ];

  logo_fp = fopen("./bin/logo", "r");
  fread(gomoku_logo, sizeof(char), BUFSIZ, logo_fp);

  system("clear");

  while (1) {
    printf("%s", gomoku_logo);
    printf("\nPlay a gomoku with your friend!\n");

    puts("1) Play game");
    puts("2) Scoreboard");
    puts("3) Rule");
    puts("4) Exit");
    printf(": ");
    scanf("%d", &option);
    clear_read_buffer();

    switch (option) {
      case 1:
        // when the player inputs Ctrl + C, pause the game
        signal(SIGINT, give_up);
        // when the player doesn't input anything, end the game
        signal(SIGALRM, time_out);
        init_game();
        player_now_placement = BLACK;
        play_gomoku();
        break;
      case 2:
        system("clear");
        print_scoreboard();
        break;
      case 3:
        system("clear");
        puts("How to play the gomoku?");
        puts("- Players alternate turns placing a stone of their color on an empty intersection.");
        puts("- The color of the stone is black or white.");
        puts("- Black plays first.");
        puts("- The winner is the first player to form an unbroken chain of five stones horizontally, vertically, or diagonally.");
        puts("- If the player does nothing for 30 seconds, the player will lose.");
        break;
      case 4:
        exit(0);
      default:
        break;
    }
  }
}
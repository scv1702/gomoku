#include "gomoku.h"

int main() {
  /*
  print_logo();

  signal(SIGINT, give_up);
  signal(SIGALRM, time_out);

  alarm(30);

  play_gomoku();

  end_gomoku();
  */

  print_gomoku();
  
  return 0;
}

void print_logo() {
  int logo_fp = 0;
  int option = 0;
  char gomoku_logo[BUFSIZ];

  logo_fp = open("logo", O_RDONLY);
  read(logo_fp, gomoku_logo, BUFSIZ);
  printf("%s", gomoku_logo);

  close(logo_fp);

  while (1) {
    printf("\nPlay a gomoku with your friend!\n");
    puts("1) Play game");
    puts("2) Scoreboard");
    puts("3) Exit");
    printf(": ");
    scanf("%d", &option);
    getchar();

    switch (option) {
      case 1:
        play_gomoku();
        break;
      case 2:
        print_scoreboard();
      case 3:
        exit(0);
        break;
      default:
        break;
    }
  }
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
    end_gomoku();
  } else {

  }
}

void time_out() {
  puts("30 seconds have passed. Time out!");
  end_gomoku();
  exit(0);
}
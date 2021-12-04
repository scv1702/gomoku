#include "gomoku.h"

int main() {
  print_logo();

  end_gomoku();
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

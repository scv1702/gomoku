#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void print_gomoku();

int main() {
  print_gomoku();
  return 0;
}

void print_gomoku() {
  int logo_fp;
  int len;
  char gomoku_logo[BUFSIZ];

  logo_fp = open("logo", O_RDONLY);
  read(logo_fp, gomoku_logo, BUFSIZ);
  printf("%s", gomoku_logo);

  close(logo_fp);
}
main: main.c gomoku.c
	gcc main.c gomoku.c -lcurses -o main

clean:
	rm main
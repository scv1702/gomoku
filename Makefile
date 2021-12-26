gomoku: ./lib/main.c ./lib/gomoku.c
	gcc ./lib/main.c ./lib/gomoku.c -lpthread -o ./bin/gomoku

clean:
	rm ./bin/gomoku
CC = cc
CFLAGS = -Wall -Werror

battleship.out: board.o input.o main.o ships.o stages.o
	$(CC) $(CFLAGS) board.o input.o main.o ships.o stages.o -o battleship.out

board.o: board.c board.h	
	$(CC) $(CFLAGS) -c board.c -o board.o
	
input.o: input.c input.h	
	$(CC) $(CFLAGS) -c input.c -o input.o

main.o: main.c board.h input.h stages.h
	$(CC) $(CFLAGS) -c main.c -o main.o

ships.o: ships.c ships.h
	$(CC) $(CFLAGS) -c ships.c -o ships.o

stages.o: stages.c stages.h
	$(CC) $(CFLAGS) -c stages.c -o stages.o

clean:
	rm -f *.o battleship.out

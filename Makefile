CC=gcc
OPT=`sdl-config --cflags --libs` -lSDL_image -lSDL_ttf
EXEC=test

all:$(EXEC)

input.o: input.c
	$(CC) -c input.c -o input.o

main.o: main.c
	$(CC) -c main.c -o main.o

$(EXEC): main.o input.o
	$(CC)  main.o input.o $(OPT) -o $(EXEC)

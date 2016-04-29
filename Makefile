CC=gcc
OPT2=-Wall
OPT=`sdl-config --cflags --libs` -lSDL_image -lSDL_ttf
EXEC=test

all:$(EXEC)

grid.o: grid.c
	$(CC) $(OPT2) -c grid.c -o grid.o

view.o: view.c
	$(CC) $(OPT2) -c view.c -o view.o

input.o: input.c
	$(CC) $(OPT2) -c input.c -o input.o

save.o: save.c
	$(CC) $(OPT2) -c save.c -o save.o

main.o: main.c
	$(CC) $(OPT2) -c main.c -o main.o

$(EXEC): main.o input.o view.o grid.o save.o
	$(CC) main.o input.o view.o grid.o save.o $(OPT) -o $(EXEC)

clean:
	rm -rf *.o

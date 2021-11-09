mygame.exe : main.o game.o
	gcc main.o game.o -o mygame.exe
main.o : main.c game.h
	gcc -Wall -c main.c
game.o : game.c game.h
	gcc -Wall -c game.c
clean :
	rm *.o mygame.exe
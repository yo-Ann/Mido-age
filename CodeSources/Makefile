CFLAGS=-Wall -g

all: jeu

jeu: Perso.o Case.o Monde.o Partie.o main.o Makefile
	gcc -o jeu Perso.o Case.o Monde.o Partie.o main.o

Perso.o: Perso.c
	gcc -o Perso.o -c Perso.c $(CFLAGS)

Case.o: Case.c
	gcc -o Case.o -c Case.c $(CFLAGS)

Monde.o: Monde.c
	gcc -o Monde.o -c Monde.c $(CFLAGS)

Partie.o: Partie.c
	gcc -o Partie.o -c Partie.c $(CFLAGS)

main.o: main.c
	gcc -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

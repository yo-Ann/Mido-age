#ifndef ESSAIMONDE_H
#define ESSAIMONDE_H

#include<stdio.h>
#include<stdlib.h>

#include"Case.h"

#define N 8

typedef struct neighbours{
  Character *character;
  struct neighbours *nxtNeighbour;
  struct neighbours *preNeighbour;
}Neighbour;

typedef struct listN{  //compose les liste de chateaux voisin
  Neighbour *head;
  Neighbour *tail;
  int length;
} ListN;

typedef struct world{
  struct casess *board[N][N];
  Character *initCastB;
  Character *initCastR;
  int treasureR;
  int treasureB;
  int scoreB;
  int scoreR;
  int nbBV; //nombre de victimes bleues
  int nbRV;//nombre de victimes rouges
ListN *lnr;//liste de chateaux voisins rouges
ListN *lnb;//liste de chateaux voisins bleus
}World;

typedef struct player{
  int score;
  char name[25];
}Player;

World *createWorld();

void initWorld(World *m);

void displayWorld(World *m);

void addCharacter(World *m, Character *p,Character *c);

int compareArray(int array1[], int array2[],int length);

Character *characterSuicide(World *m, Character *p,int mode);

Character *castleSuicide(World *m,Character *p,Character *c);

void move(World *m,Character *p,int choice);

int decreaseTreasure(int *treasure,int cout);


void battle(World *m,Character *h,ListN *occupant,int choice);

void freeWorld(World *m);

Neighbour *createNeighbour(Character *c);

ListN *createListN();

void displayCases(Cases *c);

void addToList(ListN *l,Character *p);

void deleteNeighbour(World *m,ListN *l, Character *p);

void freeListN(ListN *l);

void transfoC(World *m, Character *p);

Character *characterCastle(World *m,Character*p);

Neighbour *returnM(ListN* occupant);

Neighbour *returnL(ListN* occupant);

Neighbour *returnC(ListN* occupant);

Neighbour *returnW(ListN* occupant);

Neighbour *toBeBeaten(ListN* occupant);

void freeListNCase(Cases * c);

void displayCharacterN(struct listN* occupant);

Cases *createCases();

#endif

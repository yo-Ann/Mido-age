#ifndef ESSAI_H
#define ESSAI_H

#include<stdio.h>
#include<stdlib.h>


typedef struct character{
  char colour;
  char type;
  int position[2];
  int destination[2];
  char production;
  int productionTime;
  struct character*nxtCharacter;
  struct character *preCharacter;
}Character;

Character *createCharacter(int x,int y,char Colour, char type);

int productionCost(Character *p);

void displayCharacter(Character *p);

void freeCharacter(Character *p);




#endif

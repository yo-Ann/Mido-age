#ifndef ESSAIPARTIE_H
#define ESSAIPARTIE_H

#include<stdio.h>
#include<stdlib.h>

#include"Monde.h"


void characterProduction(World *m,Character *c,char colour);

void turn(World *m,char colour,int choice);

void scores(Player *playerRedFamily,Player *playerBlueFamily,World *m);

void save(World *m,char colour);

int leave(World *m,char colour);

void produce(World *m,Character* Castle,char resp[20]);

void match();

void currentMatch(char *text);

Character *actionC(World *m,Character *h, char resp[20],char colour);

Character *actionL(World *m,Character *h, char resp[20],char colour,int choice);

Character *actionW(World *m,Character *h, char resp[20],char colour,int choice);

Character *actionM(World *m,Character *h, char resp[20],char colour,int choice);

void saveBestScores(Player *player1,Player *player2);

void recalculateScores(ListN* l, Player *player);

#endif

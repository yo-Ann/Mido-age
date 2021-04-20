#ifndef ESSAICASE_H
#define ESSAICASE_H

#include<stdio.h>
#include<stdlib.h>

#include"Perso.h"


typedef struct casess{
  struct listN *occu;
}Cases;


typedef struct node{
  int x;
  int y;
}Node;


Node *createNode(int x,int y);

int distanceCalculation(int x1, int x2, int y1, int y2);

void freeNodeArray(Node* array[],int n);



#endif

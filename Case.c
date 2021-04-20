#include<stdio.h>
#include<stdlib.h>

#include"Case.h"

Node *createNode(int x,int y){ /*cree un nouveau noeud comportant les cordonnées d'une case du tableau*/
	Node *m=malloc(sizeof(Node));
	if (m==NULL){
		return NULL;
	}
	m->x=x;
  m->y=y;
	return m;
}

int distanceCalculation(int x1, int x2, int y1, int y2){ //calcul la distance euclidienne entre la position des cases autour du personnage et sa destination
  return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
}


void freeNodeArray(Node* array[],int n){
  int i;
  for(i=0;i<n;i++){
    free(array[i]);
  }
}

#include<stdio.h>
#include<stdlib.h>

#include"Perso.h"

Character *createCharacter(int x,int y,char colour, char type){
  Character *p=malloc(sizeof(Character));
  if(p==NULL) return NULL;
  p->colour=colour;
  p->type=type;
  p->position[0]=x;
  p->position[1]=y;
  p->destination[0]=x;
  p->destination[1]=y;
  p->production='\0';
  p->productionTime=1;
  p->nxtCharacter=NULL;
  p->preCharacter=NULL;

  return p;
}

void displayCharacter(Character *p){
  if(p==NULL) printf("THE CHARACTER DOES NOT EXIST\n");
  else printf("%c%c",p->type,p->colour);
}

int productionCost(Character *p){
  if(p->type=='c'){
    return 30;
  }
  if(p->type=='s'){
    return 20;
  }

  if(p->type=='m'){
    return 1;
  }
  if(p->type=='g'){
    return 5;
  }
  return 0;
}


void freeCharacter(Character *p){
  free(p);
}

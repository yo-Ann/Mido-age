#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"Monde.h"

World *createWorld(){
  int i,j;
  World *m=malloc(sizeof(World));  //on créer une structure Monde et on lui alloue un espace mémoire
  if(m==NULL) return NULL;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      m->board[i][j]=createCases();   //on parcours le tableau et on crée une Case pour chaque couple (i,j)
      if (m->board[i][j]==NULL) return NULL;
    }
  }
  if(m->board==NULL) return NULL;
  m->initCastB=NULL;
  m->initCastR=NULL;
  m->treasureR=0;  //on initialise le Monde avec des valeurs nulles
  m->treasureB=0;
  m->nbRV=0;
  m->nbBV=0;
  m->lnr=createListN();
  m->lnb=createListN();
  return m;
}

void initWorld(World *m){
  m->treasureB=50;
  m->treasureR=50;
  m->nbBV=0;
  m->nbRV=0;
  Character *r1=createCharacter(0,0,'R','c');
  Character *b1=createCharacter(N-1,N-1,'B','c');
  addCharacter(m,r1,r1);  //ici on initialise le tableau  en debut de partie en créant les personnages
  addCharacter(m,b1,b1);
  Character *r2,*b2;
  Character *r3,*b3;
  r2=createCharacter(0,1,'R','s');
  b2=createCharacter(N-1,N-2,'B','s');
  b3=createCharacter(N-2,N-1,'B','m');
  r3=createCharacter(1,0,'R','m');
  addCharacter(m,r2,m->initCastR);
  addCharacter(m,r3,m->initCastR);
  addCharacter(m,b2,m->initCastB);
  addCharacter(m,b3,m->initCastB);
}

void displayWorld(World *m){
  int i,j,k;
  printf("treasureR=%d\ntreasureB=%d\n",m->treasureR,m->treasureB);
  for(i=0;i<N;i++){
    for(k=0;k<N+1;k++){
      printf("_________");
    }
    printf("\n");
    for(j=0;j<N;j++){
      printf("| ");
      displayCases(m->board[i][j]);
      if(j==N-1) {
        printf("|\n");
        printf("|\n");
      }
    }
  }
}

int correctIndex(int x,int y){ /*verifie si les cordonnéesdu Noeud  (x,y) sont dans le tableau*/
  if((0<=x)&&(x<N)){
    if((0<=y)&&(y<N)){
    return 1;
    }
  }
  return 0;
}

Cases *createCases(){
  Cases *c=malloc(sizeof(Cases)); //on alloue un espace pour une case
  if (c==NULL)return NULL;        //on teste pour savoir si l'allocation s'est faite sans problème
  c->occu=createListN();
  return c;
}

void displayCharacterN(struct listN* occupant){
  if(occupant->head==NULL){
    printf("        ");
  }
  else{
    displayCharacter(occupant->head->character);
    if(occupant->length==2){
      printf("   ");
      displayCharacter(occupant->tail->character);
      printf(" ");
      return;
    }
    if(occupant->length>2){
      printf("...");
      displayCharacter(occupant->tail->character);
      printf(" ");
      return;
    }
    printf("      ");
  }
}

void displayCases(Cases *c){
  if(c->occu==NULL) printf("      ");
  else displayCharacterN(c->occu);
}

void addCharacter(World *m,Character *p,Character *c){
  addToList(m->board[p->position[0]][p->position[1]]->occu,p); //on met le personnage sur la case désignée dans ses paramètres
  Character *h;
  ListN *l;
  Neighbour *v;
  if(p->colour=='R'){
    l=m->lnr;   //on prend la liste des voisins rouges
    if(p->type=='c'){
      if(m->initCastR==NULL){
        m->initCastR=p; //si les deux personnages mis en arguments sont le meme chateau on ajoute le personnage comme chateau initial
      }
      addToList(l,p); //on ajoute le nouveau chateau dans la liste des voisins
      return;
    }
  }
  else{
    if(p->colour=='B'){ //c'est la meme chose que plus haut mais si la colour est bleue
      l=m->lnb;
      if(p->type=='c'){
        if(m->initCastB==NULL){
          m->initCastB=p;
        }
        addToList(l,p);
        return;
      }
    }
  }
  v=l->head;
  h=v->character;
  while((h->position[0]!=c->position[0])&&(h->position[1]!=c->position[1])){
    v=v->nxtNeighbour;  //on cherche le chateau auquel le nouveau personnage va etre lié
    h=v->character;
  }
  while(h->nxtCharacter!=NULL){
    h=h->nxtCharacter;  //on se place a la fin de la liste des personnages liés à  ce chateau
  }
  h->nxtCharacter=p;  //on incorpore le nouveau personnage  dans la liste des personnages liés au castle
  p->preCharacter=h;
}

int compareArray(int array1[], int array2[],int length){
  int i;
  for(i=0;i<length;i++){
    if(array1[i]!=array2[i]){
      return 0;
    }
  }
    return 1;
}

void battle(World *m,Character *h,ListN *occupant,int choice){
  int outcome;
  Neighbour *n,*tmp;
  Character *temp;


if(choice==1){
  while(occupant->length>0){ // on continue tant que tous les personnages déja présents sur la case ne sont pas morts.
    n=toBeBeaten(occupant);
    if(n!=NULL){
      printf("\nTHERE IS A BATTLE BETWEEN ");
      displayCharacter(h);
      printf(" AND ");
      displayCharacter(n->character);
      printf("\n--\n--\n--\n");


      printf("Who do you want win\n");
      printf("Press '1' for the first character, '2' for the second \n");
      scanf("%d",&outcome);

      if(outcome==1){
        printf("FIRST BATTLE WON BY THE FIRST CHARACTER ");
        displayCharacter(h);
        printf("\n");
        temp=n->character;
        tmp=n->nxtNeighbour;
        deleteNeighbour(m,occupant,n->character);
        if(temp->type=='c'){
          castleSuicide(m,temp,h);
        }
        else characterSuicide(m,temp,1);//suicide en cas de mort au combat

        n=tmp;
    }


    else if(outcome==2){
      printf("BATTLE WON BY THE SECOND CHARACTER  ");
      displayCharacter(n->character);
      printf("\n");
      characterSuicide(m,h,1);
      break; // arret car le personnage intru est mort pendant le combat
    }

    else{
      choice=0;
      break;
    }

  }
  }
  if(outcome==1){
addToList(occupant,h);
}
}

if(choice==0){


while(occupant->length>0){
    n=toBeBeaten(occupant);
    if(n!=NULL){
    printf("\nTHERE IS A BATTLE BETWEEN ");
    displayCharacter(h);
    printf(" AND ");
    displayCharacter(n->character);
    printf("\n--\n--\n--\n");

      int winner;
      srand (time (NULL));
      int selection = rand()%100 + 1;
      int cH=productionCost(h);
      int cN=productionCost(n->character);
      winner=selection%(cH+cN);// le reste  de la division euclidienne d'un nombre aléatoire entre 1 et 100
                      //et la somme des couts de productions des deux agents determine le vainqueur
      printf("BATTLE WON BY ");

      if(winner<=cH){ //victoire du Character h
        // supprimer n  de la  liste des voisins de la case
        displayCharacter(h);
        printf("\n");
        temp=n->character;
        tmp=n->nxtNeighbour;
        deleteNeighbour(m,occupant,n->character);
        if(temp->type=='c'){
          castleSuicide(m,temp,h);
        }
        else characterSuicide(m,temp,1);
        n=tmp;
      }

      else{//victoire du Character p
        displayCharacter(n->character);
        printf("\n");
        characterSuicide(m,h,1); //il se suicide vu qu'il a perdu le combat
        break;
        }
      }
    }

    if(occupant->length==0){
      addToList(occupant,h);
    }
    }
  }




Character *characterSuicide(World *m, Character *p,int mode){
  Character *T;
  char colour=p->colour;
  ListN *l;
  Neighbour *v;
  if(colour=='R'){
    l=m->lnr;
  }
  else{
    if(colour=='B'){
      l=m->lnb;
    }
  }
  v=l->head;
  while(v!=NULL){ //on parcours la liste des chateaux voisins
    T=v->character;
    while(T!=NULL){
      if((compareArray(p->position,T->position,2))&&(p->type==T->type)&&(compareArray(p->destination,T->destination,2))){    //on cherche le personnage parmi les lié du chateau du voisin v
        if(T->nxtCharacter==NULL)    //si c'est le dernier de sa liste de liés
           T->preCharacter->nxtCharacter=NULL;
        else{
          T->preCharacter->nxtCharacter=T->nxtCharacter;  //on enleve le personnage de sa suite de personnages liés
          T->nxtCharacter->preCharacter=T->preCharacter;
        }
          //on libere la case du personnage en dehors de cette fonction
        T=T->nxtCharacter;
        if(colour=='R')m->nbRV++;//augmente le nb de victime rouges
        if(colour=='B')m->nbBV++;//augmente le nb de victime bleues

        if(mode==0){ // si le suicide n'est pas lié à la défaite à un combat
          deleteNeighbour(m,m->board[p->position[0]][p->position[1]]->occu,p);
        }

        freeCharacter(p);
        return T;
      }
      T=T->nxtCharacter;
    }
    v=v->nxtNeighbour;
  }
  printf("THE CHARACTER IS A WARRIOR OF THE ARMY OF THE DEAD\n");
  displayCharacter(p);
  return NULL;
}


Character *castleSuicide(World *m,Character *p,Character* c){
  Character *T;
  char colour=p->colour;

  ListN *l;
  Neighbour *v;
  if(colour=='R'){ //on initialise la liste l avec la liste de chateaux voisins correspondant a la couleur du personnage a supprimer
    l=m->lnr;
  }
  else{
    if(colour=='B'){
      l=m->lnb;
    }
  }
  v=l->head;
  while(v!=NULL){ //on parcours la liste des chateaux voisins
    T=v->character;
    if((T->position[0]==p->position[0])&&(T->position[1]==p->position[1])){ //si on supprime un chateau il faut supprimer tous les personnages qui lui sont liés à part les manants qui changent d'allégence
      T=T->nxtCharacter;
      while(T!=NULL){ //on parcours les personnage qui sont liés au chateau qu'on supprime
        if((T->type=='m')&&(l->length>1)){//on etudie d'abord le cas si le personnage lié est un manant
          if(T->nxtCharacter==NULL)
            T->preCharacter->nxtCharacter=NULL;//on enleve le personnage lié de la liste
          else{
            T->preCharacter->nxtCharacter=T->nxtCharacter;
            T->nxtCharacter->preCharacter=T->preCharacter;
          }
          //on enleve le personnage lié de la case
          T->preCharacter=NULL;
          T->nxtCharacter=NULL;
          deleteNeighbour(m,m->board[T->position[0]][T->position[1]]->occu,T);
          if(colour=='R'){
            T->colour='B';
            if(compareArray(p->position,c->position,2) && p->type==c->type) addCharacter(m,T,m->initCastB); //on ajoute le manant qui a changer d'allégence aux personnages de la couleur adverse
            else addCharacter(m,T,characterCastle(m,c));
          }
          if(colour=='B'){
            T->colour='R';
            if(compareArray(p->position,c->position,2) && p->type==c->type) addCharacter(m,T,m->initCastR);
          else addCharacter(m,T,characterCastle(m,c));
          }
          T=T->nxtCharacter;
        }
        else{     //on etudie maintenant le cas d'un personnage lié qui n'est pas un manant
          deleteNeighbour(m,m->board[T->position[0]][T->position[1]]->occu,T);//on enleve le personnage lié de la case
          T=characterSuicide(m,T,0);
        }
      }   //on a finit de libérer les personnages liés

      deleteNeighbour(m,m->board[p->position[0]][p->position[1]]->occu,p); //p est le chateau que l'ont veut supprimer
      if(colour=='R'){
        m->nbRV++;//augmente le nb de victime rouges
        if(compareArray(m->initCastR->position,p->position,2)&&(v->nxtNeighbour!=NULL)){
          m->initCastR=v->nxtNeighbour->character;
        }
      }
      if(colour=='B'){
        m->nbBV++;//augmente le nb de victime bleues
        if(compareArray(m->initCastR->position,p->position,2)&&(v->nxtNeighbour!=NULL)){
          m->initCastR=v->nxtNeighbour->character;
        }
      }
      deleteNeighbour(m,l,p); //on enleve le chateau p de la liste des chateaux voisins
      freeCharacter(p);
      return NULL;//on renvoie NULL car on a supprimé tout une suite de personnages liés donc il n'y a plus de personnage suivant
    }
    v=v->nxtNeighbour;
  }
  printf("THE CASTLE IS NOT DEAD\n");
  return NULL;
}


void move(World *m,Character *p,int choice){
  if(p->destination[0]==-1||p->destination[1]==-1){
    printf("THE CHARACTER IS IMMOBILE,IT'S IMPOSSIBLE TO MOVE IT");
    return;
  }
  Node *array[8];
  int i,j,length=0;
  Node *tmp;
  Character *temp;
  int x=p->position[0];
  int y=p->position[1];
/* ajoute dans une liste de Noeud les points autour du Character p*/
  for(i=-1;i<=1;i++){
      for(j=-1;j<=1;j++){
          if ((x+i!=x)||(y!=y+j)){
            if((correctIndex(x+i,y+j))){
              array[length++]=createNode(x+i,y+j);
            }
        }
      }
    }
/*algorithme de tri par selection: tri les points autour de p en fonctionn de leurs distances à la destination de p:array[0] plus petite, array[length-1] plus grande*/
        for(i=0;i<length-1;i++){
        for(j=i+1;j<length;j++){
          if((distanceCalculation(array[i]->x,p->destination[0],array[i]->y,p->destination[1]))>(distanceCalculation(array[j]->x,p->destination[0],array[j]->y,p->destination[1]))){
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
              }
            }
          }

    if((m->board[array[0]->x][array[0]->y]->occu!=NULL)&&(m->board[array[0]->x][array[0]->y]->occu->head!=NULL)&&(m->board[array[0]->x][array[0]->y]->occu->head->character->colour!=p->colour)){// si la prochaine position est occupé par l'adversaire il y a combat
          temp=p;
          deleteNeighbour(m,m->board[p->position[0]][p->position[1]]->occu,temp);
          p->position[0]=array[0]->x;
          p->position[1]=array[0]->y;
          battle(m,p,m->board[array[0]->x][array[0]->y]->occu,choice);
        }

  else{ // le cas ou la case est libre
        temp=p;
        deleteNeighbour(m,m->board[p->position[0]][p->position[1]]->occu,temp);
        p->position[0]=array[0]->x;
        p->position[1]=array[0]->y;
        addToList(m->board[array[0]->x][array[0]->y]->occu,p);
    }

    freeNodeArray(array,length);
}


int decreaseTreasure(int *treasure,int cost){
  if(*treasure>=cost){
    *treasure-=cost;
    return 1;
  }
  else{
    printf("THERE IS NOT ENOUGH TREASURE\n");
    return 0;
  }
}


void freeWorld(World *m){
  int i,j;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      freeListNCase(m->board[i][j]); //libere toutes les cases du tableau
    }
  }
  freeListN(m->lnb); //libere la liste des chateaux voisins
  freeListN(m->lnr);
  free(m);
}

Neighbour *createNeighbour(Character *c){

  Neighbour *p=malloc(sizeof(Neighbour));
  if(p==NULL) return NULL;
  p->character=c;
  p->preNeighbour=NULL;
  p->nxtNeighbour=NULL;
  return p;
}

ListN *createListN(){
  ListN *l=malloc(sizeof(ListN));
  if(l==NULL) return NULL;
  l->length=0;
  l->head=NULL;
  l->tail=NULL;
  return l;
}

void addToList(ListN *l,Character *p){
  Neighbour *v=createNeighbour(p);
  if(l->length==0){
    l->head=v;
    l->tail=v;
    l->length++;
    return;
  }
  v->preNeighbour=l->tail;
  l->tail->nxtNeighbour=v;
  l->tail=v;
  l->length++;
}

void deleteNeighbour(World *m,ListN *l, Character *p){
  if (l->length >0){
        Neighbour *p_temp = l->head;
        int found = 0;
        while (p_temp != NULL && !found){
            if ((compareArray(p_temp->character->position,p->position,2))&&(compareArray(p_temp->character->destination,p->destination,2))&&(p->type==p_temp->character->type)){
                if (p_temp->nxtNeighbour== NULL){
                  if(p_temp->preNeighbour == NULL){
                    l->tail=NULL;
                    l->head=NULL;
                    free(p_temp);
                    l->length--;
                    found = 1;
                    return;
                  }
                  else{
                    l->tail = p_temp->preNeighbour;
                    l->tail->nxtNeighbour= NULL;
                  }
                }
                else if (p_temp->preNeighbour == NULL){
                    l->head = p_temp->nxtNeighbour;
                    l->head->preNeighbour = NULL;
                }
                else{
                    p_temp->nxtNeighbour->preNeighbour = p_temp->preNeighbour;
                    p_temp->preNeighbour->nxtNeighbour = p_temp->nxtNeighbour;
                }
                free(p_temp);
                l->length--;
                found = 1;
            }
            else{
                p_temp = p_temp->nxtNeighbour;
            }
        }
    }
}




void freeListN(ListN *l){
    Neighbour *v=l->head;
    while(v!=NULL){  //on libere chaque voisin de la liste
      Neighbour *d=v;
      v=v->nxtNeighbour;
      free(d);
    }
    free(l);

}



void transfoC(World *m, Character *p){
  int *treasure;
  if(p->colour=='R') treasure=&m->treasureR;
  if(p->colour=='B') treasure=&m->treasureB;
  if(decreaseTreasure(treasure,30)){
    Character *T;
    char colour=p->colour;
    ListN *l;
    Neighbour *v;
    if(colour=='R'){  //on initialise la liste l avec la liste des voisins de le bonne couleur
      l=m->lnr;
    }
    else{
      if(colour=='B'){
        l=m->lnb;
      }
      else return;
    }
    v=l->head;
    while(v!=NULL){ //on parcours chaque la liste des voisins jusqu'à trouver le chateau dont depend le seigneur qui vient d'etre transformé
      T=v->character;
      while(T!=NULL){//on parcours la liste des personnages dependant du chateau  v
        if((compareArray(p->position,T->position,2))&&(p->type==T->type)){ //on cherche le nouveau chateau
          if(T->nxtCharacter==NULL){//si le seigneur est en derniere position
            T->preCharacter->nxtCharacter=NULL; //on l'enleve de la liste des personnages liés au chateau
          }
          else{
            T->preCharacter->nxtCharacter=T->nxtCharacter;//on l'enleve de la liste des personnages liés au chateau
            T->nxtCharacter->preCharacter=T->preCharacter;
          }
          T->type='c';
          T->preCharacter=NULL;
          T->nxtCharacter=NULL;
          addToList(l,p);
          return;
        }
        T=T->nxtCharacter;
      }
      v=v->nxtNeighbour;
    }
  }
}


Character* characterCastle(World *m,Character*p){ // renvoie le chateau qui a produit le personnage
  ListN* l;
  Neighbour* v;
  Character* h;
  if(p->colour=='R')l=m->lnr;
  else l=m->lnb;
  v=l->head;
  while(v!=NULL){
    h=v->character;
    while (h!=NULL){
      if(compareArray(h->position,p->position,2)&&(compareArray(h->destination,p->destination,2))&&(h->type==p->type)){
        return v->character;
      }
      h=h->nxtCharacter;
  }
    v=v->nxtNeighbour;
  }

  printf("THE CASTLE DOES NOT EXIST\n");
  return NULL;
}


Neighbour *returnC(ListN* occupant){ // retourne les chateaux de la case jusqu'a ce qu'il n'y en ait plus
  Neighbour *n=occupant->head;
  while(n!=NULL){
    if(n->character->type=='c'){
      return n;
    }
    n=n->nxtNeighbour;
  }
  return n;
}

Neighbour *returnW(ListN* occupant){ // retourne les guerriers de la case jusqu'a ce qu'il n'y en ait plus
  Neighbour *n=occupant->head;
  while(n!=NULL){
    if(n->character->type=='g'){
      return n;
    }
    n=n->nxtNeighbour;
  }
  return n;

}
Neighbour *returnL(ListN* occupant){ // retourne les seigneurs de la case jusqu'à ce qu'il n'y en ait plus
  Neighbour *n=occupant->head;
  while(n!=NULL){
    if(n->character->type=='s'){
      return n;
    }
    n=n->nxtNeighbour;
  }
  return n;
}

Neighbour *returnM(ListN* occupant){ // retourne les manants de la case jusqu'à ce qu'il n'y en ait plus
  Neighbour *n=occupant->head;
  while(n!=NULL){
    if(n->character->type=='m'){
      return n;
    }
    n=n->nxtNeighbour;
  }
  return n;
}

void freeListNCase(Cases * c){
    Neighbour *v=c->occu->head;
    while(v!=NULL){  //on libere chaque voisin de la liste
      Neighbour *d=v;
      v=v->nxtNeighbour;
      if(d->character!=NULL)free(d->character);
    }
    if(c->occu!=NULL)freeListN(c->occu);
    free(c);

}

Neighbour *toBeBeaten(ListN* occupant){
  Neighbour *n;
  n=returnW(occupant);
  if(n==NULL){//il n'y a plus de seigneur dans la case
    n=returnL(occupant);
      if(n==NULL){//il n'y a plus de seigneur dans la case
        n=returnM(occupant);
        if(n==NULL){ //il n'y a plus de manant dans la case
          n=returnC(occupant);
          return n;
        }
        else return n;
      }

      else return n;
    }


  else return n;
}

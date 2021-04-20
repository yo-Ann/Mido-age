#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"Partie.h"

void characterProduction(World *m,Character *c,char colour){
  int i=c->position[0],j=c->position[1];
  Character *p=createCharacter(i,j,colour,c->production);
  addCharacter(m,p,c);
  c->production='\0';
}


Character *actionC(World *m,Character *h, char resp[20],char colour){
    Character *next = h->nxtCharacter;
  h->productionTime--;
  if(h->productionTime<=0){
    if((h->production=='m')||(h->production=='s')||(h->production=='g')){  //on crée un personnage si le temps de production est fini
      printf("?\n");
      characterProduction(m,h,colour);
    }
    else{ //si il n'y a pas de production en attente
      printf("or production ? \n");
    }
    scanf("%s",resp);
    if(!strcmp(resp,"suicide"))return castleSuicide(m,h,h);
    if(!strcmp(resp,"production")&&(h->production!='m')&&(h->production!='s')&&(h->production!='g')){ //on verifie bien que il n'y a rien en attente pour produire
      printf("lord, warrior or manant ? \n");
      scanf("%s",resp);
      produce(m,h,resp);
      }
    }
  else{
    printf("?\n");
    printf("production in  %d turn(s)\n",h->productionTime);
    scanf("%s",resp);
    if(!strcmp(resp,"suicide"))return castleSuicide(m,h,h);
  }
  return next;
}

Character *actionL(World *m,Character *h, char resp[20],char colour,int choice){
  int x=234,y=-4;//on initialise de facon à pouvoir rentrer dans la boucle plus bas
  Character *next = h->nxtCharacter;
  if((h->destination[0]!=h->position[0])||(h->destination[1]!=h->position[1])){ //on verifie si le personnage est en deplacement
    printf("?\nthe Character is going to the Case %d%d\n",h->destination[0],h->destination[1]);
    scanf("%s",resp);
    if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
    else move(m,h,choice);
  }
  else{
    printf("or movement or transformation ? \n");
    scanf("%s",resp);
    if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
    if(!strcmp(resp,"movement")){
      while((x>=N)||(x<0)||(y>=N)||(y<0)){  //on veut des coordonnées existantes
        printf("give coordonates between 0 and 7 to move towards the case : \n");
        printf("height : ");
        scanf("%d",&x);
        printf("length : ");
        scanf("%d",&y);
      }
      h->destination[0]=x;
      h->destination[1]=y;
      move(m,h,choice);
    }
    if(!strcmp(resp,"transformation")) transfoC(m,h);
  }
  return next;
}

Character *actionW(World *m,Character *h, char resp[20],char colour,int choice){ //fonction similaire a actionL sans possibilité de transformation
  int x=234,y=-4;
  Character *next = h->nxtCharacter;
  if((h->destination[0]!=h->position[0])||(h->destination[1]!=h->position[1])){
    printf("?\nthe Character is going to the Case %d%d\n",h->destination[0],h->destination[1]);
    scanf("%s",resp);
    if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
    else move(m,h,choice);
  }
  else{
    printf("or movement ?\n");
    scanf("%s",resp);
    if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
    if(!strcmp(resp,"movement")){
      while((x>=N)||(x<0)||(y>=N)||(y<0)){
        printf("give coordonates between 0 and 7 to move towards the case : \n");
        printf("height : ");
        scanf("%d",&x);
        printf("length : ");
        scanf("%d",&y);
      }
      h->destination[0]=x;
      h->destination[1]=y;
      move(m,h,choice);
    }
  }
  return next;
}

Character *actionM(World *m,Character *h, char resp[20],char colour,int choice){
  int x=234,y=-4;
    Character *next = h->nxtCharacter;
  if((h->destination[0]<0)&&(h->destination[1]<0)){ //on augmente le tresor si le mamant est immobile
    if(colour=='R') m->treasureR++;
    if(colour=='B') m->treasureB++;
    printf("?\n");
    scanf("%s",resp); //on donne la possibilité de se suicider
    if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
  }
  else{ //si le manant n'est pas immobile
    if((h->destination[0]!=h->position[0])||(h->destination[1]!=h->position[1])){ //si il est en déplacement
      printf("?\nthe Character is going to the Case %d%d\n",h->destination[0],h->destination[1]);
      scanf("%s",resp);
      if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
      else move(m,h,choice);
    }

    else{ //si il n'est ni en déplacement ni immobile
      printf("or movement or immobility ? \n");
      scanf("%s",resp);
      if(!strcmp(resp,"suicide")) return characterSuicide(m,h,0);
      if(!strcmp(resp,"movement")){
        while((x>=N)||(x<0)||(y>=N)||(y<0)){
          printf("give coordonates between 0 and 7 to move towards the case : \n");
          printf("height : ");
          scanf("%d",&x);
          printf("length : ");
          scanf("%d",&y);
        }
        h->destination[0]=x;
        h->destination[1]=y;
        move(m,h,choice);

      }
      if(!strcmp(resp,"immobility")){
        h->destination[0]=-1;
        h->destination[1]=-1;
      }
    }
  }
  return next;
}


void turn(World *m,char colour,int choice){
  Character *h;
  char resp[20];
  ListN *l;
  Neighbour *v,*n;
  if(colour=='R') l=m->lnr;
  if(colour=='B') l=m->lnb;
  v=l->head;
  while(v!=NULL){//on parcours chaque chateau voisin
    h=v->character;
    n=v->nxtNeighbour;
    while(h!=NULL){//on parcours tous les personnages liés au chateau
      if((m->lnb->length==0)||(m->lnr->length==0)) return; //si une couleur n'a plus de chateau la partie est finie
      if(colour=='R') printf("\n\n   RED");
      if(colour=='B') printf("\n\n   BLUE");
      printf(" TURN\n\n");
      displayWorld(m);
      displayCharacter(h);
      printf(" of the  Case %d%d : suicide or nothing ",h->position[0],h->position[1]);//on donne le personnage à qui on va donner une action à faire
      if(h->type=='c'){ //on renvoie à la fonction correspondant au type du personnage qui joue
        h=actionC(m,h,resp,colour);
        if((m->lnb->length==0)||(m->lnr->length==0)) return;

        continue;
      }
      if(h->type=='s'){
        h=actionL(m,h,resp,colour,choice);
        continue;
      }
      if(h->type=='g'){
        h=actionW(m,h,resp,colour,choice);
        continue;
      }
      if(h->type=='m'){
        h=actionM(m,h,resp,colour,choice);
        continue;
      }
    }
    v=n;//si le chateau précédant vient de se suicider cela met une segmentation fault car v n'existe plus.
  }
}

void scores(Player *playerRedFamily,Player *playerBlueFamily,World *m){
  int i,j;
  Neighbour *n;
  for(i=0;i<N;i++){ //en fonction du type des personnages restant, on augmente le score de l'équipe
    for(j=0;j<N;j++){

      if(m->board[i][j]->occu!=NULL){

        n=m->board[i][j]->occu->head;

          while(n!=NULL){
            if(n->character->colour=='R'){

            if(n->character->type=='c'){
              playerRedFamily->score+=50;
            }
            if(n->character->type=='s'){
              playerRedFamily->score+=30;
            }
            if(n->character->type=='g'){
              playerRedFamily->score+=10;
            }
            if(n->character->type=='m'){
              playerRedFamily->score+=2;
            }
          }
          if(n->character->colour=='B'){

            if(n->character->type=='c'){
              playerBlueFamily->score+=50;
            }
            if(n->character->type=='s'){
              playerBlueFamily->score+=30;
            }
            if(n->character->type=='g'){
              playerBlueFamily->score+=10;
            }
            if(n->character->type=='m'){
              playerBlueFamily->score+=2;
            }
          }
          n=n->nxtNeighbour;
        }
      }
    }
  }

  if(m->lnb->length==0){
  playerRedFamily->score+=m->nbBV*15;
  playerBlueFamily->score+=m->nbRV*5;
}
else if(m->lnr->length==0){
  playerRedFamily->score+=m->nbBV*15;
  playerBlueFamily->score+=m->nbRV*5;
}

  printf("%s,Your score is %d\n",playerRedFamily->name,playerRedFamily->score);
  printf("%s,Your score is %d\n",playerBlueFamily->name,playerBlueFamily->score);
}


void save(World *m,char colour){
  FILE *f;
  char resp[20];
  Character *p;
  Neighbour *v;
  do{//on demande un nom pour la sauvegarde finissant par .got
    printf("name of the back-up file finishing by the extension .got : \n");
    scanf("%s",resp);
  }
  while((resp[strlen(resp)]!='\0')&&(resp[strlen(resp)-1]!='t')&&(resp[strlen(resp)-2]!='o')&&(resp[strlen(resp)-3]!='g')&&(resp[strlen(resp)]!='.'));
  f=fopen(resp,"w");
  if(colour=='R'){ //on écrit la colour qui doit jouer la premiere
    fprintf(f,"%c %d\n",colour,m->treasureR);
    fprintf(f,"B %d",m->treasureB);
  }
  if(colour=='B'){
    fprintf(f,"%c %d\n",colour,m->treasureB);
    fprintf(f,"R %d",m->treasureR);
  }
  v=m->lnb->head; //on sauvegarde d'abord les bleus
  while(v!=NULL){//on parcours tous les chateaux bleus
    p=v->character;
    while(p!=NULL){//on sauvergarde les personnage dépendant du chateau
      if(p->type=='c'){
        fprintf(f,"\nB c %d %d %c %d",p->position[0],p->position[1],p->production,p->productionTime);
      }
      else{
        fprintf(f,"\nB %c %d %d %d %d",p->type,p->position[0],p->position[1],p->destination[0],p->destination[1]);
      }
      p=p->nxtCharacter;
    }
    v=v->nxtNeighbour;
  }
  v=m->lnr->head; //on fait la meme chose pour les rouges
  while(v!=NULL){
    p=v->character;
    while(p!=NULL){
      if(p->type=='c'){
        fprintf(f,"\nR c %d %d %c %d",p->position[0],p->position[1],p->production,p->productionTime);
      }
      else{
        fprintf(f,"\nR %c %d %d %d %d",p->type,p->position[0],p->position[1],p->destination[0],p->destination[1]);
      }
      p=p->nxtCharacter;
    }
    v=v->nxtNeighbour;
  }
  fclose(f);
}

void saveBestScores(Player *player1,Player *player2){
  FILE *f;
  Player names[12]; //cree une liste de Joueur
  Player temp;
  int i=0,j=0,k;
  int tmp;
  int r,mark=0;
  Player p1;
  Player p2;
  char rank[2];
  char name[25];

  p1.score=player1->score;
  strcpy(p1.name,player1->name);

  p2.score=player2->score;
  strcpy(p2.name,player2->name);

  printf("\n\n");

  f=fopen("bestScores.got","r");
  if(f==NULL) return;
  fscanf(f,"THE BEST SCORES\n");
  r=fscanf(f,"%s %s %d\n",rank,name,&tmp);//verifie que le fichier n'est pas vide
  if(r==EOF){
    mark=1;
    fclose(f);//sortie si vide
  }
  else{ //sinon lire le fichier normalement
    for(i=0;i<10;i++){
      if(r!=EOF){
        strcpy(names[j].name,name);
        names[j++].score=tmp;
      }
      r=fscanf(f,"%s %s %d\n",rank,name,&tmp);
    }
    fclose(f);
  }

if(p1.score>p2.score){
names[j]=p1;
names[++j]=p2;
}
else{
  names[j]=p2;
  names[++j]=p1;
}

  if(mark==1){// ecriture dans le Cas  où le fichier est vide au départ

    f=fopen("bestScores.got","w");
    if(f==NULL) return;
    fprintf(f,"THE BEST SCORES\n");
    printf("1.  %s  %d\n",names[0].name,names[0].score);
    fprintf(f,"1.  %s  %d\n",names[0].name,names[0].score);
    printf("2.  %s  %d\n",names[1].name,names[1].score);
    fprintf(f,"2.  %s  %d\n",names[1].name,names[1].score);
    fclose(f);
  }

  else{//ecriture dans le Cas où le fichier contient  au moins une note


    for(i=1;i<=j+1;i++){
      for(k=0;k<j;k++){
        if(names[k].score < names[k+1].score){
            temp= names[k];
            names[k] = names[k+1];
            names[k+1] = temp;
          }
        }
      }


    if(j>=10){// cas où il y deja 10 scores dans le fichier
      j=9;
    }

    f=fopen("bestScores.got","w");
    if(f==NULL){
      return;
    }


    fprintf(f,"THE BEST SCORES\n");
    for(k=0;k<=j;k++){
        printf("%d.  %s  %d\n",k+1,names[k].name,names[k].score);
        fprintf(f,"%d.   %s   %d\n", k+1,names[k].name,names[k].score);
      }
      fclose(f);
  }

  free(player1);
  free(player2);
}


int leave(World *m,char colour){
  char resp[20];
  printf("Do you want to save the match, yes or no ?\n");
  scanf("%s",resp);
  if(!strcmp(resp,"yes")) save(m,colour);
  if(colour == 'B') return 2;
  else return 1;
}

void match(){//fonction utilisée pour commencer une nouvelle partie
  char colour;
  char name[25];
  Player *playerRedFamily=malloc(sizeof(Player));
  Player *playerBlueFamily=malloc(sizeof(Player));
  playerRedFamily->score=0;
  playerBlueFamily->score=0;

  printf("For which family to you want to battle : 'R' for the red Lannisters, 'B' for the blue Starks\n");
  scanf("%c",&colour);

  if(colour=='R'){
    printf("please enter your name\n");
    scanf("%s",name);
    strcpy(playerRedFamily->name,name);
    printf("The other player is Blue\n");
    printf("please enter your name\n");
    scanf("%s",name);
    strcpy(playerBlueFamily->name,name);
  }
  else if(colour=='B'){
    printf("please enter your name\n");
    scanf("%s",name);
    strcpy(playerBlueFamily->name,name);
    printf("The other player is Red\n");
    printf("please enter your name\n");
    scanf("%s",name);
    strcpy(playerRedFamily->name,name);
  }
  else{
    printf("This colour doesn't exist\n");
    free(playerRedFamily);
    free(playerBlueFamily);
    return;
  }


  char vote[4];
  int choice;
  char response[8];
  int q=0;
  printf("Do you want to choose the outcome of the different battle ?: yes or no \n");
  scanf("%s",vote);

  if(!strcmp(vote,"yes"))choice=1;
  else if(!strcmp(vote,"no"))choice=0;
  else choice=0;

  int ct=0;
  World *m=createWorld();
  initWorld(m);
  while((m->lnb->length!=0)&&(m->lnr->length!=0)){ //tant que les deux couleurs ont des chateaux
    if(ct==0){ //ct permet de faire jouer alternativement les deux couleurs
      printf("WRITE 'leave'(you can still save when leaving) TO LEAVE THE MATCH OR 'save' TO KEEP YOUR DATA\n");
      scanf("%s",response);
      if(!strcmp(response,"leave")){
        q=leave(m,'R');
        break;
      }
      if(!strcmp(response,"save"))save(m,'R');
      turn(m,'R',choice);
      ct++;
    }
    else{
      printf("WRITE 'leave'(you can still save when leaving) TO LEAVE THE MATCH OR 'save' TO KEEP YOUR DATA\n");
      scanf("%s",response);
      if(!strcmp(response,"leave")){
        q=leave(m,'B');
        break;
      }
      if(!strcmp(response,"save"))save(m,'B');
      turn(m,'B',choice);
      ct--;
    }
  }
  if((m->lnb->length==0)||(q==2)) {
      printf("\nTHE RED HOUSE WINS !!\n\n");
  }
  else{
        printf("\nTHE BLUE HOUSE WINS !!\n\n");
    }

  scores(playerRedFamily,playerBlueFamily,m);
  saveBestScores(playerRedFamily,playerBlueFamily);
  freeWorld(m);
  return;
}

void currentMatch(char *texte){ //utiliser pour reprendre une partie sauvergardée
  FILE *f;
  char colour,ty,typrod;
  char name[25];
  int ct,treasureB,treasureR,px,py,dx,dy,tmp;
  Player *playerRedFamily=malloc(sizeof(Player));
  Player *playerBlueFamily=malloc(sizeof(Player));
  playerRedFamily->score=0;
  playerBlueFamily->score=0;
  f=fopen(texte,"r");
  fscanf(f,"%c",&colour);
  if(colour=='R'){ //si le premier a devoir jouer est le joueur rouge
    ct=0;  //ct=0 indique que c'est au rouge de jouer
    fscanf(f,"%d\n",&treasureR);
    fscanf(f,"%c ",&ty);
    fscanf(f,"%d\n",&treasureB);
  }
  else{
    ct=1;
    fscanf(f,"%d\n",&treasureB);
    fscanf(f,"%c ",&ty);
    fscanf(f,"%d\n",&treasureR);
  }
  if(colour=='R'){
    printf("please re-enter your name you were battling for the LANNISTERs\n");
    scanf("%s",name);
    strcpy(playerRedFamily->name,name);
    printf("The other player was battling for the STARKs\n");
    printf("please re-enter your name\n");
    scanf("%s",name);
    strcpy(playerBlueFamily->name,name);
  }
  else if(colour=='B'){
    printf("please re-enter your name you were battling for the STARKs\n");
    scanf("%s",name);
    strcpy(playerBlueFamily->name,name);
    printf("The other player was battling for the LANNISTERs\n");
    printf("please re-enter your name\n");
    scanf("%s",name);
    strcpy(playerRedFamily->name,name);
  }
  Character *p,*c;
  World *m=createWorld(); //on crée un monde vide
  m->treasureR=treasureR; //on initialise le monde
  m->treasureB=treasureB;
  while(!feof(f)){ //on parcours chaque ligne du fichier
    fscanf(f,"%c ",&colour);
    fscanf(f,"%c ",&ty);
    fscanf(f,"%d ",&px);
    fscanf(f,"%d ",&py);
    p=createCharacter(px,py,colour,ty); //on crée chaque personnage
    if(p->type=='c'){ //on differencie les chateaux des autres car les valeurs sauvegardées ne sont pas les memes
      fscanf(f,"%c ",&typrod);
      fscanf(f,"%d\n",&tmp);
      p->production=typrod;
      p->productionTime=tmp;
      c=p; //c mémorise le chateau juste au dessus du personnage
    }

    else{
      fscanf(f,"%d ",&dx);
      fscanf(f,"%d\n",&dy);
      p->destination[0]=dx;
      p->destination[1]=dy;
    }
    if(colour=='R'){
      if((p->type=='c')&&(m->initCastR!=NULL)) addCharacter(m,p,m->initCastR);//si ce n'est pas le premier chateau rencontré
      else addCharacter(m,p,c);//si c'est le 1er chateau rencontré on le met comme chateau initial
    }
    if(colour=='B'){
      if((p->type=='c')&&(m->initCastB!=NULL)) addCharacter(m,p,m->initCastB);
      else addCharacter(m,p,c);
    }
  }
  fclose(f);//on a fini l'initialisation

  char vote[4];
  int choice,q=0;
  char response[8];
  printf("Do you want to choose the outcome of the different battle ?: yes or no \n");
  scanf("%s",vote);

  if(!strcmp(vote,"yes"))choice=1;
  else if(!strcmp(vote,"no"))choice=0;
  else choice=0;
  recalculateScores(m->lnb,playerBlueFamily);
  recalculateScores(m->lnr,playerRedFamily);
  while((m->lnb->length!=0)&&(m->lnr->length!=0)){ //tant que les deux couleurs ont des chateaux

    if(ct==0){ //ct permet de faire jouer alternativement les deux couleurs
      printf("WRITE 'leave'(you can still save when leaving) TO LEAVE THE MATCH OR 'save' TO KEEP YOUR DATA\n");
      scanf("%s",response);
      if(!strcmp(response,"leave")){
        q=leave(m,'R');
        break;
      }
      if(!strcmp(response,"save"))save(m,'R');
      turn(m,'R',choice);
      ct++;
    }
    else{
      printf("WRITE 'leave'(you can still save when leaving) TO LEAVE THE MATCH OR 'save' TO KEEP YOUR DATA\n");
      scanf("%s",response);
      if(!strcmp(response,"leave")){
        q=leave(m,'B');
        break;
      }
      if(!strcmp(response,"save"))save(m,'B');
      turn(m,'B',choice);
      ct--;
    }
  }
  if((m->lnb->length==0)||(q==2)) {
      printf("\nTHE RED HOUSE WINS !!\n\n");
  }
  else{
        printf("\nTHE BLUE HOUSE WINS !!\n\n");
    }
  scores(playerRedFamily,playerBlueFamily,m);
  saveBestScores(playerRedFamily,playerBlueFamily);
  freeWorld(m);
  return;
}


void produce(World *m,Character* castle,char resp[20]){//cette fonction teste juste si il y a assez d'argent pour créer le personnage

  int *tresor;                                          //Et si il y a assez de tresor , initialise le paramètre production du chateau
  if(castle->type!='c'){
    return;
  }
  if(castle->colour=='R') tresor=&m->treasureR;
  if(castle->colour=='B') tresor=&m->treasureB;
  if(!strcmp(resp,"lord")){
    if(decreaseTreasure(tresor,20)){
      castle->productionTime=6;
      castle->production='s';
    }
  else{
    printf("IT'S IMPOSSIBLE TO CREATE A LORD");
  }
}

  if (!strcmp(resp,"manant")){
      if(decreaseTreasure(tresor,1)){
        castle->productionTime=2;
        castle->production='m';
  }
  else{
    printf("IT'S IMPOSSIBLE TO CREATE A MANANT");
  }
}

  if(!strcmp(resp,"warrior")){
    if(decreaseTreasure(tresor,5)){
      castle->productionTime=4;
      castle->production='g';
    }
    else{
      printf("IT'S IMPOSSIBLE TO CREATE A WARRIOR");
    }
  }
}


void recalculateScores(ListN* l,Player *player){
  Neighbour*v;
  Character *h;
  v=l->head;
  while(v!=NULL){
    h=v->character;
    while(h!=NULL){
      if(h->type=='c'){
        player->score+=30;
      }
      if(h->type=='s'){
        player->score+=20;
      }
      if(h->type=='g'){
        player->score+=5;
      }
      if(h->type=='m'){
        player->score+=1;
      }
      h=h->nxtCharacter;
  }
  v=v->nxtNeighbour;
}
}

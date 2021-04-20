#include<stdio.h>
#include<stdlib.h>

#include"Partie.h"

int main(int argc, char *argv[]){
  if(argc==2){
    currentMatch(argv[1]);
  }
  if(argc==1){
    match();
  }
  if(argc>2){
    printf("TOO MANY FILES GIVEN\n");
  }
  return 0;
}

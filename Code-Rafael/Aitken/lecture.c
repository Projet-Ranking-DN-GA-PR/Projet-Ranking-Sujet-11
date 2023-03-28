#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lecture.h"

int nb_sommet(int argc, char *argv[], FILE *f) {
  
  int nbsommet = 0;
  int error;
  
  error = fscanf(f, "%d", &nbsommet);
  
  if (error == EOF){
    printf("\nerreur scan\n");
    exit(1);
  }
  
  return nbsommet;
}

int nb_arc(int argc, char *argv[], FILE *f) {
  
  int nbarc = 0;
  int error;
  
  error = fscanf(f, "%d", &nbarc);

  if (error == EOF){
    printf("\nerreur scan\n");
    exit(1);
  }
  
  return nbarc;
}

void stocker_arc(int ligne, FILE *f, ARC *S,int *testfils){

  ARC *arc;

  arc = malloc(sizeof(ARC));
    if (arc == NULL) {
      printf("\n\nPB malloc \n\n");
      exit(2);
    }
  
  arc->pere = ligne;
  double poid = 0;
  int fils = 0;

  int error;
  
  error = fscanf(f, "%d", &fils);

  if (error == EOF){
    printf("\nerreur scan\n");
    exit(1);
  }

  error = fscanf(f, "%lf", &poid);

  if (error == EOF){
    printf("\nerreur scan\n");
    exit(1);
  }

  *testfils = fils;

  arc->poid = poid;
  
  if (S[fils-1].pere == 0){

    S[fils-1] = *arc;
    //printf("FLAG 11");
  }
    
  else{
    
    if (S[fils-1].suivant == NULL){

      S[fils-1].suivant = arc;
      //printf("FLAG 22");
    }
      
    else{
      arc->suivant = S[fils-1].suivant;
      S[fils-1].suivant = arc;
     // printf("FLAG 33");
    }
    
  }

  //printf("\n%d arc :\n poid : %f\n pere : %d\nfils : %d\n", 1, arc->poid,arc->pere, *testfils);
  
}

void stocker_ligne(FILE *f, ARC *S, double vecteurf[]){
  int ligne = 0;
  int deg = 0;
  int error;
  
  error = fscanf(f, "%d", &ligne);

  if (error == EOF){
    printf("\nerreur scan\n");
    exit(1);
  }

  error = fscanf(f, "%d", &deg);

  if (error == EOF){
    printf("\nerreur scan\n");
    exit(1);
  }

  //initialise le vecteur f en fonction des degré des sommets
  if (deg == 0){
    vecteurf[ligne-1] = 1;
  }
  else{
    vecteurf[ligne-1] = 0;
  }
  

  //printf("\nnumero de ligne : %d   degré du sommet : %d\n\n", ligne, deg);
  
  for (int i = 0; i<deg; i++){
    int testfils = 0;
    stocker_arc(ligne, f, S, &testfils);
    }
  
}

void affichage_ArcsEntrants(int indice, ARC *S){

  int i = 1;
  ARC *a;

  a= &S[indice-1];

  printf("\nSommet numéro : %d\n",indice);
  
  while(a != NULL){
    printf(" arc numero %d =>  pere : %d ; poid : %.15lf\n",i, a->pere, a->poid);
    a=a->suivant;
    i++;
  }
  
}

void affiche_time(clock_t current_time) {

  clock_t test = clock();
  test = test - current_time;
  printf("%ld min %ld sec %ld ms\n",test/(CLOCKS_PER_SEC*60), (test/CLOCKS_PER_SEC)%60, (test*1000/CLOCKS_PER_SEC)%1000 );
  printf("Finished in %ld µs\n\n",(test*1000000/CLOCKS_PER_SEC) );
}

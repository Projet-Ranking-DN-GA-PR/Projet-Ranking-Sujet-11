#include <stdio.h>
#include <stdlib.h>

struct Arc {
  int pere;
  double poid;
  struct Arc *suivant;
};

typedef struct Arc ARC;

int nb_sommet(int argc, char *argv[], FILE *f);

int nb_arc(int argc, char *argv[], FILE *f);

void stocker_arc(int ligne, FILE *f, ARC *S[], int *testfils);

void stocker_ligne(FILE *f, ARC *S[], double vecteurf[]);

void affichage_ArcsEntrants(int indice, ARC *S[]);

void affiche_time(clock_t current_time);
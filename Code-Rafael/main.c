#include <stdio.h>
#include <time.h>

#include "calcul.h"

#define EPSILON  0.00000001
#define alpha 0.85

int main(int argc, char *argv[]) {


  /***************LECTURE DU FICHIER (MATRICE) ET STOCKAGE EN LISTE CHAINEE (COLONNE)**************************/

  clock_t clock_start = clock(); 


  FILE *f;
  f = fopen(argv[1], "r");


  // nbsom = nombre de sommet | nbarc = nombre d'arc
  int nbsom = 0;
  int nbarc = 0;

  nbsom = nb_sommet(argc, argv, f);
  nbarc = nb_arc(argc, argv, f);

  printf("\nnb sommet : %d\n nb arcs : %d\n", nbsom, nbarc);

  printf("\n\n\n----------Lecture et stockage de la Matrice en cours----------\n\n\n");

  double vecteurf[nbsom];


  //créer le tableau des listes chainées de chaque sommet
  //un noeud représente un arc et contient le pere dudit sommet, ainsi que le poid de l'arc
  ARC *Sommets[nbsom];

  for (int i = 0; i < nbsom; i++) {

    Sommets[i] = malloc((12) * sizeof(ARC));
    
    if (Sommets[i] == NULL) {
      printf("\n\nPB malloc %d\n\n", i);
      exit(2);
    }

  }


  //lis le fichier ligne par ligne, une ligne par sommet
  for (int i = 0; i < nbsom; i++) {

    stocker_ligne(f, Sommets, vecteurf);
  }

  //affiche_vecteur(nbsom, vecteurf);

  fclose(f);

  printf("\n\n\nLecture et stockage terminé\n\n");

  printf("durée : ");
  affiche_time(clock_start);  
  
  //affiche le résultat du stockage en liste chainée 
  /*for (int i = 0; i < nbsom; i++) {
    affichage_ArcsEntrants(i + 1, Sommets);
  }*/


/***************DEBUT DU CALCUL**************************/

  clock_t clock_calc = clock();

  //vecteur x :

  //double x[] = {0.1,0.1,0.2,0,0.1,0.15,0.15,0.2};
  //double x[] = {0.125,0.125,0.125,0.125,0.125,0.125,0.125,0.125};


  //double x[nbsom];
  double *x;
  x = malloc((nbsom) * sizeof(double));
    
    if (x == NULL) {
      printf("\n\nPB malloc\n\n");
      exit(2);
    }
  
  //double nx[nbsom];

  double *nx;
  nx = malloc((nbsom) * sizeof(double));
    
    if (x == NULL) {
      printf("\n\nPB malloc\n\n");
      exit(2);
    }

  //initialise les vecteurs e et x à 1/N pour toutes les valeurs, et fait pareil pour nx.
  for(int i = 0 ; i<nbsom ; i++){
    
    x[i] = 1.0/nbsom;
    nx[i] = x[i];

  }


  //diffnorme = cf fontion 'diff_norme' dans calcul.c | compteur = nb itération de algo des puissance

  double diffnorme = 1;
  int compteur = 1;


  //algo des puissance et/ou avec la précision de Google, jusq'à atteindre epsilon (convergence)

  printf("\n\n\n----------Calcul de convergence de la Matrice en cours----------\n\n\n");

  printf("\nprécision Epsilon : %.2e", EPSILON);
  printf("\nvaleur d'alpha : %.2lf\n",alpha);
  

  while ( diffnorme > EPSILON ){

  //calcul du scalaire s tq : s = x*f-transposé
  double s = 0;
  s = scalaire_s(nbsom, x, vecteurf);

  //calcul principale cf calcul.c

  //produit_vecteur_matrice(x, Sommets, nbsom, nx);
  calcul(alpha, nbsom, x, s, nx, Sommets);

  //affiche_vecteur(nbsom, nx);

  //calcul la norme de la différence en valeur absolu de nx - x
  diffnorme = diff_norme(nbsom, x, nx);
  //printf("\n\nvaleur norme : %.12lf",diffnorme);

  //printf("\n diff norme : %.9lf\n",diffnorme);
  compteur++;

  }
  
  printf("\n\n\nCalcul de convergence de la Matrice terminé\n\n");

  printf("\nnombre de tour de boucle avant convergence : %d\n\n",compteur);

  printf("durée : ");
  affiche_time(clock_calc);

  printf("\n\ndurée totale du programme : ");
  affiche_time(clock_start);

  //affiche le résultat après convergence 
  //affiche_vecteur(nbsom, nx);

  return 0;
}

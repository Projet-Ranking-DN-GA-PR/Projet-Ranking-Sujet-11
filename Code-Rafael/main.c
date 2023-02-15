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

  int nbsom = 0;  //nombre de sommet
  int nbarc = 0;  //nombre d'arc

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

  
  for (int i = 0; i < nbsom; i++) {

    stocker_ligne(f, Sommets, vecteurf); //lis le fichier ligne par ligne, une ligne par sommet
  }

  //affiche_vecteur(nbsom, vecteurf);

  fclose(f);

  printf("\n\n\nLecture et stockage terminé\n\n");

  printf("durée : ");
  affiche_time(clock_start);  
  
  
  /*for (int i = 0; i < nbsom; i++) {
    affichage_ArcsEntrants(i + 1, Sommets); //affiche le résultat du stockage en liste chainée 
  }*/


/***************DEBUT DU CALCUL**************************/

  clock_t clock_calc = clock();

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

  
  for(int i = 0 ; i<nbsom ; i++){
    
    x[i] = 1.0/nbsom; //initialise les vecteurs x et nx à 1/N pour toutes les valeurs.
    nx[i] = x[i];

  }

  double diffnorme = 1.0; // diff entre étape k et étape k+1, indique si on a converger ou non.
  int compteur = 0; //nb d'itération de l'algo des puissance avant convergence.


  //algo des puissance avec/sans la précision de Google, jusq'à atteindre epsilon (convergence).

  printf("\n\n\n----------Calcul de convergence de la Matrice en cours----------\n\n\n");

  printf("\nprécision Epsilon : %.2e", EPSILON);
  printf("\nvaleur d'alpha : %.2lf\n",alpha);
  

  while ( diffnorme > EPSILON ){
    
    diffnorme = 0.0;

    //produit_vecteur_matrice(x, Sommets, nbsom, nx); //calcul du produit sans la précision Google.

    double s = 0.0;
    s = scalaire_s(nbsom, x, vecteurf); //scalaire s servant dans la précision Google.

    calcul(alpha, nbsom, x, s, nx, Sommets);   //calcul principale avec la précision Google.

    //affiche_vecteur(nbsom, nx); //affiche le vecteur résultat

    
    diffnorme = diff_norme(nbsom, x, nx); //calcul la norme de la différence en valeur absolu de nx - x
    //printf("\n\nvaleur norme : %.12lf",diffnorme);

    compteur++;
  }
  
  printf("\n\n\nCalcul de convergence de la Matrice terminé\n\n");

  printf("\nnombre de tour de boucle avant convergence : %d\n\n",compteur);

  printf("durée : ");
  affiche_time(clock_calc);

  printf("\n\ndurée totale du programme : ");
  affiche_time(clock_start);

  //affiche_vecteur(nbsom, nx); //affiche le résultat après convergence 

  return 0;
}

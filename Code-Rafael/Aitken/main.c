#include <stdio.h>
#include <time.h>

#include "calcul.h"

#define EPSILON  0.00000001
#define alpha 0.85

int main(int argc, char *argv[]) {


  /***************LECTURE DU FICHIER (MATRICE) ET STOCKAGE EN LISTE CHAINEE (COLONNE)**************************/

  clock_t clock_start = clock(); 

  char *nameFic = argv[1];
  printf("\n\n\n\n GRAPHE TRAITÉ PRÉSENTEMENT :\n\n%s\n\n",nameFic);

  FILE *f;
  f = fopen(argv[1], "r");

  int nbsom = 0;  //nombre de sommet
  int nbarc = 0;  //nombre d'arc

  nbsom = nb_sommet(argc, argv, f);
  nbarc = nb_arc(argc, argv, f);

  printf("\nnb sommet : %d\n nb arcs : %d\n", nbsom, nbarc);

  printf("\n\n\n----------Lecture et stockage de la Matrice en cours----------\n\n\n");

  //double vecteurf[nbsom];
  double *vecteurf;
  vecteurf = malloc((nbsom) * sizeof(double));
    
    if (vecteurf == NULL) {
      printf("\n\nPB malloc\n\n");
      exit(2);
    }


  //créer le tableau des listes chainées de chaque sommet
  //un noeud représente un arc et contient le pere dudit sommet, ainsi que le poid de l'arc
  ARC *Sommets;

  Sommets = malloc( nbsom * sizeof(ARC));
  
  if (Sommets == NULL) {
    printf("\n\nPB malloc\n\n");
    exit(2);
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

  double *resPageRank;
  resPageRank = malloc((nbsom) * sizeof(double));
    
  if (resPageRank == NULL) {
    printf("\n\nPB malloc\n\n");
    exit(2);
  }

  double *resAitken;
  resAitken = malloc((nbsom) * sizeof(double));
    
  if (resAitken == NULL) {
    printf("\n\nPB malloc\n\n");
    exit(2);
  }

  for(int i = 0;i<2;i++){

    clock_t clock_calc = clock();

    //double x[nbsom];
    double *x;
    x = malloc((nbsom) * sizeof(double));
      
      if (x == NULL) {
        printf("\n\nPB malloc\n\n");
        exit(2);
      }

    double *xk1;
    xk1 = malloc((nbsom) * sizeof(double));
      
      if (xk1 == NULL) {
        printf("\n\nPB malloc\n\n");
        exit(2);
      }

    double *xk2;
    xk2 = malloc((nbsom) * sizeof(double));
      
      if (xk2 == NULL) {
        printf("\n\nPB malloc\n\n");
        exit(2);
      }

    
    for(int i = 0 ; i<nbsom ; i++){
      
      x[i] = 1.0/nbsom; //initialise les vecteurs x et nx à 1/N pour toutes les valeurs.
      xk1[i] = x[i];
      xk2[i] = x[i];

    }

    calcul(alpha, nbsom, x, xk1, Sommets, vecteurf); //init xk1 = x1

    calcul(alpha, nbsom, xk1, xk2, Sommets, vecteurf); // init xk2 = x2

    double diffnorme = 1.0; // diff entre étape k et étape k+1, indique si on a converger ou non.
    int compteur = 2; //nb d'itération de l'algo des puissance avant convergence.


    //algo des puissance avec/sans la précision de Google, jusq'à atteindre epsilon (convergence).

    if (i == 0){printf("\n\n\n----------Calcul de convergence (PageRank) de la Matrice en cours----------\n\n\n");}
    else{printf("\n\n\n----------Calcul de convergence (Aitken) de la Matrice en cours----------\n\n\n");}

    printf("\nprécision Epsilon : %.2e", EPSILON);
    printf("\nvaleur d'alpha : %.2lf\n",alpha);
    
    int cptAitken = 0;
    while ( diffnorme > EPSILON  ){
      
      //diffnorme = 0.0;

      for (int i = 0; i < nbsom ; i++){

        x[i] = xk1[i];
        xk1[i] = xk2[i];

      }

      //produit_vecteur_matrice(x, Sommets, nbsom, nx); //calcul du produit sans la précision Google.

      //s = 0.0;
      //s = scalaire_s(nbsom, xk1, vecteurf); //scalaire s servant dans la précision Google.

      //calcul(alpha, nbsom, xk1, xk2, Sommets, vecteurf);   //calcul principale avec la précision Google.


      //calculAitken(alpha, nbsom, x, xk1, xk2, Sommets, compteur, vecteurf); //calcul de pageRank avec l'approximation de Aikten.

      calcul(alpha, nbsom, xk1, xk2, Sommets, vecteurf);

      if( (compteur%20) == 0 && compteur >19 && i == 1) {
        cptAitken++;
        Aitken(nbsom, x, xk1, xk2);
        //Aitken2(nbsom, x, xk1, xk2);
        //printf("\nFLAGFLAGFLAG\n");

      }

      diffnorme = diff_norme(nbsom, xk1, xk2); //calcul la norme de la différence en valeur absolu de nx - x

      //affiche_vecteur(nbsom, xk2); //affiche le vecteur résultat
      //testNorme(xk2,nbsom); //vérifie que la norme 1 du vecteur obtenu est bien égale à 1.
      
      if (i == 1){printf("\n\nvaleur norme : %.12lf nb tour : %d",diffnorme, compteur);}

      compteur++;
    }
    
    printf("\n\n\nCalcul de convergence de la Matrice terminé\n\n");

    printf("\nnombre de tour de boucle avant convergence : %d\n\n",compteur);
    printf("\nNombre d'appel à Aitken : %d\n\n",cptAitken);

    printf("durée : ");
    affiche_time(clock_calc);

    for(int j = 0; j<nbsom;j++){

      if(i == 0){resPageRank[j] = xk2[j];}
      else{resAitken[j] = xk2[j];}

    }

    free(x);
    free(xk1);
    free(xk2);
  }

  double NormeFinale = 0.0;
  NormeFinale = diff_norme(nbsom, resPageRank, resAitken);

  printf("\n\nvaleur de la norme des différences entre PageRank et Aitken après convergence : %.3e",NormeFinale);

  printf("\n\n\n----------Fin du Programme----------\n\n");

  printf("\ndurée totale du programme : ");
  affiche_time(clock_start);
  printf("\n");

  //affiche_vecteur(nbsom, xk2); //affiche le résultat après convergence 

  return 0;
}

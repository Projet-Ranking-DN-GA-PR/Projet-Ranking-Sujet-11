#include <stdio.h>
#include <time.h>

#include "calcul.h"

//#define EPSILON  0.00000001
//#define alpha 0.999

int main(int argc, char *argv[]) {


  /***************LECTURE DU FICHIER (MATRICE) ET STOCKAGE EN LISTE CHAINEE (COLONNE)**************************/

  clock_t clock_start = clock(); 

  char *nameFic = argv[1];
  printf("\n GRAPHE TRAITÉ PRÉSENTEMENT :\n%s\n",nameFic);

  FILE *f;
  f = fopen(argv[1], "r");

  int nbsom = 0;  //nombre de sommet
  int nbarc = 0;  //nombre d'arc

  nbsom = nb_sommet(argc, argv, f);
  nbarc = nb_arc(argc, argv, f);

  printf("nb sommet : %d nb arcs : %d\n", nbsom, nbarc);

  printf("----------Lecture et stockage de la Matrice en cours----------\n");

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

  printf("Lecture et stockage terminé\n");

  printf("durée : ");
  affiche_time(clock_start);  
  printf("\n");
  
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

  double ALPHATAB[6] = {0.5, 0.7, 0.85, 0.9, 0.99, 0.999}; //défini les différente valeurs d'alpha.

  double FREQTAB[6] = {5, 10, 20, 38, 450, 500}; //défini la fréquence d'appel à Aitken en fonction de la valeur d'alpha.

  for(int a = 0; a < 5; a++) { //boucle qui itère sur les valeurs d'alpha.

    double alpha = ALPHATAB[a];
    int freq = FREQTAB[a];

    double EPSILON = 0.01;

    for(int e = 0; e < 7; e++){ //boucle qui itère sur EPSILON de puissance de 10 en puissance de 10, de 10e-03 à 10e-09.

      EPSILON = EPSILON/10;

      /*
        La boucle for qui suit englobe le coeur du programme.

        Lorsque i = 0 => l'algo utilisé sera PageRank classique.
        lorsque i = 1 => l'algo utilisé sera PageRank avec l'approximation d'Aitken.
      */

        clock_t clock_calc = clock();

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

        
        int compteur = 2; //nb d'itération de l'algo des puissance avant convergence. Le conteur démarre à 2 du fait des initialisation de xk1 et xk2.


        //printf("\n\n\n----------Calcul de convergence (Aitken) de la Matrice en cours----------\n\n\n");


        printf("précision Epsilon : %.2e valeur d'alpha : %.3lf\n", EPSILON,alpha);
        printf("valeur de la fréquence d'appel à Aitken : %d\n",freq);
        
        int cptAitken = 0; //Nombre d'appel à l'approximation d'Aikten.

        double diffnorme = 1.0; // diff entre étape k et étape k+1, indique si on a converger ou non.

        while ( diffnorme > EPSILON  ) {
          
          for (int j = 0; j < nbsom ; j++){

            x[j] = xk1[j];
            xk1[j] = xk2[j];
            xk2[j] = 0.0;

          }

          
          calcul(alpha, nbsom, xk1, xk2, Sommets, vecteurf); //calcul la méthode des puissance classique de l'algo de PageRank.


          /*
            Cette boucle correspond à l'appel à l'approximation d'Aitken.
            Conditions :
              . i == 1 : cf commentaire ligne 93.
              . (compteur%freq) == 0 : correspond à la fréquence à laquelle on veut appelé la fonction Aitken. 
                Une fréquence basse sur certains paramètre peut amener à une divergence de l'algorithme. Le choix de la variable freq est donc important, bien qu'arbitraire.
              . compteur > 49 : définis une borne minimum avant l'appel d'Aitken, afin que l'algo est pu converger un petit peu, et que lambda2 soit devenu majoritaire.
              .diffnorme > EPSILON*1 : définis une borne max pour l'appel d'Aitken afin que le résultat final ne soit pas trop différent de celui de PageRank.
          */
          if( (compteur%freq) == 0 && compteur > 49 && diffnorme > EPSILON*1) {

            cptAitken++;
            Aitken(nbsom, x, xk1, xk2);

          }

          diffnorme = diff_norme(nbsom, xk1, xk2); //calcul la norme de la différence en valeur absolu de nx - x

          //affiche_vecteur(nbsom, xk2); //affiche le vecteur résultat

          compteur++;
        }

        printf("nombre de tour de boucle avant convergence : %d\n",compteur);
        printf("Nombre d'appel à Aitken : %d\n",cptAitken);

        printf("durée : ");
        affiche_time(clock_calc);
        printf("\n");

        for(int j = 0; j<nbsom;j++){

          
          resAitken[j] = xk2[j];

        }

        free(x);
        free(xk1);
        free(xk2);
      
    
      /*double NormeFinale = 0.0;
      NormeFinale = diff_norme(nbsom, resPageRank, resAitken);

      printf("\n\nvaleur de la norme des différences entre PageRank et Aitken après convergence : %.3e",NormeFinale);*/

      
      /*printf("durée totale du programme (depuis le tout début) : ");
      affiche_time(clock_start);
      printf("\n");*/

      //affiche_vecteur(nbsom, resPageRank); //affiche le résultat après convergence de PageRank classique.
      //affiche_vecteur(nbsom, resAitken); //affiche le résultat après convergence de PageRank avec l'approximation d'Aitken.
    }
    if(a != 6){printf("----------Changement de la valeur d'alpha----------\n");}
  }

  printf("----------Fin du Programme----------\n");
  return 0;
}
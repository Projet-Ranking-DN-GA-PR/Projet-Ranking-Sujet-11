#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calcul.h"

/*
fonction qui effectue le produit à gauche du vecteur ligne x par la matrice S
*/
void produit_vecteur_matrice(double x[], ARC *S[], int nbsom, double res[]) {

  for (int i = 0; i < nbsom; i++) {

    ARC *a;
    double som = 0;

    if(S[i] == NULL || S[i]->pere == 0){

      //printf("\n\nsommets %d n'a pas d'arcs entrant\n\n",i);
     
      
    }

    else{

      a = S[i];
      double prod = x[a->pere-1] * a->poid;
      som = som + prod;
      //printf("\n\n facteur x : %f poid : %f pere : %d fils : %d\n",x[a->pere-1], a->poid, a->pere, i);

      while(a->suivant != NULL){
      
      a=a->suivant;
      prod = x[a->pere-1] * a->poid;
      som = som + prod;

      }

    }

    res[i] = som;
    
  }
  
  
}

void affiche_vecteur(int taille_vec, double vec[]){

  printf("\n\n Resultat final\n\n");

  for (int i = 0; i < taille_vec; i++) {

    printf("valeur %d :     %lf;\n", i+1, vec[i]);
  }
  printf("\n\n");

}

/** 
fonction qui calcule le vecteur de différence de nx - x en valeur absolu
puis calcul la norme de ce vecteur, et remplace x par nx pour les itérations suivantes.
*/

double diff_norme(int taille_x, double x[], double nx[]){

  double res = 0.0;

  for(int i = 0; i<taille_x; i++){

    double diff = 0;
    diff = nx[i] - x[i];

    if( diff < 0){
      diff = -diff;
    }

    res = res + diff;
    x[i] = nx[i];

  }
  //printf("\n norme : %lf",res);
  return res;

}

/**
Fonction qui calcul le scalaire de x*f-transposé
*/
double scalaire_s(int taille_vec, double x[], double ftrans[]){

  double res = 0;

  for(int i = 0; i<taille_vec; i++){

    res = res + x[i] * ftrans[i];

  }

  return res;

}

/**
efectue le calcul suivant :
nx = alpha * x*P + alpha*s*s*e/N + (1-alpha)*e/N
*/
void calcul(double alpha, int N, double x[], double s, double nx[], ARC *S[]){


  //calcul s' tq s' = (s*alpha)/N
  // puis s' = s' + (1-alpha)/N
  double sprime = 0;

  sprime = (s*alpha)/N;
  sprime = sprime + (1-alpha)/N ;


  //produit = x*P
  double produit[N];

  produit_vecteur_matrice(x, S, N, produit);

  //calcul nx = alpha*x*P + sprime
  for (int i = 0; i<N; i++){

    nx[i] = alpha * produit[i] + sprime;

  }


}

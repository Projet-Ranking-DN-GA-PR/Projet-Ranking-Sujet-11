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
    a = S[i]; //récupére le 1er sommet de la liste chainée de la colonne i

    double som = 0.0;
      
    while(a != NULL){ //cette boucle calcul le produit du vecteur avec la colonne i de la matrice et l'écrit dans la colonne i du vecteur résultat
      
      som = som + (x[a->pere-1] * a->poid);
      a=a->suivant;

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

    double diff = 0.0;
    diff = nx[i] - x[i];

    if( diff < 0){
      diff = (-1) * diff;
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

  double res = 0.0;

  for(int i = 0; i<taille_vec; i++){

    if(ftrans[i] == 1){
      res = res + (x[i] * ftrans[i]);
    }

  }

  return res;

}

/**
efectue le calcul suivant :
nx = alpha * x*P + alpha*s*e/N + (1-alpha)*e/N avec x vecteur résultat à l'étape k et nx vecteur résultat à l'étape k+1
*/
void calcul(double alpha, int N, double x[], double s, double nx[], ARC *S[]){

  double sprime = 0.0;

  sprime = (s*alpha+(1-alpha))/N; //calcul s' à partir de s 

  double produit[N];  

  produit_vecteur_matrice(x, S, N, produit);  //produit = x*P (P est ici S : matrice d'adjacence du graphe).

  for (int i = 0; i < N; i++) {

    nx[i] = (alpha * produit[i]) + sprime; //fait la dernière étape du calcul avec la précision Google, i.e : ajout du surfer aléatoire (rend la matrice irréductible).

  }

}

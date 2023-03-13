#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calcul.h"

double previouslambda2 = 0.0;

/*
fonction qui effectue le produit à gauche du vecteur ligne x par la matrice S
*/
void produit_vecteur_matrice(double x[], ARC *S, int nbsom, double res[]) {

  for (int i = 0; i < nbsom; i++) {

    ARC *a;
    a = &S[i]; //récupére le 1er sommet de la liste chainée de la colonne i

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
    //x[i] = nx[i];

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
void calcul(double alpha, int N, double x[], double nx[], ARC *S, double f[]){


  double s = 0.0;
  s = scalaire_s(N, x, f);

  double sprime = 0.0;

  sprime = (s*alpha+(1-alpha))/N; //calcul s' à partir de s 

  double *produit;
  produit = malloc(N * sizeof(double));
    
  if (produit == NULL) {
    printf("\n\nPB malloc\n\n");
    exit(2);
  }   

  produit_vecteur_matrice(x, S, N, produit);  //produit = x*P (P est ici S : matrice d'adjacence du graphe).

  for (int i = 0; i < N; i++) {

    nx[i] = (alpha * produit[i]) + sprime; //fait la dernière étape du calcul avec la précision Google, i.e : ajout du surfer aléatoire (rend la matrice irréductible).

  }

  testNorme(nx,N);
  free(produit);

}

void Aitken( int N, double xk[], double xk1[], double xk2[]){


  
  

  double *a;
  a = malloc((N) * sizeof(double));
    
  if (a == NULL) {
    printf("\n\nPB malloc\n\n");
    exit(2);
  }

    
  for (int i = 0; i < N; i++){

    a[i] = 0.0;
    double b = 0.0;
    double lambda2 = 0.0;
    
    a[i] = xk[i] - xk1[i];
    b = xk1[i] - xk2[i];

    //if(a[i] == 0 || b == 0){lambda2 += previouslambda2/(i+1);}
    //else{lambda2 += b/a[i];}
    
    if(a[i] != 0){
      lambda2=b/a[i];
    }
    //lambda2=b/a[i];


    //previouslambda2 = lambda2;
    //printf("\nValeur de lambda2 trouvée : %.12lf\n",lambda2);
    if (lambda2 == 1) printf("FLAGGY FLAGGY FLAG FLAG");


    double u2lambda2k = 0.0;

    u2lambda2k = a[i]/(1 - lambda2);
    if (u2lambda2k < 0) u2lambda2k = 0;
    
    //printf("\t %.12lf",u2lambda2k);

    if(u2lambda2k < xk[i]){  
      //printf("FLAGGY FLAGGY FLAG FLAG");
      //printf("\t %.12lf",u2lambda2k);
      xk2[i] = xk[i] - u2lambda2k;
    }

    //xk2[i] = xk[i] - u2lambda2k;

    //xk2[i] = xk2[i] - xk2[i]*lambda2;

  }
  
  
  testNorme(xk2, N);
  free(a);

}

void Aitken2( int N, double xk[], double xk1[], double xk2[]) {

  for (int i = 0; i < N; i++){

    if (xk1[i] > xk[i]) {xk2[i] = xk2[i] - xk[i] + xk1[i];}

  }

  testNorme(xk2, N);


}

void testNorme(double x[], int N){

  double res = 0.0;

  for (int i = 0; i<N;i++){
    //if(x[i] < 0){x[i] = -x[i];}
    res+=x[i];
  }

  double ress = 0.0;
  for (int i = 0; i<N;i++){
    x[i]=x[i]/res;
    ress+=x[i];
  }

  //printf("\nNorme du vecteur xk : %.12lf          Seconde norme : %.12lf",res,ress);
}

void Aitken3( int N, double xk[], double xk1[], double xk2[], int k){


  
  

  double *a;
  a = malloc((N) * sizeof(double));
    
  if (a == NULL) {
    printf("\n\nPB malloc\n\n");
    exit(2);
  }

    double lambda2 = 0.0;
    
  for (int i = 0; i < N; i++) {

    double aprime = 0.0;
    double b = 0.0;
    
    aprime = xk[i] - xk1[i];
    b = xk1[i] - xk2[i];

    if(aprime == 0 || b == 0){lambda2 += previouslambda2;}
    else{lambda2 += b/aprime;}

  }

    lambda2 = lambda2 / N;
    previouslambda2 = lambda2;
    //printf("\nValeur de lambda2 trouvée : %.12lf\n",lambda2);
    //if (lambda2 < 0){lambda2 = -lambda2;}
    //if (lambda2 >= 1) lambda2 = 0.999999999;

    printf("\nValeur de lambda2 trouvée : %.12lf\n",lambda2);
    if (lambda2 < 0){lambda2 = 0;}

    double lambda2k = lambda2;
    
  for (int j = 1; j < k+2; j++) {

    lambda2k = lambda2k*lambda2;
  
  }

  //printf("\ndiff bt lambda2 et lambda2k : %3e %3e",lambda2, lambda2k);

  double norme = 0.0;
  norme = diff_norme(N, xk1, xk2);
 // printf("\n valeur norme : %.12lf", norme);

  for (int i = 0; i < N; i++) {

    double tmp = 0.0;
    tmp = xk2[i] - xk2[i]*lambda2k;
    //printf("\ndiff bt lambda2 et lambda2k : %3e %3e %3e",xk2[i], xk2[i]*lambda2, tmp);
    xk2[i] = tmp;
    //xk2[i] = a[i];
    //norme += xk2[i] - xk1[i];
    printf("\n valeur xk[i] : %3e",xk2[i]);
  
  }
  //printf("\n valeur norme : %.12lf", norme/N);
  //testNorme(xk2, N);
  //norme = diff_norme(N, a, xk2);
  //printf("\n valeur norme : %.12lf", norme);
  free(a);

}

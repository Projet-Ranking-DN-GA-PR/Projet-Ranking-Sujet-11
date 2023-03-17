#include "lecture.h"

void produit_vecteur_matrice(double x[], ARC *S, int nbsom, double *res);

void affiche_vecteur(int taille_vec, double *vec);

double diff_norme(int taille_x, double x[], double nx[]);

double scalaire_s(int taille_vec, double x[], double ftrans[]);

void calcul(double alpha, int N, double x[], double nx[], ARC *S, double f[]);

void Aitken( int N, double xk[], double xk1[], double xk2[]);

void Renormalisation(double x[], int N);
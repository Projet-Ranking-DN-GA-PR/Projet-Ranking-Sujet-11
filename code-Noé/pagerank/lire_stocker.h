#ifndef _LIRE_STOCKER_H
#define _LIRE_STOCKER_H

struct Arc{
    int pred;
    float weight;
    struct Arc *suiv;
};

typedef struct Arc ARC;

void stocker(FILE *F, int nb_sommets, int nb_arcs, ARC *Tsommets, double *f);
void remplir(ARC *Tsommets, int som_pred, int som_suc, double weight);
void aff_ARC(ARC *A);
void aff_Tab_ARC(ARC* Tsommets, int nb_sommets);
/*
struct Tableau{
  int taille; //taille du tableau (nombre de mots)
  char *tab; //tableau de char de dimension n*taille
};

typedef struct Tableau TABLEAU;

int taille(char *fichier, int *nb_ligne);
TABLEAU creer_tab(TABLEAU T);
TABLEAU remplir_tab(TABLEAU T, int *L, char *fichier);
void affiche_T(TABLEAU T);
void affiche_L(TABLEAU T, int *L, int nb_ligne);
*/
#endif

#include <stdio.h>
#include <stdlib.h>
#include "lire_stocker.h"

void remplir(ARC *Tsommets, int som_pred, int som_suc, double weight){
    ARC *A;
    A = (ARC*)malloc(sizeof(ARC));
    A->pred = som_pred;
    A->weight = weight;
    A->suiv = NULL;
    if(Tsommets[som_suc-1].pred == -1){
        Tsommets[som_suc-1] = *A;
    }else{
        if(Tsommets[som_suc-1].suiv == NULL){
            Tsommets[som_suc-1].suiv = A;
        }else{
            A->suiv = Tsommets[som_suc-1].suiv;
            Tsommets[som_suc-1].suiv = A;
        }
    }
}

void stocker(FILE *F, int nb_sommets, int nb_arcs, ARC *Tsommets, double* f){
    for(int i =0; i<nb_sommets;i++){
        ARC init = {-1,0,NULL};
        Tsommets[i]=init;
    }
    
    int som_pred;
    int som_suc;
    int suc=0;
    double weight;
    
    for(int i = 0; i<nb_sommets; i++){
        if(fscanf(F,"%d %d",&som_pred,&suc)==EOF){
            printf("Erreur scan\n");
            exit(4);
        }
        if(suc == 0){f[i]=1;}
        else{f[i]=0;}
        for(int j = 0; j<suc; j++){
            if(fscanf(F,"%d %lf",&som_suc,&weight)==EOF){
                printf("Erreur scan\n");
                exit(4);
            }
            remplir(Tsommets, som_pred, som_suc, weight);
        }
    }
}

void aff_ARC(ARC *A){
    if(A == NULL) return;
    printf("    Pred : %d, Poids : %lf\n",A->pred,A->weight);
    aff_ARC(A->suiv);
}

void aff_Tab_ARC(ARC* Tsommets, int nb_sommets){
    for(int i = 0; i< nb_sommets; i++){
        printf("Sommet : %d\n",i+1);
        aff_ARC(&Tsommets[i]);
    }
}


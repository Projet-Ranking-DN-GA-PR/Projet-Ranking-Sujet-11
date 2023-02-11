#include <stdio.h>
#include <stdlib.h>
#include "lire_stocker.h"

double EPSILON = 0.00000001;
double alpha = 0.85;

//Affichage
void aff_vec(int nb_sommets, double newX[]){
    printf("Resultat\n");
    for(int i=0;i<nb_sommets;i++){
        printf("%f ",newX[i]);
    }
    printf("\n");
}


//Main
int main(int argc, char *argv[]){

    int nb_sommets;
    int nb_arcs;

    //Lecture matrice et stockage
    FILE *F;
	F = fopen(argv[1],"r");
	if(F == NULL){
		fprintf(stderr, "Erreur ouverture fichier %s\n", argv[1]);
		exit(3);
	}
    
    if(fscanf(F,"%d\n%d",&nb_sommets,&nb_arcs)==EOF){
        printf("Erreur scan\n");
        exit(4);
    }
    ARC *Tsommets;
    Tsommets = (ARC*)malloc(nb_sommets * sizeof(ARC));
    double *f;
    f = (double*)malloc(nb_sommets * sizeof(double));
    stocker(F,nb_sommets,nb_arcs, Tsommets, f);
    fclose(F);
    printf("nb_sommets: %d\n",nb_sommets);
    printf("nb_arcs: %d\n",nb_arcs);
    //aff_Tab_ARC(Tsommets,nb_sommets);
    
    
    //méthode puissance

    //double x[] = {0.1,0.1,0.2,0,0.1,0.15,0.15,0.2};
    //double newX[] = {0.1,0.1,0.2,0,0.1,0.15,0.15,0.2};
    double x[nb_sommets];
    double newX[nb_sommets];

    for(int j=0;j<nb_sommets;j++){
        x[j] = 1.0/nb_sommets;
        newX[j] = x[j];
    }


    double norme;
    double c = 0.0;
    int cpt = 0;
    do{
        norme = 0.0;
        //p = multi_VecMat(Tsommets,nb_sommets,f);
        double inter;
        ARC *A;
        double s=0;
        double s1=0;
        for(int i=0;i<nb_sommets;i++){
            if(f[i]==1){
                s+=x[i]*f[i];
            }
        }
        s1=(s*alpha+(1-alpha))/nb_sommets;
        for(int i=0;i<nb_sommets;i++){
            A = &Tsommets[i];
            inter = 0;
            while(A!=NULL){
                inter += A->weight*x[A->pred-1];
                A = A->suiv;
            }
            newX[i] = alpha*inter+s1;
        }
        //aff_vec(nb_sommets);
        for(int i=0;i<nb_sommets;i++){
            if((newX[i]-x[i])>0){
                c = newX[i]-x[i];}
            else {c = x[i]-newX[i];}
        norme+=c;
        x[i] = newX[i];
        }
        //printf("%lf\n",norme);
        cpt++;
    }while(norme>EPSILON);
    printf("Nn itération : %d\n",cpt);
    //aff_vec(nb_sommets, newX);
    exit(0);
}

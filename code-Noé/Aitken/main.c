#include <stdio.h>
#include <stdlib.h>
#include "lire_stocker.h"

double EPSILON = 0.000000001;
double alpha = 0.9;

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

    //variable
    double *x;
    x = (double*)malloc(nb_sommets*sizeof(double));
    double *newX;
    newX = (double*)malloc(nb_sommets*sizeof(double));
    double *x1;
    x1 = (double*)malloc(nb_sommets*sizeof(double));
    double *x2;
    x2 = (double*)malloc(nb_sommets*sizeof(double));
   // double g[nb_sommets];
   // double h[nb_sommets]; 
    double inter = 0;
    ARC *A;
    double s=0;
    double s1=0;

    //Initialisation de x
    for(int j=0;j<nb_sommets;j++){
        x[j] = 1.0/nb_sommets;
        x1[j] = 0.0;
        x2[j] = 0.0;
        newX[j] = 0.0;
       // g[j] = 0.0;
       // h[j] = 0.0;
    }

    double norme=1.0;
    double c = 0.0;
    int cpt = 0;
    do{
        //p = multi_VecMat(Tsommets,nb_sommets,f);
        s=0;
        s1=0;
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

        //Aitken
        if(((cpt+1)%60==0)&&(norme>EPSILON*100)){
            printf("Aitken\n");
            //calcul de x1
            s=0;
            s1=0;
            for(int i=0;i<nb_sommets;i++){
                if(f[i]==1){
                    s+=newX[i]*f[i];
                }
            }
            s1=(s*alpha+(1-alpha))/nb_sommets;
            for(int i=0;i<nb_sommets;i++){
                A = &Tsommets[i];
                inter = 0;
                while(A!=NULL){
                    inter += A->weight*newX[A->pred-1];
                    A = A->suiv;
                }
                x1[i] = alpha*inter+s1;
            }

            //calcul du nouveau x1
            for(int i=0;i<nb_sommets;i++){
                x1[i]=x1[i]-(newX[i]-x1[i]); 
            }

            //calcul de x2
            s=0;
            s1=0;
            for(int i=0;i<nb_sommets;i++){
                if(f[i]==1){
                    s+=x1[i]*f[i];
                }
            }
            s1=(s*alpha+(1-alpha))/nb_sommets;
            for(int i=0;i<nb_sommets;i++){
                A = &Tsommets[i];
                inter = 0;
                while(A!=NULL){
                    inter += A->weight*x1[A->pred-1];
                    A = A->suiv;
                }
                x2[i] = alpha*inter+s1;
            }
            
            /*for(int i=0;i<nb_sommets;i++){
                g[i]= (x1[i]-x[i])*(x1[i]-x[i]);
                h[i]= x2[i]-(2*x1[i])+x[i];
                newX[i]= x[i]-(g[i]/h[i]);
            }*/
            for(int i=0;i<nb_sommets;i++){
                x[i]=x1[i];
                newX[i]=x2[i];
            }
        }

        //calcul de la norme
        norme = 0.0;
        for(int i=0;i<nb_sommets;i++){
            if((newX[i]-x[i])>0){
                c = newX[i]-x[i];}
            else {c = x[i]-newX[i];}
        norme+=c;
        x[i] = newX[i];
        }
        //printf("norme : %lf\n",norme);
        cpt++;//indentation 
    }while(norme>EPSILON);
    printf("Nb itération : %d\n",cpt);
    //aff_vec(nb_sommets, x);
    free(x); free(newX); free(x1); free(x2);
    exit(0);
}

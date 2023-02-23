#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lire_stocker.h"

//double EPSILON = 0.00000001;
//double alpha = 0.85;

//Affichage
void aff_vec(int nb_sommets, double newX[]){
    printf("Resultat\n");
    for(int i=0;i<nb_sommets;i++){
        printf("%f ",newX[i]);
    }
    printf("\n");
}

void affiche_time(clock_t current_time) {

  clock_t test = clock();
  test = test - current_time;
  printf("%ld min %ld sec %ld ms %ld µs\n",test/(CLOCKS_PER_SEC*60), (test/CLOCKS_PER_SEC)%60, (test*1000/CLOCKS_PER_SEC)%1000, (test*1000000/CLOCKS_PER_SEC)%1000 );
  printf("Finished in %ld µs\n\n",(test*1000000/CLOCKS_PER_SEC) );
}


//Main
int main(int argc, char *argv[]){

    float EPSILON; //= atof(argv[3]);
    float alpha; //= atof(argv[2]);
    float tab_alp[] = {0.5 , 0.7, 0.85, 0.9, 0.99};
    int nb_sommets;
    int nb_arcs;
    clock_t clock_start = clock(); 
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

    printf("\n\n\nLecture et stockage terminé\n");

    printf("durée : ");
    affiche_time(clock_start); 
    //printf("nb_sommets: %d\n",nb_sommets);
    //printf("nb_arcs: %d\n",nb_arcs);
    //aff_Tab_ARC(Tsommets,nb_sommets);
    
    
    //méthode puissance

    //double x[] = {0.1,0.1,0.2,0,0.1,0.15,0.15,0.2};
    //double newX[] = {0.1,0.1,0.2,0,0.1,0.15,0.15,0.2};

    for(int p = 0; p<5; p++){
    EPSILON = 0.01;
    for(int m = 0; m<7 ; m++){
        EPSILON = EPSILON/10;
        alpha = tab_alp[p];
        clock_t clock_calc = clock();
        double *x;
        x = (double*)malloc(nb_sommets*sizeof(double));
        double *newX;
        newX = (double*)malloc(nb_sommets*sizeof(double));

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
            //if(cpt <= 1){printf("\n scalaire s : %.15lf\n",s);}
            s1=(s*alpha+(1-alpha))/nb_sommets;
            for(int i=0;i<nb_sommets;i++){
                A = &Tsommets[i];
                inter = 0;
                while(A!=NULL){
                    inter += A->weight*x[A->pred-1];
                    //printf("  poid : %lf  ;",A->weight);
                    A = A->suiv;
                }
                newX[i] = alpha*inter+s1;
            }
            
            for(int i=0;i<nb_sommets;i++){
                if((newX[i]-x[i])>0){
                    c = newX[i]-x[i];}
                else {c = x[i]-newX[i];}
            norme+=c;
            x[i] = newX[i];
            }
            //aff_vec(nb_sommets, newX);
            double sumvec = 0.0;
            for (int i = 0 ; i < nb_sommets ; i++){
                sumvec+=x[i];

            }
            //printf("somme vec x : %lf\n",sumvec);
            //printf("%lf\n",norme);
            cpt++;
        }while(norme>EPSILON);
        printf("Nb itération : %d, alpha : %.4f, epsilon : %.2e\n",cpt,alpha,EPSILON);
        //aff_vec(nb_sommets, newX);
        printf("Calcul de convergence de la Matrice terminé\n");

        printf("durée : ");
        affiche_time(clock_calc);

        free(x);
        free(newX);
        }
    }
    exit(0);
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

int main(int argc,char* argv[]){

    FILE* fichier = NULL;
    int GrandNombre =1000000000;
    double alpha = atof(argv[2]);
    fichier = fopen(argv[1], "r");
    char* LectureFichier=malloc(GrandNombre*sizeof(char));

    fgets(LectureFichier, GrandNombre, fichier);
    int nbSommet = strtol(LectureFichier,NULL,10);
    fgets(LectureFichier, GrandNombre, fichier);
    int nbArc = strtol(LectureFichier,NULL,10);

    int* degréEntrant = malloc(nbSommet*sizeof(int));
    int sommet = 0;

    while(fgets(LectureFichier, GrandNombre, fichier)!= NULL){ // degré Entrant      
        char* strToken= strtok(LectureFichier," ,;");
        sommet = strtol(strToken,NULL,10);
        strToken= strtok(NULL," ,;");
        int nbArca = strtol(strToken,NULL,10);    
        int i=0;
        while(i<nbArca){
            strToken= strtok(NULL," ,;");
            degréEntrant[strtol(strToken,NULL,10)-1]+=1;
            strToken= strtok(NULL," ,;");
            i++;
        }
        
    }
    fclose(fichier);

    int* debut = malloc(nbSommet*sizeof(int));
    int* fin = malloc(nbSommet*sizeof(int));
    int posT=0;

    for(int i = 0 ; i< nbSommet ; i++){  // Debut Fin
        debut[i] = posT;
        posT = posT + degréEntrant[i];
        fin[i] = posT;

    }
    free(degréEntrant);
    /*
    for(int i = 0 ; i < nbSommet;i++){
        printf("Sommet %d : ",i+1);
        printf("%d -> ",debut[i]);
        printf("%d\n",fin[i]);
    }
    printf("\n");
    */

    fichier = fopen(argv[1], "r");

    fgets(LectureFichier, GrandNombre, fichier);
    fgets(LectureFichier, GrandNombre, fichier);

    int* tSommetEntrant = malloc(nbArc*sizeof(int));
    float* tPonderation = malloc(nbArc*sizeof(float));
    
    int* f = malloc(nbSommet*sizeof(int));

    while(fgets(LectureFichier, GrandNombre, fichier)!= NULL){ // Tableau T 
        char* strToken= strtok(LectureFichier," ,;");
        sommet = strtol(strToken,NULL,10);
        strToken= strtok(NULL," ,;");
        int nbArca = strtol(strToken,NULL,10); 
        f[sommet-1]=1; 
        if(nbArca>0){
			f[sommet-1]=0;
		}  
        int i=0;
        while(i<nbArca){
            strToken= strtok(NULL," ,;");
            int sommetTraité = strtol(strToken,NULL,10)-1;
            tSommetEntrant[debut[sommetTraité]] = sommet;
            strToken= strtok(NULL," ,;");
            tPonderation[debut[sommetTraité]] = strtof(strToken,NULL);
            debut[sommetTraité]+=1;
            i++;
        }
        
    }
    free(debut);
    free(LectureFichier);
    /*int j = 0;
    for(int i = 0 ; i < nbArc;i++){ // print des differents arcs
        int sommetretrouve=0;
        while(sommetretrouve==0){
            if(i<fin[j]){
                printf("Sommet %d : ",j+1);
                sommetretrouve=1;
            }
            else{
                j=j+1;
            }
        }
        printf("%d ",tSommetEntrant[i]);
        printf(" | %.2f\n",tPonderation[i]);
    }
    */
    fclose(fichier);
    
    double* x0 = malloc(nbSommet*sizeof(double));
    double s=0;
    //double x[8] = { 0.1 ,0.1, 0.2, 0, 0.1, 0.15, 0.15, 0.2};
    for(int i=0;i<nbSommet;i++){
		x0[i]=1.0/nbSommet;
		s = s + x0[i] * f[i];
	}
	free(f);
    double s2 = (s*alpha)/nbSommet;
    double s3 = (s2 + (1.0-alpha)/nbSommet);
	double* x1 = malloc(nbSommet*sizeof(double));
	for(int i=0;i<nbSommet;i++){
		x1[i]=1.0/nbSommet;
	}
	double* result = malloc(nbSommet*sizeof(double));
    double norme=1;
    int nbIte = 0;
	posT=0;
	norme = 0;
	for(int i=0;i<nbSommet;i++){ // Calcul x*M
		result[i]=0;
		while(posT<fin[i]){
			result[i]=result[i]+x0[tSommetEntrant[posT]-1]*tPonderation[posT];
			posT=posT+1;
		}
		result[i]=(alpha*result[i])+s3;
		norme = norme + fabs(result[i]-x0[i]);
	}
	for(int i=0;i<nbSommet;i++){
		x1[i]=result[i];
	}
	double* x2 = malloc(nbSommet*sizeof(double));
	for(int i=0;i<nbSommet;i++){
		x2[i]=1.0/nbSommet;
	}
	posT=0;
	norme = 0;
	for(int i=0;i<nbSommet;i++){ // Calcul x*M
		result[i]=0;
		while(posT<fin[i]){
			result[i]=result[i]+x1[tSommetEntrant[posT]-1]*tPonderation[posT];
			posT=posT+1;
		}
		result[i]=(alpha*result[i])+s3;
		norme = norme + fabs(result[i]-x1[i]);
	}
	for(int i=0;i<nbSommet;i++){
		x2[i]=result[i];
	}
    nbIte=1;
    while(norme>atof(argv[3])){ // Attente de la convergence de x
		for(int i=0;i<nbSommet;i++){
			x0[i]=x1[i];
			x1[i]=x2[i];
		}
		posT=0;
		norme = 0;
		for(int i=0;i<nbSommet;i++){ // Calcul x*M
			result[i]=0;
			while(posT<fin[i]){
				result[i]=result[i]+x1[tSommetEntrant[posT]-1]*tPonderation[posT];
				posT=posT+1;
			}
			result[i]=(alpha*result[i])+s3;
			norme = norme + fabs(result[i]-x1[i]);
		}
		for(int i=0;i<nbSommet;i++){
			x2[i]=result[i];
			if(nbIte==30){
				double g=(x1[i]-x0[i])*(x1[i]-x0[i]);
				double h=x2[i]-2.0*x1[i]+x0[i];
				if(x2[i] > g/h ) x2[i] =x2[i]-g/h;
			}
		}
		//printf("\n  La norme est de %f \n",norme);
		nbIte++;
	}
	printf("Le nb itération est : %d \n",nbIte);

    free(result);
    free(tPonderation);
    free(tSommetEntrant);
    free(fin);
    return 0;
    
}

<<<<<<< HEAD
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
    double* tPonderation = malloc(nbArc*sizeof(double));
    
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
    
    double* x = malloc(nbSommet*sizeof(double));
    double s=0;
    //double x[8] = { 0.1 ,0.1, 0.2, 0, 0.1, 0.15, 0.15, 0.2};
    for(int i=0;i<nbSommet;i++){
		x[i]=1.0/nbSommet;
		s = s + x[i] * f[i];
	}
	free(f);
    double s2 = (s*alpha)/nbSommet;
    double s3 = (s2 + (1.0-alpha)/nbSommet);
    
    double* result = malloc(nbSommet*sizeof(double));
    double norme=1;
    int nbIte = 0;
    while(norme>atof(argv[3])){ // Attente de la convergence de x
		posT=0;
		norme = 0;
		for(int i=0;i<nbSommet;i++){ // Calcul x*M
			result[i]=0;
			while(posT<fin[i]){
				result[i]=result[i]+x[tSommetEntrant[posT]-1]*tPonderation[posT];
				posT=posT+1;
			}
			result[i]=(alpha*result[i])+s3;
			norme = norme + fabs(result[i]-x[i]);
		}
		for(int i=0;i<nbSommet;i++){
			x[i]=result[i];
			//printf("%f ",x[i]);
		}
		//printf("\n");
		//printf("\n  La norme est de %f \n",norme);
		nbIte++;
	}
	printf("Le nb itération est : %d \n",nbIte);

    free(result);
    free(tPonderation);
    free(tSommetEntrant);
    free(fin);
    free(x);
    return 0;
    
}
=======
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
    double* tPonderation = malloc(nbArc*sizeof(double));
    
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
    
    double* x = malloc(nbSommet*sizeof(double));
    double s=0;
    //double x[8] = { 0.1 ,0.1, 0.2, 0, 0.1, 0.15, 0.15, 0.2};
    for(int i=0;i<nbSommet;i++){
		x[i]=1.0/nbSommet;
		s = s + x[i] * f[i];
	}
	free(f);
    double s2 = (s*alpha)/nbSommet;
    double s3 = (s2 + (1.0-alpha)/nbSommet);
    
    double* result = malloc(nbSommet*sizeof(double));
    double norme=1;
    int nbIte = 0;
    while(norme>atof(argv[3])){ // Attente de la convergence de x
		posT=0;
		norme = 0;
		for(int i=0;i<nbSommet;i++){ // Calcul x*M
			result[i]=0;
			while(posT<fin[i]){
				result[i]=result[i]+x[tSommetEntrant[posT]-1]*tPonderation[posT];
				posT=posT+1;
			}
			result[i]=(alpha*result[i])+s3;
			norme = norme + fabs(result[i]-x[i]);
		}
		for(int i=0;i<nbSommet;i++){
			x[i]=result[i];
			//printf("%f ",x[i]);
		}
		//printf("\n");
		//printf("\n  La norme est de %f \n",norme);
		nbIte++;
	}
	printf("Le nb itération est : %d \n",nbIte);

    free(result);
    free(tPonderation);
    free(tSommetEntrant);
    free(fin);
    free(x);
    return 0;
    
}
>>>>>>> d6a04c629a0ad3073d3778a5f9172ad97e6aa8a0

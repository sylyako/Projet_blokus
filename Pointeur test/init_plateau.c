/* Initialise le plateau de jeux */
#include "init_plateau.h"

void init_plateau(t_plateau* plateau, int nbj_max){
    int i,j;

    plateau->plateau = malloc(plateau->taille_plateau * sizeof(t_case));

    for(i = 0 ; i < plateau->taille_plateau ; i++){
        plateau->plateau[i] = malloc(plateau->taille_plateau * sizeof(t_case));
    }

    for(i = 0 ; i < plateau->taille_plateau ; i++){
        for(j = 0 ; j < plateau->taille_plateau ; j++){
            plateau->plateau[i][j].couleur = libre;
        }
    }

}

/* Return 1 si la coordonner fournie est hors plateau, 0 sinon */
int coordonner_invalide(int x, int y, int taille_plateau){
    if (x < 0 || y < 0){
        return (1);
    }
    if(taille_plateau == 20){   // plateau a 4
        if(x > 19 || y > 19){
            return(1);
        }else{
            return(0);
        }
    }else{                      // plateau a 2
        if(x > 13 || y > 13){
            return(1);
        }else{
            return(0);
        }
    }
}

void libere_plateau(t_plateau* plateau){
	int i;
	
	for(i = 0 ; i < plateau->taille_plateau ; i++){
        free(plateau->plateau[i]);
    }
	free(plateau->plateau);
}


#include "init_plateau.h"

void init_plateau(int taille_plateau, t_case_m (*plateau)[taille_plateau], int nbj_max, t_liste* liste_piece, int* joueur_en_jeux, int* score){
    int i,j;
    
    for(i = 0; i < taille_plateau; i++){
        for(j = 0; j < taille_plateau; j++){
            plateau[i][j].couleur = libre;
            plateau[i][j].possible_r = 0;
            plateau[i][j].possible_b = 0;
            plateau[i][j].possible_v = 0;
            plateau[i][j].possible_j = 0;
        }
    }
    /* On definie les emplacements possible des premieres pieces */
    if (taille_plateau == 20){      // plateau a 4
        plateau[0][0].possible_r = 1;
        plateau[0][taille_plateau-1].possible_b = 1;
        plateau[taille_plateau-1][taille_plateau-1].possible_v = 1;
        plateau[taille_plateau-1][0].possible_j = 1;
    }else{                          // plateau a 2
        plateau[4][4].possible_r = 1;
        plateau[9][9].possible_b = 1;
    }
    
    /* Cree les listes et la disponibiliter des joueur*/
    for(i = 0; i < nbj_max; i++ ){
        init_liste(&liste_piece[i]);      //On initialise les liste de pieces de tout les joueur
        remplir_listes(&liste_piece[i]);  //On remplit les listes de tout les joueurs
        joueur_en_jeux[i] = 1;              //Met dispo tout les joueurs
        score[i] = 89;              //On initialise les score a 89
        
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

/* Creer un second plateau en fonction du premier, avec pour seul coordonner possible celle entrer en parameter */
void init_plateau_fictif(int taille_plateau, t_case_m (*plateau_original)[taille_plateau], t_case_m (*plateau_copie)[taille_plateau],int joueur, t_coordonnee* coord){
    int i,j;
    
    for(i = 0; i < taille_plateau; i++){ // Creer le plateau_copie avec juste les case de couleur de plateau_original
        for(j = 0; j < taille_plateau; j++){
            plateau_copie[i][j].possible_r = 0;
            plateau_copie[i][j].possible_b = 0;
            plateau_copie[i][j].possible_v = 0;
            plateau_copie[i][j].possible_j = 0;
            plateau_copie[i][j].couleur = plateau_original[i][j].couleur;
        }
    }
    
    if(joueur == rouge){ // Ajoute l'unique coordonner possible
        plateau_copie[coord->y][coord->x].possible_r = 1;
    }else if(joueur == bleu){
        plateau_copie[coord->y][coord->x].possible_b = 1;
    }else if(joueur == vert){
        plateau_copie[coord->y][coord->x].possible_v = 1;
    }else{
        plateau_copie[coord->y][coord->x].possible_j = 1;
    }
}

/* Copie le plateau_original dans le plateau_copie  */
void copie_plateau(int taille_plateau, t_case_m (*plateau_original)[taille_plateau] , t_case_m (*plateau_copie)[taille_plateau]){
    int i,j;
    
    for(i = 0; i < taille_plateau; i++){ // Creer le plateau_copie
        for(j = 0; j < taille_plateau; j++){
            plateau_copie[i][j].possible_r = plateau_original[i][j].possible_r;
            plateau_copie[i][j].possible_b = plateau_original[i][j].possible_b;
            plateau_copie[i][j].possible_v = plateau_original[i][j].possible_v;
            plateau_copie[i][j].possible_j = plateau_original[i][j].possible_j;
            plateau_copie[i][j].couleur = plateau_original[i][j].couleur;
        }
    }
}

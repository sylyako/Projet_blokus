/* Initialise le plateau de jeux */
#include "init_plateau.h"


/**
 * \file init_plateau.c
 * \brief Module de fonctions pour le plateau
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void init_plateau(int taille_plateau, t_case (*plateau)[taille_plateau], int nbj_max, t_liste* liste_piece, int* joueur_en_jeux, int* score)
 * \brief Initialise le plateau selon les règles du Blokus
 * \param taille_plateau la taille du plateau
 * \param (*plateau)[taille_plateau] Le plateau 
 * \param nbj_max Le nombre de joueurs
 * \param *liste Pointeur sur une liste de pièces
 * \param *joueurs_en_jeux Le nombre de joueurs encore en jeu
 * \param *score Le score de chaque joueur
 *
 * \fn int piece_dispo(int piece, int* nb_piece, int tab_piece[], t_liste* liste, t_matrice* copie)
 * \brief Verifie si la piece choisie (int piece) est bien une piece disponible. Si c'est le cas on copie tout les information de la piece dans copie.
 * \param piece Numero de la piece concernée
 * \param tabpiece Tableau contenant les numeros des pieces disponibles
 * \param liste Pointeur de type t_liste contenant toutes les pieces d'un joueur
 * \param copie Pointeur de type t_matrice recevant la piece disponible
 *
 * \fn int coordonner_invalide(int x, int y, int taille_plateau)
 * \brief Vérifie si les coordonnées sont dans le plateau
 * \param x La colonne du plateau
 * \param y La ligne du plateau
 * \param taille_plateau la aille du plateau
 * 
 *
 * \fn void init_plateau_fictif(int taille_plateau, t_case (*plateau_original)[taille_plateau], t_case (*plateau_copie)[taille_plateau],int joueur, t_coordonnee* coord)
 * \brief Créé un plateau avec une seule possibilité de placement
 * \param taille_plateau la taille du plateau
 * \param (*plateau)[taille_plateau] Le plateau 
 * \param nbj_max Le nombre de joueurs
 * \param *liste Pointeur sur une liste de pièces
 * \param *joueurs_en_jeux Le nombre de joueurs encore en jeu
 * \param *score Le score de chaque joueur 
 *
 * \fn void copie_plateau(int taille_plateau, t_case (*plateau_original)[taille_plateau] , t_case (*plateau_copie)[taille_plateau])
 * \brief Copie le tableau dans un autrre
 * \param taille_plateau La taille du plateau
 * \param (*plateau_original)[taille_plateau] Le plateau original
 * \param (*plateau_copie)[taille_plateau] Le plateau copié
 */


void init_plateau(int taille_plateau, t_case (*plateau)[taille_plateau], int nbj_max, t_liste* liste_piece, int* joueur_en_jeux, int* score){
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
void init_plateau_fictif(int taille_plateau, t_case (*plateau_original)[taille_plateau], t_case (*plateau_copie)[taille_plateau],int joueur, t_coordonnee* coord){
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
void copie_plateau(int taille_plateau, t_case (*plateau_original)[taille_plateau] , t_case (*plateau_copie)[taille_plateau]){
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

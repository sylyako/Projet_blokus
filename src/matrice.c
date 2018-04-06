#include "matrice.h"
#include "structures.h"

/**
 * \file matrice.c
 * \brief Module de fonctions pour la gestion de matrices.
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void init_matrice (t_matrice* piece)
 * \brief Initialise une matrice à 0
 * \param *piece Structure contenant les informations sur la matrice
 *
 * \fnvoid afficher_matrice (t_matrice piece)
 * \brief Affiche la piece 
 * \param piece La piece et ses informations
 *
 *
 * \fn void copie_matrice(t_matrice* source, t_matrice* copie)
 * \brief Copie une matrice dans une autre
 * \param *source La source
 * \param *copie La copie
 *
 * \fn void insertion_matrice_piece(t_matrice* piece, t_coordonnee coord)
 * \brief Insère dans la matrice un morceau d'une pièce de jeu
 * \param *piece La matrice
 * \param coord Les coordonnées du bout de pièce
 *
 *
 * \fn void insertion_num_piece(t_matrice* piece, int numero)
 * \brief Insère dans la matrice le numéro de la pièce de jeu
 * \param *piece La pièce de jeu
 * \param numero Le numéro de la pièce
 *
 * \fn void insertion_taille_piece(t_matrice* piece, int taille_piece)
 * \brief Fonction qui insère la taille de la pièce dans la structure
 * \param *piece La pièce de jeu
 * \param taille_piece La taille de la pièce
 *
 * \fn void miroir_horizontal (int (*piece)[TAILLE_MATRICE_PIECE])
 * \brief Fait le miroir horizontal de la pièce
 * \param *piece La pièce
 *
 *
 * \fn void miroir_vertical (int (*piece)[TAILLE_MATRICE_PIECE])
 * \brief Fait le miroir vertical de la pièce
 * \param *piece La pièce
 *
 *
 * \fn void tourner_piece (int (*piece)[TAILLE_MATRICE_PIECE])
 * \brief Fait une rotation de la pièce à 90°
 * \param *piece La pièce
 *
 *
 * \fn void rotation (int (*piece)[TAILLE_MATRICE_PIECE], int sens)
 * \brief Fait une rotation de la pièce selon un sens passé en paramètre
 * \param *piece La pièce
 * \param sens Le sens de la pièce
 */


void init_matrice (t_matrice* piece) { 
	int i, j;

	piece->taille = 0;
	piece->num = 0;
	for (i = 0; i < TAILLE_MATRICE_PIECE; i++) {
		for (j = 0; j < TAILLE_MATRICE_PIECE; j++)
			piece->mat[i][j] = 0;
	}
}
/* Affiche tous les elements de la liste, utile au debug et pour afficher la piece selectionner*/
void afficher_matrice (t_matrice piece) { 
	int i, j;

	for (i = 0; i < TAILLE_MATRICE_PIECE; i++) {
		for ( j = 0; j < TAILLE_MATRICE_PIECE; j++){
            if(piece.mat[i][j] == 0){
                printf("|   ");
            }else{
                printf("| X ");
            }
		}
		printf("|");
		printf("\n");
	}
	printf("num = %i\n", piece.num+1); 
    printf("taille = %i\n", piece.taille);
    printf("\n");
}

/* copie le contenue d'une type matrice dans une autre */
void copie_matrice(t_matrice* source, t_matrice* copie){
    int i,j;

    copie->num = source->num;
    copie->taille = source->taille;

    for(i = 0; i < TAILLE_MATRICE_PIECE; i++){
        for(j = 0; j < TAILLE_MATRICE_PIECE; j++){
            copie->mat[i][j]  = source->mat[i][j];
        }
    }
}

/* Insert la matrice de la piece */
void insertion_matrice_piece(t_matrice* piece, t_coordonnee coord){ 
    piece->mat[coord.x][coord.y] = 1;
}

/* Insert le numero de la piece */
void insertion_num_piece(t_matrice* piece, int numero){ 
    piece->num = numero;
}

/* Insert la taille de la piece */
void insertion_taille_piece(t_matrice* piece, int taille_piece){ 
    piece->taille = taille_piece;
}

/*Donne le miroir miroir_horizontal*/
void miroir_horizontal (int (*piece)[TAILLE_MATRICE_PIECE]) {
    int i, j, tampon, max = TAILLE_MATRICE_PIECE - 1;

    for (i = 0; i < max / 2; i++) {
        for (j = 0; j < TAILLE_MATRICE_PIECE; j++) {
            tampon = piece [i][j];
            piece [i] [j] = piece [max - i] [j];
            piece [max - i] [j] = tampon;
        }
    }
}

/*Donne le miroir vertical*/
void miroir_vertical (int (*piece)[TAILLE_MATRICE_PIECE]) {
    int i, j, tampon, max = TAILLE_MATRICE_PIECE - 1;

    for (i = 0; i < TAILLE_MATRICE_PIECE; i++) {
        for (j = 0; j < max / 2; j++) {
            tampon = piece [i][j];
            piece [i] [j] = piece [i] [max - j];
            piece [i] [max - j] = tampon;
        }
    }
}

/*Fait tourner la pièce*/
void tourner_piece (int (*piece)[TAILLE_MATRICE_PIECE]) {
    int i,j, tampon, max = TAILLE_MATRICE_PIECE - 1;

    for (j = 0; j < max - 1; j++) {
        for (i = j; i < max - j; i++) {
            tampon = piece[i] [j] ;
            piece[i] [j] = piece[max - j] [i];
            piece[max - j] [i] = piece[max - i] [max - j];
            piece[max - i] [max-j] = piece[j] [max - i];
            piece[j] [max - i] = tampon;
        }
    }
}

/*
sens = 1 rotation droite
sens = 2 retourner
sens = 3 rotation gauche
*/
void rotation (int (*piece)[TAILLE_MATRICE_PIECE], int sens) {
    int i;

    for (i = 0; i < sens; i++){
        tourner_piece(piece);
    }
}

#include "matrice.h"
#include "structures.h"

void init_matrice (t_matrice* matrice) { //FONCTIONNE CORRECTEMENT
	int i, j;

	matrice->taille = 0;
	matrice->num = 0;
	for (i = 0; i < TAILLE_MATRICE_PIECE; i++) {
		for (j = 0; j < TAILLE_MATRICE_PIECE; j++)
			matrice->mat[i][j] = 0;
	}
}
/* Affiche tous les elements de la liste, utile au debug et pour afficher la piece selectionner*/
void afficher_matrice (t_matrice matrice) { //FONCTIONNE CORRECTEMENT
	int i, j;

	for (i = 0; i < TAILLE_MATRICE_PIECE; i++) {
		for ( j = 0; j < TAILLE_MATRICE_PIECE; j++){
            if(matrice.mat[i][j] == 0){
                printf("|   ");
            }else{
                printf("| X ");
            }
		}
		printf("|");
		printf("\n");
	}
	printf("num = %i\n", matrice.num+1); // !! ATTTENTION n'affiche pas le numeros contenue dans la memoire ATTTENTION !!
    printf("taille = %i\n", matrice.taille);
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
void insertion_matrice_piece(t_matrice* matrice, t_coordonnee coord){ //FONCTIONNE CORRECTEMENT
    matrice->mat[coord.x][coord.y] = 1;
}

/* Insert le numero de la piece */
void insertion_num_piece(t_matrice* matrice, int numero){ //FONCTIONNE CORRECTEMENT
    matrice->num = numero;
}

/* Insert la taille de la piece */
void insertion_taille_piece(t_matrice* matrice, int taille_piece){ //FONCTIONNE CORRECTEMENT
    matrice->taille = taille_piece;
}

/*Donne le miroir miroir_horizontal*/
void miroir_horizontal (int (*mat)[TAILLE_MATRICE_PIECE]) {
    int i, j, tampon, max = TAILLE_MATRICE_PIECE - 1;

    for (i = 0; i < max / 2; i++) {
        for (j = 0; j < TAILLE_MATRICE_PIECE; j++) {
            tampon = mat [i][j];
            mat [i] [j] = mat [max - i] [j];
            mat [max - i] [j] = tampon;
        }
    }
}

/*Donne le miroir vertical*/
void miroir_vertical (int (*mat)[TAILLE_MATRICE_PIECE]) {
    int i, j, tampon, max = TAILLE_MATRICE_PIECE - 1;

    for (i = 0; i < TAILLE_MATRICE_PIECE; i++) {
        for (j = 0; j < max / 2; j++) {
            tampon = mat [i][j];
            mat [i] [j] = mat [i] [max - j];
            mat [i] [max - j] = tampon;
        }
    }
}

/*Fait tourner la pièce*/
void tourner_piece (int (*mat)[TAILLE_MATRICE_PIECE]) {
    int i,j, tampon, max = TAILLE_MATRICE_PIECE - 1;

    for (j = 0; j < max - 1; j++) {
        for (i = j; i < max - j; i++) {
            tampon = mat[i] [j] ;
            mat[i] [j] = mat[max - j] [i];
            mat[max - j] [i] = mat[max - i] [max - j];
            mat[max - i] [max-j] = mat[j] [max - i];
            mat[j] [max - i] = tampon;
        }
    }
}

/*
sens = 1 rotation droite
sens = 2 retourner
sens = 3 rotation gauche
*/
void rotation (int (*mat)[TAILLE_MATRICE_PIECE], int sens) {
    int i;

    for (i = 0; i < sens; i++){
        tourner_piece(mat);
    }
}

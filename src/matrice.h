#ifndef MATRICE_H
#define MATRICE_H
#include "structures.h"

typedef struct {
	int mat[5][5];
	int taille;
	int num;
}t_matrice;

void init_matrice (t_matrice* mat);
void afficher_matrice (t_matrice mat);
void copie_matrice(t_matrice* source, t_matrice* copie);
void insertion_matrice_piece(t_matrice* matrice, t_coordonnee coord);
void insertion_num_piece(t_matrice* matrice, int numero);
void insertion_taille_piece(t_matrice* matrice, int taille_piece);
void miroir_horizontal (int mat [5][5]);
void miroir_vertical (int mat [5][5]);
void tourner_piece (int mat [5][5]);
void rotation (int mat [5][5], int sens);

#endif

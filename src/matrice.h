#ifndef MATRICE_H
#define MATRICE_H
#include "structures.h"

 /** 
 * \brief structure t_matrice :Contient les informations d'une piece.
 */
typedef struct {
	int mat[5][5];	/**< Matrice ou l'on retrouve la piece */
	int taille;		/**< Taille qu'occupe la piece dans la matrice (3x3,2x3...) */
	int num;		/**< Numero de la piece correspondante */
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

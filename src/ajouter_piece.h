#ifndef AJOUTER_PIECE
#define AJOUTER_PIECE

#include "structures.h"
#include "liste.h"
#include "matrice.h"

void placer_posibiliter(int taille_plateau, t_case_m (*plateau)[taille_plateau], int y, int x, int joueur);
int placer_piece(int taille_plateau, t_case_m (*plateau)[taille_plateau], t_matrice matri, t_coordonnee coord, int joueur, int mode);

#endif

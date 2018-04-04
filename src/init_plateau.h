#ifndef INITPLATEAU
#define INITPLATEAU

#include "structures.h"
#include "liste.h"

void init_plateau(int taille_plateau, t_case_m (*plateau)[taille_plateau], int nbj_max, t_liste* liste_piece, int* player, int* score);
int coordonner_invalide(int x, int y, int taille_plateau);
void init_plateau_fictif(int taille_plateau, t_case_m (*plateau_original)[taille_plateau], t_case_m (*plateau_copie)[taille_plateau],int joueur, t_coordonnee* coord);
void copie_plateau(int taille_plateau, t_case_m (*plateau_original)[taille_plateau] , t_case_m (*plateau_copie)[taille_plateau]);
#endif

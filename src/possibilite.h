#ifndef POSSIBILITE
#define POSSIBILITE

#include "structures.h"
#include "liste.h"
#include "matrice.h"

int verif_posibiliter(int nb_tour, t_coordonnee** tab_dispo, int joueur, int* nb_dispo, t_liste* liste, int taille_plateau,t_case (*plateau)[taille_plateau]);
int possible_de_jouer(int taille_plateau, t_case (*plateau)[taille_plateau], int joueur, int nb_tour, t_coordonnee** tab_dispo, int* nb_dispo, t_liste* liste);

#endif

#ifndef AFFICHER_H
#define AFFICHER_H

#include "structures.h"


void affichage_menu_pause(void);
void affiche_plateau(int taille_plateau, t_case (*plateau)[taille_plateau], int joueur, int statut, int nbj_max);

#endif
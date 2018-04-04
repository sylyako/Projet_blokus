#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H

#include "structures.h"
#include "liste.h"

int charger_partie(void);
void sauvegarder_partie(int nbj, int nbj_max, int nb_tour_joueur, int* score, int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece);
int menu_pause(int nbj, int nbj_max, int nb_tour_joueur, int* score,int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece);

#endif

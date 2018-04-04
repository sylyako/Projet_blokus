#ifndef PARTIE
#define PARTIE

#include "liste.h"
#include "matrice.h"
#include "init_plateau.h"
#include "afficher.h"
#include "menu_pause.h"
#include "ajouter_piece.h"
#include "possibilite.h"
#include "IA.h"
#include "reseau.h"

void afficher_piece_dispo(int nb_piece, t_liste* liste);
int piece_dispo(int num_piece_choisi, t_liste* liste, t_matrice* piece);
void calcule_score(int nbj_max,int* score,int joueur, t_liste* liste);
int jeux(int nbj, int nbj_max, int nb_tour_joueur, int* score, int* joueur_en_jeux, int taille_plateau, t_case (*plateau)[taille_plateau],t_liste* liste_piece, int partie);

#endif

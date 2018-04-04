#ifndef IA_H
#define IA_H

#include "structures.h"
#include "liste.h"

typedef struct {
	int nb_rota;
	int numero_piece;
	int resultat;
	t_coordonnee coord;
}t_retour;

int calcul_1_score_placement(int taille_plateau, t_case (*plateau)[taille_plateau], int joueur);
int calcul_2_score_placement(int taille_piece, t_coordonnee* coord, int taille_plateau, int nb_tour_joueur);
void simuler_tour(int nbj_max, int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece, int cpt, int joueur, int nb_tour_joueur);
t_retour calcule_ia(int nbj_max, int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece, int cpt, int joueur, int nb_tour_joueur);
#endif

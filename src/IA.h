#ifndef IA_H
#define IA_H

#include "structures.h"
#include "liste.h"

 /** 
 * \brief structure t_retour : Structure permettant a l'IA de renvoyer la piece qu'il souhaite poser.
 */

typedef struct {
	int nb_rota;	/**< Nombre de rotations a effectuer */
	int numero_piece;		/**< Numero de la piece a poser */
	int resultat;			/**< Plus le resultat est haut, plus la position est bonne pour l'IA */
	t_coordonnee coord;	/**< Contient les coordonnees de la piece a placer */
}t_retour;

int calcul_1_score_placement(int taille_plateau, t_case_m (*plateau)[taille_plateau], int joueur);
int calcul_2_score_placement(int taille_piece, t_coordonnee* coord, int taille_plateau, int nb_tour_joueur);
void simuler_tour(int nbj_max, int* player, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_liste* liste_piece, int cpt, int joueur, int nb_tour_joueur);
t_retour calcule_ia(int nbj_max, int* player, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_liste* liste_piece, int cpt, int joueur, int nb_tour_joueur);
#endif

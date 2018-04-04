/**
*@file unicode.c
*@brief Fonctions d'affichage des cases du plateau avec des caractères unicode
*@details Contient deux fonctions pour l'affichage du haut d'une case et du bas d'une case en caractère unicode et avec gestion de couleur. Les caractères unicodes sont directement rentrés dans le code car sinon les lignes du plateau ne s'alignent pas correctement.
*@author Kevin Semamra
*@version 1.0
*@date mars 2018
*/

#include <stdlib.h>
#include <stdio.h>
#include "unicode.h"
#include "couleurs.h"
#include "structures.h"


/**
* \fn 		void aff_case_haut(int x, int y, int couleur, int nb_joueurs)
 * \brief      	Affiche le haut d'une case du plateau
 * \details   	Affiche les bordures de la partie haute de la case, ainsi que la couleur correspondant à
 *              une pièce ou une possibilité de placement pour le joueur courant.
 * \param    x		x représente un numéro de colonne.
 * \param    y          y représente un numéro de ligne.
 * \param    nb_joueurs	nb_joueurs est utilisé pour déterminé la longueur du plateau.
 */

void aff_case_haut(int x, int y, int couleur, int nb_joueurs) {

	if (y == 0 )
		printf("   ");
	printf("┃");	
	switch (couleur) {
		case rouge : couleur("41");break;
		case bleu : couleur("44");break;
		case vert : couleur("43");break;
		case jaune : couleur("42");break;
		case 5 : couleur("47");break;
		case libre : couleur("0");break;
	}
	x == 0 ? printf("▔▔▔"):printf("   ");
	
	couleur("0");
	if (nb_joueurs == 4 && y == 19)
		printf("┃\n");
	if (nb_joueurs == 2 && y == 13)
		printf("┃\n");
	
	
}


/**
* \fn 		void aff_case_bas (int x, int y, int couleur, int nb_joueurs)
 * \brief      	Affiche le bas d'une case du plateau
 * \details   	Affiche les bordures de la partie basse de la case, ainsi que la couleur correspondant à
 *              une pièce ou une possibilité de placement pour le joueur courant.
 * \param    x		x représente un numéro de colonne.
 * \param    y          y représente un numéro de ligne.
 * \param    nb_joueurs	nb_joueurs est utilisé pour déterminé la longueur du plateau.
 */

void aff_case_bas (int x, int y, int couleur, int nb_joueurs) {
	
		if (y == 0)
			x < 10 ? printf(" %i ", x):printf("%i ", x);
		printf("┃");
		switch (couleur) {
			case rouge : couleur("41");break;
			case bleu : couleur("44");break;
			case vert : couleur("43");break;
			case jaune : couleur("42");break;
			case 5 : couleur("47");break;
			case libre : couleur("0");break;
		}
		printf("▁͟▁▁");
		couleur("0");
		if (nb_joueurs == 4 && y == 19)
			printf("┃\n");
		if (nb_joueurs == 2 && y == 13)
			printf("┃\n");
		
			
}	




/* Toutes les fonctions d'affichage */

#include "structures.h"
#include "couleurs.h"
#include "unicode.h"


/**
 * \file afficher.c
 * \brief Ensemble de fonctions d'affichage
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void affichage_menu_pause(void)
 * \brief Affiche le menu de pause 
 * 
 *
 *
 * \fn void affiche_plateau(int taille_plateau, t_case (*plateau) [taille_plateau], int joueur, int statut, int nbj_max)
 * \brief Affiche le plateau de jeu 
 * \param taille_plateau La taille du plateau
 * \param (*plateau)[taille_plateau] Le plateau
 * \param joueur le joueur actuel
 * \param nbj_max Le nombre de joueurs
 *
 */



/* Affiche le menue de pause */
void affichage_menu_pause(void){
    printf("\nMenue de pause : \n");
	
    printf("	0.Passer son tour");
    printf("\n");
    printf("	1.Sauvegarder");
    printf("\n");
    printf("	2.Charger");
    printf("\n");
    printf("	3.Retouner au menue principale");
    printf("\n");
    printf("	4.Annuler");
    printf("\n");
    printf("--> Saisissez ici : ");
}

/* Affiche le plateau de jeu actuel */
void affiche_plateau(int taille_plateau, t_case (*plateau) [taille_plateau], int joueur, int statut, int nbj_max){
    int i,j;
	
       printf("y\\x ");
        for(i = 0; i < taille_plateau; i++){
            if (i < 10)
                printf(" %i  ",i);
            else
                printf(" %i ",i);
        }
        printf("\n");
        
	 /*Une case fait deux de longueur et de largeur, on doit alors traiter ligne par ligne,
	  *à cause du retour à la ligne
	 */ 
            
	    for(i = 0; i < taille_plateau; i++){

/***************** AFFICHAGE PARTIE HAUTE DES CASES SUR UNE LIGNE *******************/
                for(j = 0; j < taille_plateau; j++){

		/*On vérifie si la case actuelle est une possibilité pour le joueur*/

		     if (joueur == rouge && plateau[i][j].couleur == libre && plateau[i][j].possible_r) 
			aff_case_haut(i, j, 5, nbj_max);
		     else if (joueur == bleu && plateau[i][j].couleur == libre && plateau[i][j].possible_b) 
			aff_case_haut(i, j, 5, nbj_max);
		     else if (joueur == vert && plateau[i][j].couleur == libre && plateau[i][j].possible_v) 
			aff_case_haut(i, j, 5, nbj_max);
		     else if (joueur == jaune && plateau[i][j].couleur == libre && plateau[i][j].possible_j) 
			aff_case_haut(i, j, 5, nbj_max);

                /*Sinon, on affiche la couleur de la case */	
	
		     else {
			switch(plateau[i][j].couleur) {
				case rouge : aff_case_haut(i, j, rouge, nbj_max);break;
				case bleu  : aff_case_haut(i, j, bleu, nbj_max);break;
				case vert  : aff_case_haut(i, j, vert, nbj_max);break;
				case jaune : aff_case_haut(i, j, jaune, nbj_max);break;
				default : aff_case_haut(i, j, libre, nbj_max);break;
		  	}
                     }
                }
            	
/***************** AFFICHAGE PARTIE BASSE DES CASES SUR UNE LIGNE *******************/
               
                for(j = 0; j < taille_plateau; j++){

		/*On vérifie si la case actuelle est une possibilité pour le joueur*/

                    if (joueur == rouge && plateau[i][j].couleur == libre && plateau[i][j].possible_r) 
			aff_case_bas(i, j, 5, nbj_max);
		    else if (joueur == bleu && plateau[i][j].couleur == libre && plateau[i][j].possible_b) 
			aff_case_bas(i, j, 5, nbj_max);
		    else if (joueur == vert && plateau[i][j].couleur == libre && plateau[i][j].possible_v) 
			aff_case_bas(i, j, 5, nbj_max);
		    else if (joueur == jaune && plateau[i][j].couleur == libre && plateau[i][j].possible_j) 
			aff_case_bas(i, j, 5, nbj_max);

		/*Sinon, on affiche la couleur de la case */

		    else {
		  	switch(plateau[i][j].couleur) {
				case rouge : aff_case_bas(i, j, rouge, nbj_max);break;
				case bleu  : aff_case_bas(i, j, bleu, nbj_max);break;
				case vert  : aff_case_bas(i, j, vert, nbj_max);break;
				case jaune : aff_case_bas(i, j, jaune, nbj_max);break;
				default : aff_case_bas(i, j, libre, nbj_max);break;
		   	}
		    }
               }
          }

}



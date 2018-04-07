/* Toutes les fonctions d'affichage */

#include "afficher.h"
#include "unicode.h"

void affiche_plateau( t_plateau* plateau_jeu, int joueur, int statut, int nbj_max){
    int i,j;
	
       printf("y\\x ");
        for(i = 0; i < plateau_jeu->taille_plateau; i++){
            if (i < 10)
                printf(" %i  ",i);
            else
                printf(" %i ",i);
        }
        printf("\n");
        
	 /*Une case fait deux de longueur et de largeur, on doit alors traiter ligne par ligne,
	  *à cause du retour à la ligne
	 */ 
            
	    for(i = 0; i < plateau_jeu->taille_plateau; i++){

/***************** AFFICHAGE PARTIE HAUTE DES CASES SUR UNE LIGNE *******************/
                for(j = 0; j < plateau_jeu->taille_plateau; j++){

		/*On vérifie si la case actuelle est une possibilité pour le joueur*/

		     if (joueur == rouge && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_r) 
			aff_case_haut(i, j, 5, nbj_max);
		     else if (joueur == bleu && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_b) 
			aff_case_haut(i, j, 5, nbj_max);
		     else if (joueur == vert && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_v) 
			aff_case_haut(i, j, 5, nbj_max);
		     else if (joueur == jaune && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_j) 
			aff_case_haut(i, j, 5, nbj_max);

                /*Sinon, on affiche la couleur de la case */	
	
		     else {
			switch(plateau_jeu->plateau[i][j].couleur) {
				case rouge : aff_case_haut(i, j, rouge, nbj_max);break;
				case bleu  : aff_case_haut(i, j, bleu, nbj_max);break;
				case vert  : aff_case_haut(i, j, vert, nbj_max);break;
				case jaune : aff_case_haut(i, j, jaune, nbj_max);break;
				default : aff_case_haut(i, j, libre, nbj_max);break;
		  	}
                     }
                }
            	
/***************** AFFICHAGE PARTIE BASSE DES CASES SUR UNE LIGNE *******************/
               
                for(j = 0; j < plateau_jeu->taille_plateau; j++){

		/*On vérifie si la case actuelle est une possibilité pour le joueur*/

                    if (joueur == rouge && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_r) 
			aff_case_bas(i, j, 5, nbj_max);
		    else if (joueur == bleu && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_b) 
			aff_case_bas(i, j, 5, nbj_max);
		    else if (joueur == vert && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_v) 
			aff_case_bas(i, j, 5, nbj_max);
		    else if (joueur == jaune && plateau_jeu->plateau[i][j].couleur == libre && plateau_jeu->plateau[i][j].possible_j) 
			aff_case_bas(i, j, 5, nbj_max);

		/*Sinon, on affiche la couleur de la case */

		    else {
		  	switch(plateau_jeu->plateau[i][j].couleur) {
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




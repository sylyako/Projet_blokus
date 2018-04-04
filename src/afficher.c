/* Toutes les fonctions d'affichage */

#include "structures.h"
#include "couleurs.h"
#include "unicode.h"

/*Affichage des regles du BLOKUS en "brut". Il faudra la completer pour le SDL*/
void affichage_regles(void){
	char carac;
	FILE * regles;

	regles = fopen("regles.txt","r");

	printf("\n**** REGLES DU BLOKUS ****\n\n");

	while(!feof(regles)){
		fscanf(regles,"%c",&carac);
		printf("%c",carac);
	}
	fclose(regles);
}


/*Proc�dure qui affiche les diff�rents menu*/
void affichage_menu_pincipale(int mode){

    if(mode == 1){

        printf("Veuillez saisir le mode de jeu qui vous convient : \n");

        printf("	1.Jeux Local");
        printf("\n");
        printf("	2.Jeux en r�seaux");
        printf("\n");
        printf("	3.Reprendre une partie");
        printf("\n");
        printf("	4.Voir les regles");
        printf("\n");
        printf("	5.Quitter");
        printf("\n");
        printf("--> Saisissez ici : ");

    }else if(mode == 2){
        printf("Quel mode de jeu voulez vous : \n");

        printf("	1. 2 joueurs");
        printf("\n");
        printf("	2. 4 joueurs");
        printf("\n");
        printf("	3. Retour menu principale");
        printf("\n");
        printf("--> Saisissez ici : ");

    }
}

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

/* Affiche le plateau de jeux actuel */
void affiche_plateau(int taille_plateau, t_case_m (*plateau)[taille_plateau], int joueur, int statut){
    int i,j;
    
    if (statut == 0){ //affichage simple
        
        printf(" y\\x  ");
        for(i = 0; i < taille_plateau; i++){
            if (i < 10){
                printf(" %i  ",i);
            }else{
                printf(" %i ",i);
            }
        }
        printf("\n");
        for(i = 0; i < taille_plateau; i++){
            if (i < 10){
                printf(" %i   ",i);
            }else{
                printf(" %i  ",i);
            }
            for(j = 0; j < taille_plateau; j++){
                if(plateau[i][j].couleur == rouge){
                    printf("| R ");
                }else if(plateau[i][j].couleur == bleu){
                    printf("| B ");
                }else if(plateau[i][j].couleur == vert){
                    printf("| V ");
                }else if(plateau[i][j].couleur == jaune){
                    printf("| J ");
                }else{
                    printf("|   ");
                }
            }
            printf("|");
            printf("\n");
        }
    }else{ //affichage avec les case disponibles
        printf(" y\\x  ");
        for(i = 0; i < taille_plateau; i++){
            if (i < 10){
                printf(" %i  ",i);
            }else{
                printf(" %i ",i);
            }
        }
        printf("\n");
        if(joueur == rouge){ //economiese au minimum 0 et au maximum nbj*(taille_plateau)² -4 (~= 1600 pour 4 joueur) verification par appel
            for(i = 0; i < taille_plateau; i++){
                if (i < 10){
                    printf(" %i   ",i);
                }else{
                    printf(" %i  ",i);
                }
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].couleur == libre && plateau[i][j].possible_r){ //Si la case est libre et que le joueur rouge a la possibiliter de jouer ici
                        printf("| O ");
                    }else if(plateau[i][j].couleur == rouge){
                        printf("| R ");
                    }else if(plateau[i][j].couleur == bleu){
                        printf("| B ");
                    }else if(plateau[i][j].couleur == vert){
                        printf("| V ");
                    }else if(plateau[i][j].couleur == jaune){
                        printf("| J ");
                    }else{
                        printf("|   ");
                    }
                }
                printf("|");
                printf("\n");
            }
        }else if(joueur == bleu){
            for(i = 0; i < taille_plateau; i++){
                if (i < 10){
                    printf(" %i   ",i);
                }else{
                    printf(" %i  ",i);
                }
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].couleur == libre && plateau[i][j].possible_b){ //Si la case est libre et que le joueur bleu a la possibiliter de jouer ici
                        printf("| O ");
                    }else if(plateau[i][j].couleur == rouge){
                        printf("| R ");
                    }else if(plateau[i][j].couleur == bleu){
                        printf("| B ");
                    }else if(plateau[i][j].couleur == vert){
                        printf("| V ");
                    }else if(plateau[i][j].couleur == jaune){
                        printf("| J ");
                    }else{
                        printf("|   ");
                    }
                }
                printf("|");
                printf("\n");
            }
        }else if(joueur == vert){
            for(i = 0; i < taille_plateau; i++){
                if (i < 10){
                    printf(" %i   ",i);
                }else{
                    printf(" %i  ",i);
                }
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].couleur == libre && plateau[i][j].possible_v){ //Si la case est libre et que le joueur vert a la possibiliter de jouer ici
                        printf("| O ");
                    }else if(plateau[i][j].couleur == rouge){
                        printf("| R ");
                    }else if(plateau[i][j].couleur == bleu){
                        printf("| B ");
                    }else if(plateau[i][j].couleur == vert){
                        printf("| V ");
                    }else if(plateau[i][j].couleur == jaune){
                        printf("| J ");
                    }else{
                        printf("|   ");
                    }
                }
                printf("|");
                printf("\n");
            }
        }else{
            for(i = 0; i < taille_plateau; i++){
                if (i < 10){
                    printf(" %i   ",i);
                }else{
                    printf(" %i  ",i);
                }
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].couleur == libre && plateau[i][j].possible_j){ //Si la case est libre et que le joueur jaune a la possibiliter de jouer ici
                        printf("| O ");
                    }else if(plateau[i][j].couleur == rouge){
                        printf("| R ");
                    }else if(plateau[i][j].couleur == bleu){
                        printf("| B ");
                    }else if(plateau[i][j].couleur == vert){
                        printf("| V ");
                    }else if(plateau[i][j].couleur == jaune){
                        printf("| J ");
                    }else{
                        printf("|   ");
                    }
                }
                printf("|");
                printf("\n");
            }
        }
    }
}

#include "structures.h"
#include "Partie.h"


void affichage_regle(void){
	char carac;
	FILE * regles;

	regles = fopen("ressources/regles.txt","r");

	printf("\n**** REGLES DU BLOKUS ****\n\n");

	while(!feof(regles)){
		fscanf(regles,"%c",&carac);
		printf("%c",carac);
	}
	fclose(regles);
}

void nb_ia(int *nbj,int nbj_max){

    do{
        printf("\n--> Saisissez le nombre d'ordinateur : ");
        scanf("%i",nbj);

    }while(*nbj < 0 || *nbj >= nbj_max );

}

int commencer_partie( int partie);

int type_joueur () {
    int choix;

    printf("    1. Créer une partie\n");
    printf("    2. Rejoindre une partie\n");
    printf("    3. Retour au menu\n");
    printf("--> Saisissez ici : ");
    scanf("%i",&choix);

    switch(choix) {
        case 1: commencer_partie(1);break;
        case 2: commencer_partie(2);break;
	case 3: return(1);break;
    }
    return(1);
}

int commencer_partie( int partie){
    int nbj; //nb joueur ia
    int nbj_max; // nombre total de joueur
    int choix,retour;

    printf("    1. 4 joueur\n");
    printf("    2. 2 joueur\n");
    printf("    3. Retour au menu\n");
    printf("--> Saisissez ici : ");
    scanf("%i",&choix);

    switch(choix){

        case 1:{
            nbj_max = 4;
            int score[nbj_max], joueur_en_jeux[nbj_max],taille_plateau = 20;
            t_liste liste_piece[nbj_max];
            t_case plateau [taille_plateau][taille_plateau];
	    if (partie == 0)
            	nb_ia(&nbj,nbj_max);
	    else
		nbj = 0;
            init_plateau(taille_plateau,plateau,nbj_max,liste_piece,joueur_en_jeux,score);

            retour = jeux(nbj,nbj_max,0,score,joueur_en_jeux,taille_plateau,plateau,liste_piece, partie);
            if(retour == 4){
                return(4);
            }else{
                return(1);
            }
            break;
        }
       

    case 2:{
            nbj_max = 2;
            int score[nbj_max], joueur_en_jeux[nbj_max],taille_plateau = 14;
            t_liste liste_piece[nbj_max];
            t_case plateau [taille_plateau][taille_plateau];

           if (partie == 0)
            	nb_ia(&nbj,nbj_max);
	    else
		nbj = 0;

            init_plateau(taille_plateau,plateau,nbj_max,liste_piece,joueur_en_jeux,score);

            retour = jeux(nbj,nbj_max,0,score,joueur_en_jeux,taille_plateau,plateau,liste_piece, partie);
            if(retour == 4){
                return(4);
            }else{
                return(1);
            }
            break;
        }
     case 3:
            return(1);
            break;
    }
    return(1);
}

int main(){
    int choix = 1;

    printf("        ####################################################################\n");
    printf("        ####################################################################\n");
    printf("        ####                                                            ####\n");
    printf("        ####                                                            ####\n");
    printf("        ####   ####    ##       ####     ##   ##   ##     ##    ####    ####\n");
    printf("        ####   ## ##   ##      ##  ##    ##  ##    ##     ##   ##  ##   ####\n");
    printf("        ####   ## ##   ##     ##    ##   ## ##     ##     ##   ##       ####\n");
    printf("        ####   ####    ##     ##    ##   ####      ##     ##    ####    ####\n");
    printf("        ####   ## ##   ##     ##    ##   ## ##     ##     ##       ##   ####\n");
    printf("        ####   ## ##   ##      ##  ##    ##   ##   ##     ##   ##  ##   ####\n");
    printf("        ####   ####    #####    ####     ##    ##    #####      ####    ####\n");
    printf("        ####                                                            ####\n");
    printf("        ####                                                            ####\n");
    printf("        ####################################################################\n");
    printf("        ####################################################################\n");


    printf("\n\n\n");

    do{
        if(choix != 3){
            printf("\n");
            printf("    1. Jeu Local\n");
            printf("    2. Jeu Reseau\n");
            printf("    3. Charger une partie\n");
	    printf("    4. Afficher règles\n");
            printf("    5. Quitter le jeu\n");
            printf("\n");
            printf("--> Saisissez ici : ");
            scanf("%i",&choix);
        }

        if(choix == 1){
            if(commencer_partie(0) == 4){
                if(charger_partie() == 4){
                    choix = 3;
            	}
            }
	}else if (choix == 2){
	    type_joueur ();

        }else if(choix == 3){
            printf("La partie a bien ete charger\n");
            if(charger_partie() == 1){
                choix = 1;
            }
        }else if (choix == 4)
		affichage_regle();

    }while(choix != 5);

    return(0);
}

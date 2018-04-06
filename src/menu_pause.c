/* Menue de pause + sauvegarde et charge */

#include "menu_pause.h"
#include "Partie.h"
#include "afficher.h"


/**
 * \file menu_pause.c
 * \brief Fonctions de sauvegarde, de chargement et du menu de pause
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn int charger_partie()
 * \brief Charge une partie à partir d'un fichier de sauvegarde
 *
 *
 * \fn void sauvegarder_partie(int nbj, int nbj_max, int nb_tour_joueur, int* score, int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece){
 * \brief Sauvegarde la partie
 * \details Enregistre dans un fichier l'état du plateau, les pièces restantes de chaque joueur ainsi que leur score et à qui c'est le tour de jouer
 * \param nbj Nombre de joueurs ordinateurs
 * \param nbj_max Nombre de joueurs
 * \param nb_tour_joueur Le tour
 * \param *score Tableau des scores des joueurs
 * \param *player
 * \param taille_plateau La taille du plateau
 * \param (*plateau)[taille_plateau] Le plateau
 * \param *liste_piece Les listes de pièces des joueurs 
 *
 *
 * \fn menu_pause(int nbj, int nbj_max, int nb_tour_joueur, int* score,int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece)
 * \brief Le menu de pause
 * \param nbj Nombre de joueurs ordinateurs
 * \param nbj_max Nombre de joueurs
 * \param nb_tour_joueur Le tour
 * \param *score Tableau des scores des joueurs
 * \param *player
 * \param taille_plateau La taille du plateau
 * \param (*plateau)[taille_plateau] Le plateau
 * \param *liste_piece Les listes de pièces des joueurs 
 */

int charger_partie(){
    // retourne une valeur qui fera quitter jusqu'au menu principale
    //ou jeux(nbj,nbj_max,0,score,player,taille_plateau,plateau,piece);
    // Apres avoir choisi le fichier de sauvegarde, on le copie sur un autre fichier et on retourne une valeur spécial (return(100) ?)qui fera dire au menu principale de charger ce fichier
    int caractereActuel;
    int nbj, nbj_max,nb_tour_joueur = 0, taille_plateau, nb_piece, num_piece;
    int i = 1,j,k;
    t_matrice piece;
    FILE *fichier;

	

    fichier = fopen("ressources/SAV1", "r");
    caractereActuel = fgetc(fichier);
    nbj = caractereActuel - 48;		//nb joueur humain
    caractereActuel = fgetc(fichier);
    nbj_max = caractereActuel - 48;	//nb total de joueur
	printf("\n nbj%i nbj_max%i \n",nbj,nbj_max);
    caractereActuel = fgetc(fichier);
    while(caractereActuel != 59){ // 59 = ;
        nb_tour_joueur = (nb_tour_joueur*i) + (caractereActuel - 48);	//nb de tour de joueur effectuer(definie indirectement sur quel joueur on s'est arreter)
        i*=10;
	caractereActuel = fgetc(fichier);
    }

    i = 1;

    int score[nbj_max],player[nbj_max];
    t_liste liste_piece[nbj_max];

    for(j = 0; j < nbj_max; j++){
	score[j] = 0;
	caractereActuel = fgetc(fichier);
        while(caractereActuel != 59){
            score[j] = (score[j]*i) + (caractereActuel - 48);	// score de chaque joueur
            i*=10;
	    caractereActuel = fgetc(fichier);
        }
	i = 1;
    }

    for(i = 0; i < nbj_max; i++){
        caractereActuel = fgetc(fichier);
        player[i] = caractereActuel -48;		//Quel joueur peut encore jouer (quel joueur est encore en jeu)
    }
	
    caractereActuel = fgetc(fichier);
    if(caractereActuel == '1'){
        taille_plateau = 14;		// La taille du plateau
    }else{
        taille_plateau = 20;
    }


    t_case plateau[taille_plateau][taille_plateau];
    caractereActuel = fgetc(fichier);

    for(i = 0; i < taille_plateau; i++){		// Initialisation du plateau
        for(j = 0; j < taille_plateau; j++){
            plateau[i][j].couleur = caractereActuel - 48;
            caractereActuel = fgetc(fichier);
            plateau[i][j].possible_r = caractereActuel - 48;
            caractereActuel = fgetc(fichier);
            plateau[i][j].possible_b = caractereActuel - 48;
            caractereActuel = fgetc(fichier);
            plateau[i][j].possible_v = caractereActuel - 48;
            caractereActuel = fgetc(fichier);
            plateau[i][j].possible_j = caractereActuel - 48;
            caractereActuel = fgetc(fichier);
        }
    }

    for(j = 0; j < nbj_max; j++){	//Pour chaque joueur
        i = 1;
        nb_piece = 0;
        while(caractereActuel != 59){	//recupere le nombre de piece qu'il reste au joueur i
            nb_piece = (nb_piece * i) + caractereActuel - 48;
            i *= 10;
            caractereActuel = fgetc(fichier);
        }

        caractereActuel = fgetc(fichier);

        init_liste(&liste_piece[j]);
        remplir_listes(&liste_piece[j]);  //On remplie la liste de piece du joueur avec tout les piece
        en_tete(&liste_piece[j]);

        for(k = 0; k < nb_piece; k++){ //pour chaque piece du joueur enregistree dans la sauvegarde

            val_elem(&liste_piece[j],&piece);
            i = 1;
            num_piece = 0;
            while(caractereActuel != 59){	//recupere le numero de la piece enregistree dans la sauvegarde
                num_piece = (num_piece*i) + caractereActuel - 48;
                i *= 10;
                caractereActuel = fgetc(fichier);
            }

            caractereActuel = fgetc(fichier);

            while(num_piece != piece.num && !hors_liste(&liste_piece[j])){ // Tant que le numero de la piece enregistree dans la sauvegarde n'est pas le meme que celui de la liste
                oter_elt(&liste_piece[j]);	//On retire cette element et passe au suivant
                val_elem(&liste_piece[j],&piece);
            }
            suivant(&liste_piece[j]);
        }
        printf("\n");

    }

    fclose(fichier);

    if(jeux(nbj,nbj_max,nb_tour_joueur,score,player,taille_plateau,plateau,liste_piece, 0 ) == 1){
        return(1);
    }else{
        return(4);
    }
	
    return(1);

}

void sauvegarder_partie(int nbj, int nbj_max, int nb_tour_joueur, int* score, int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece){ //Sauvegarde sur un fichier unique des donnée pour reprendre la partie
    FILE *fichier;
    int i , j, cpt;
    t_matrice piece;

    fichier = fopen("ressources/SAV1", "w+");

    fprintf(fichier,"%i",nbj);

    fprintf(fichier,"%i",nbj_max);

    fprintf(fichier,"%i;",nb_tour_joueur);


    for(i = 0; i < nbj_max; i++){
        fprintf(fichier,"%i;",score[i]);
    }

    for(i = 0; i < nbj_max; i++){
        fprintf(fichier,"%i",player[i]);
    }

    if(taille_plateau == 20){
        fprintf(fichier,"%i",2);
    }else{
        fprintf(fichier,"%i",1);
    }

    for(i = 0; i < taille_plateau; i++){
        for(j = 0; j < taille_plateau; j++){
            fprintf(fichier,"%i%i%i%i%i",plateau[i][j].couleur,plateau[i][j].possible_r,plateau[i][j].possible_b,plateau[i][j].possible_v,plateau[i][j].possible_j);
        }
    }

    for(i = 0; i < nbj_max; i++ ){
        en_tete(&liste_piece[i]);
        cpt = 0;
        while(!hors_liste(&liste_piece[i])){
            cpt ++;
            suivant(&liste_piece[i]);
        }
        fprintf(fichier,"%i;",cpt);

        en_tete(&liste_piece[i]);
        for(j = 0; j < cpt; j++){
            val_elem(&liste_piece[i],&piece);
            fprintf(fichier,"%i;",piece.num);
            suivant(&liste_piece[i]);
        }
    }

    fclose(fichier);

}

int menu_pause(int nbj, int nbj_max, int nb_tour_joueur, int* score,int* player, int taille_plateau, t_case (*plateau)[taille_plateau], t_liste* liste_piece){
    int choix;

    do{
        affichage_menu_pause();
        scanf("%i",&choix);
        fflush(stdout);
        switch(choix){

            case 0 : //Passer son tour
                return(2);
                break;
            case 1 : // Sauvegarder la partie
                sauvegarder_partie(nbj,nbj_max,nb_tour_joueur,score,player,taille_plateau,plateau,liste_piece);
                printf("\nVotre partie a bien ete sauvegarder\n\n");
                break;
            case 2 : // Charger la partie
                return(4);
                break;
            case 3 : // Retour au menu
                printf("\nRetour menu principale\n\n");
                return (1);
                break;
            case 4 : // Fermer le menue de pause
                printf("\nFermeture du menu de pause\n\n\n");
                return(3);
                break;
           default :
                printf("\nErreur de saisie\n\n");
                break;
        }
    }while (choix != 4 && choix != 0);
    return (1);
}

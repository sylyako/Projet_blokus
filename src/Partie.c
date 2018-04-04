#include "Partie.h"


/* Affiche tout les numero des pieces restantes en utilisant */
void afficher_piece_dispo(int nb_piece, t_liste* liste){
    int i = 0;
    t_matrice piece;

    en_tete(liste);
    while(!hors_liste(liste)){
        val_elem(liste,&piece);
        printf(" %i",piece.num+1);
        suivant(liste);
    }
    en_tete(liste);
}

/* Verifie si le numero de la piece choisi est bien une piece disponible dans laa liste du joueur, si c'est le cas on note tout les information de la piece */
int piece_dispo(int num_piece_choisi, t_liste* liste, t_matrice* piece){
    int i;

    en_tete(liste);
    val_elem(liste,piece);
    while(piece->num != num_piece_choisi && !hors_liste(liste)){
        suivant(liste);
        val_elem(liste,piece);
    }
    if(hors_liste(liste)){
        return(0);
    }

    return(1);
}

/* Calcule le score final */
void calcule_score(int nbj_max,int* score,int joueur, t_liste* liste){
    t_matrice piece;
    en_tete(liste);

    if (!hors_liste(liste)){
    	while(!hors_liste(liste)){
            val_elem(liste,&piece);
            suivant(liste);
            score[joueur] = score[joueur] - piece.taille;
    	}
    }
    en_tete(liste);
}

/* Fonction de jeux */
int jeux(int nbj, int nbj_max, int nb_tour_joueur, int* score, int* joueur_en_jeux, int taille_plateau, t_case (*plateau)[taille_plateau],t_liste* liste_piece, int partie){
    int nb_joueur_en_jeux = 0, nb_piece, nb_dispo = 0, choix, menu, statut, rotat, num;
    int i,j,l,x,y,cpt = nbj_max;
    int tab_piece[TAILLE_MAX];
    int mon_num;
    int socket_client [4];
    int socket_serveur;
    int socket_client1;
    t_matrice piece;
    t_couleur joueur = nb_tour_joueur % nbj_max; // 0 = rouge, 1 = bleu, 2 = vert, 3 = jaune
    t_coordonnee* tab_dispo, coord; //tableau dynamique qui contiendra tout les possibiliter ou l'on peut jouer
    t_retour ret;

    if(nbj_max == 4){   //mode 4 joueur
        taille_plateau = 20;
    }else{              // mode 2 joueur(*tab_dispo)[k];
        taille_plateau = 14;
    }

    for(i = 0; i < nbj_max; i++){
        if (joueur_en_jeux[i] == 1){
            nb_joueur_en_jeux ++;
        }
    }
	
     if (partie == 1) {
        init();

	char message_tt_present [] = "Tous les joueurs sont présents !";
        
        struct sockaddr_in adresse_serveur;
        struct sockaddr_in adresse_client [4];

        init_serveur (&socket_serveur, &adresse_serveur);
	mon_num = 0;
        listen(socket_serveur, nbj_max -1);
        ajout_clients(&socket_serveur, socket_client, nbj_max);
	
    }

    if (partie == 2) {
        init();

	char message_serveur [250];
        
        struct sockaddr_in server_address;

        socket_client1 = socket(AF_INET, SOCK_STREAM, 0);
        if (connexion_serveur(&socket_client1, &server_address) == 0) {
            printf("Connexion réussie !\n");

        }else {
            printf("Erreur : Connexion échouée !\n");
	    close (socket_client1);
	    return 0;
	}
	
	while (!recv (socket_client1, message_serveur, sizeof(message_serveur), 0));
	printf("Message du serveur : %s\n", message_serveur);
	
        mon_num = 1;
	
	
   }
    
       
    while(nb_joueur_en_jeux >= 1){
	
        statut = 0;
        tab_dispo = NULL; // pour chaque joueur on remet a 0 le tableau des possibiliter
        nb_dispo = 0;
        if(joueur_en_jeux[joueur] == 1){
            affiche_plateau(taille_plateau,plateau,joueur,1, nbj_max);
            if(possible_de_jouer(taille_plateau, plateau, joueur, nb_tour_joueur/4, &tab_dispo, &nb_dispo,&liste_piece[joueur])){
                if(joueur < nbj_max-nbj){ //Si le joueur est un humain
                   if ((joueur == mon_num && (partie == 1 || partie == 2)) || partie == 0) { 
			do{
		                printf("Tour joueur %i\n",joueur+1);
		                printf("	0. Menu Pause");
		                printf("\n");
		                afficher_piece_dispo(nb_piece,&liste_piece[joueur]);
		                printf("\n");
						
						
		                printf("--> Saisissez ici : ");
		                scanf("%i",&choix);
		                fflush(stdout);
		                printf("\n");
		                if(choix > 0 && choix < 22){ // choix d'une piece de 1 a 21
		                    if(piece_dispo(choix-1, &liste_piece[joueur], &piece)){ //si la piece choisi est bien dans la liste des pieces du joueur, on recuperes toutes les informations sur cette piece
		                        do{
		                            afficher_matrice(piece);
		                            printf("\n");
		                            printf("Tour joueur %i\n",joueur+1);
		                            printf("    0. Menu de pause\n");
		                            printf("    1. Oui je veux cette piece\n");
		                            printf("    2. Rotation a Gauche\n");
		                            printf("    3. Rotation a Droit\n");
		                            printf("    4. Rotation mirroir vertical\n");
		                            printf("    5. Rotation mirroir horizontale\n");
		                            printf("    6. Retour au choix de piece\n");
		                            printf("--> Saisissez ici : ");
		                            scanf("%i",&choix);
		                            fflush(stdout);
		                            printf("\n");

		                            switch(choix){

		                                case 0 :
		                                    menu = menu_pause(nbj,nbj_max,nb_tour_joueur,score,joueur_en_jeux,taille_plateau,plateau,liste_piece);
		                                    if(menu == 1){ // retour menu principale
		                                        return(1);
		                                    }else if(menu == 2){
		                                        statut = 1;
		                                    }else if(menu == 4){ // charger la sauvegarde en cours de partie
		                                        return(4);
		                                    }
		                                   break;

		                                case 1 :
		                                    affiche_plateau(taille_plateau, plateau, joueur,1, nbj_max);
		                                    printf("Entree les coordonne ou placer la piece(-1 pour retourner au choix des pieces)\n");
		                                    printf("\nx : ");
		                                    scanf("%i",&x);
		                                    if (x == -1){
		                                        printf("\nRetour au choix des pieces\n\n");
		                                        choix = 22;
		                                        break;
		                                    }
		                                    printf("y : ");
		                                    scanf("%i",&y);
		                                    if (y == -1){
		                                        printf("\nRetour au choix des pieces\n\n");
		                                        choix = 22;
		                                        break;
		                                    }
		                                    coord.x = x;
		                                    coord.y = y;
		                                    if(!coordonner_invalide(x,y,taille_plateau) && placer_piece(taille_plateau, plateau, piece, coord, joueur,0)){
		                                        oter_elt(&liste_piece[joueur]);
		                                        if(piece.num == 0){
		                                            if(hors_liste(&liste_piece[joueur])){
		                                                score[joueur] += 15;
		                                            }
		                                        }
		                                    }else{
		                                        printf("\nVous ne pouvez pas placer votre piece ici\n\n");
		                                        choix = 22;
		                                    }
		                                    break;

		                                case 2 :
		                                    rotation(piece.mat,3);
		                                    break;

		                                case 3 :
		                                    rotation(piece.mat,1);
		                                    break;

		                                case 4 :
		                                    miroir_vertical(piece.mat);
		                                    break;

		                                case 5 :
		                                    miroir_horizontal(piece.mat);
		                                    break;

		                                case 6 : // Retour
		                                    printf("\nRetour au choix des pieces\n\n");
		                                    choix = 22;
		                                    break;

		                                default :
		                                    printf("Erreur de saisie\n");
		                                    break;

		                            }
                                }while (choix != 22 && choix != 1 && statut != 1);

                            }else{ //Si le numero de la piece choisi n'est pas dans la liste des pieces du joueur, on relance la selection
                                printf("La piece choisie a deja ete placer\n");
                                choix = 22;
                            }
                        }else if(choix == 0){ // menue de sauvegarde, charge, quitter et passer tour
                           menu = menu_pause(nbj,nbj_max,nb_tour_joueur,score,joueur_en_jeux,taille_plateau,plateau,liste_piece);
                           if(menu == 1){ // retour menu principale
                                return(1);
                            }else if(menu == 2){ //Passer son tour
                                statut = 1;
                            }else if(menu == 4){ // charger la sauvegarde en cours de partie
                                return(4);
                            }
                        }else{
                            printf("\nSaisie incorrect, recommencer\n\n");
                        }
                    }while ((choix < 1 || choix > 21) && statut != 1);
		  }	

		 
		   
			
                   if (partie == 1 && joueur == mon_num) {
			envoyer_plateau_clients( socket_client, taille_plateau, plateau, nbj_max);
		  	affiche_plateau(taille_plateau,plateau,joueur,0, nbj_max);
		   }
		   	nv_plateau( socket_client [joueur], taille_plateau, plateau);
		   if (partie == 2 && joueur == mon_num) {
			envoyer_plateau( socket_client1, taille_plateau, plateau);
		  }else if (partie == 2 && joueur != mon_num)
			nv_plateau( socket_client1, taille_plateau, plateau);
		 
		
                }else{
                   // printf("nb tour = %i\n",nb_tour_joueur);
                   // printf("Tour joueur %i\n",joueur+1);
                    ret = calcule_ia(nbj_max,joueur_en_jeux,taille_plateau,plateau,liste_piece,2,joueur,nb_tour_joueur); //On lance le tour de l'ia
                    //printf("On sort avec %i rota, %i num, %i coord.x, %i coord.y, resultat %i\n",ret.nb_rota,ret.numero_piece,ret.coord.x,ret.coord.y,ret.resultat);
                    if(piece_dispo(ret.numero_piece, &liste_piece[joueur], &piece)){
                        if(joueur %2 == 0){
                            rotation(piece.mat,1);
                        }
                        for(l = 1; l <= ret.nb_rota; l++){
                            rotation(piece.mat,1);
                            if(l == 4 || l == 8){
                                miroir_vertical(piece.mat);
                            }
                        }
                        if(placer_piece(taille_plateau,plateau,piece,ret.coord,joueur,3) == 0){
                            printf("ZUT TU A TROUVER UN BUG !!!\n");
                            printf("On a pas réussie a placer la piece dans le plateau\n");
                            scanf("%i",&y);
                        }
                        oter_elt(&liste_piece[joueur]);
                        if(piece.num == 0){
                            if(hors_liste(&liste_piece[joueur])){
                                score[joueur] += 15;
                            }
                        }
                    }else{
                        printf("ZUT TU A TROUVER UN BUG !!!\n");
                        printf("La piece selectionner par l'ia n'est pas dans sa liste de piece\n");
                        scanf("%i",&y);
                    }
                }
            }else{
               statut = 1;
            }
            if(statut == 1){
                printf("\nJoueur %i passe son tour\n\n",joueur+1);
                joueur_en_jeux[joueur] = 0;
                nb_joueur_en_jeux --;
                calcule_score(nbj_max, score, joueur, &liste_piece[joueur]);
                statut = 0;
            }
        }
        /* Change de joueur */
        if(nbj_max == 4){
            if(joueur == 3){
                joueur = 0;
            }else{
                joueur++;
            }
        }else{
	    
            if(joueur == 1){
                joueur = 0;
            }else{
                joueur ++;
            }
        }
        free(tab_dispo);
        nb_tour_joueur++;
    }

    for(i = 0; i < nbj_max; i++){
        for(j = 0; j < nbj_max; j++){
            if(score[i] > score[j]){
                cpt --;
            }
        }
        printf("Le joueur %i est arriver %i avec %i\n", i+1, cpt, score[i]);
        cpt = nbj_max;
    }
    affiche_plateau(taille_plateau,plateau,joueur,0, nbj_max);
    close(socket_serveur);
    return (1);
}

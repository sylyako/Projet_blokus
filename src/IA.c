#include "structures.h"
#include "liste.h"
#include "matrice.h"
#include "init_plateau.h"
#include "afficher.h"
#include "ajouter_piece.h"
#include "possibilite.h"
#include "dessine.h"
#include "sdl.h"
#include <string.h>
#include "Partie.h"
#include "IA.h"


/* Calcule le score de placement quand on arrive en bas de l'arbre */
int calcul_1_score_placement(int taille_plateau, t_case_m (*plateau)[taille_plateau], int joueur){
    int i,j;
    float cpt = 0;

    if(joueur == rouge){
        for(i = 0; i< taille_plateau; i++){
            for(j = 0; j < taille_plateau; j++){
                if(plateau[i][j].possible_r == 1){
                    cpt += 3.5;
                }
                if(plateau[i][j].possible_b == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_v == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_j == 1){
                    cpt --;
                }
            }
        }
    }else if(joueur == bleu){
        for(i = 0; i< taille_plateau; i++){
            for(j = 0; j < taille_plateau; j++){
                if(plateau[i][j].possible_b == 1){
                    cpt += 3.5;
                }
                if(plateau[i][j].possible_v == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_j == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_r == 1){
                    cpt --;
                }
            }
        }
        cpt += 3; //Bonus car le joueur rouge a jouer avant
    }else if (joueur == vert){
        for(i = 0; i< taille_plateau; i++){
            for(j = 0; j < taille_plateau; j++){
                if(plateau[i][j].possible_v == 1){
                    cpt += 3.5;
                }
                if(plateau[i][j].possible_j == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_r == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_b == 1){
                    cpt --;
                }
            }
        }
        cpt += 6;
    }else{
        for(i = 0; i< taille_plateau; i++){
            for(j = 0; j < taille_plateau; j++){
                if(plateau[i][j].possible_j == 1){
                    cpt += 3.5;
                }
                if(plateau[i][j].possible_r == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_b == 1){
                    cpt --;
                }
                if(plateau[i][j].possible_v == 1){
                    cpt --;
                }
            }
        }
        cpt += 9;
    }
    return ((int)cpt);
}

/* Calcule le bonus du score de placement */
int calcul_2_score_placement(int taille_piece, t_coordonnee* coord, int taille_plateau,int nb_tour_joueur){
    int cpt = 2*(taille_piece);
    int bonus = 1;
    if(nb_tour_joueur < 12){
        bonus = 10;
    }

    if(((taille_plateau - coord->x) > 2 && (taille_plateau - coord->x) < 17) && ((taille_plateau - coord->y) > 2 && (taille_plateau - coord->y) < 17)){
        cpt += (bonus/5) + 1;
        if(((taille_plateau - coord->x) > 5 && (taille_plateau - coord->x) < 14) && ((taille_plateau - coord->y) > 5 && (taille_plateau - coord->y) < 14)){
            cpt += bonus + 1;
            if(((taille_plateau - coord->x) >= 8 && (taille_plateau - coord->x) <= 11) && ((taille_plateau - coord->y) >= 8 && (taille_plateau - coord->y) <= 11)){
                cpt += (bonus*2) + 1;
            }
        }
    }
    return(cpt);
}

/* Simule le tour des adversaires */
void simuler_tour(int nbj_max, int* joueur_en_jeux, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_liste* liste_piece, int cpt, int joueur, int nb_tour_joueur){
    int i,j,l,rotat,num,tampo;
    t_retour ret;
    t_coordonnee coord;
    t_matrice piece;


    for(i = 0; i < nbj_max-1; i++){ //On simule le tours des X autres joueurs
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
        nb_tour_joueur ++;
        if(joueur_en_jeux[joueur] == 1){ //Si ce joueur puet encore jouer
            ret = calcule_ia(nbj_max,joueur_en_jeux,taille_plateau,plateau,liste_piece,cpt-1,joueur,nb_tour_joueur); //On lance la simulation de ce joueur scpecifique
            //printf("On sort avec %i rota, %i num, %i coord.x, %i coord.y, resultat %i\n",rotat,num,coord.x,coord.y,ret.resultat);
            if(ret.numero_piece >= 0){ // Si le joueur nous a retourner une piece (cpt > 0)
                if(piece_dispo(ret.numero_piece, &liste_piece[joueur], &piece)){
                    if(ret.nb_rota==4)
                        ret.nb_rota=0;
                    for(l = 1; l <= ret.nb_rota; l++){
                        rotation(piece.mat,1);
  /*                      if(l == 4 || l == 8){
                            miroir_vertical(piece.mat);
                        }*/
                    }
                    if(placer_piece(taille_plateau,plateau,piece,ret.coord,joueur,3) == 0){
                        printf("ZUT TU A TROUVER UN BUG !!!\n");
                        printf("On a pas réussie a placer la piece dans le plateau\n");
                        exit(0);
                    }
                    oter_elt(&liste_piece[joueur]);
                }else{
                    printf("ZUT TU A TROUVER UN BUG !!!\n");
                    printf("La piece selectionner par l'ia n'est pas dans sa liste de piece\n");
                    exit(0);
                }
            }
        }
    }
}

/* Simule le tour de l'ia et nous renvoie les information necessaire pour poser la piece sur le plateau */
t_retour calcule_ia(int nbj_max, int* joueur_en_jeux, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_liste* liste_piece, int cpt, int joueur, int nb_tour_joueur){
     t_retour ret,ret2;
     t_coordonnee* tab_dispo = NULL,coord,coord2;
     t_matrice piece,piece2,piece_sans_rotation;
     t_case_m plateau2 [taille_plateau][taille_plateau],plateau_fictif[taille_plateau][taille_plateau];
     t_liste liste_piece2[nbj_max];
     int nb_case_disponible = 0,i,j,k,compte,nb_simulation_rotation,nb_simulation_piece,nb_simulation_autour,num_piece,nb_piece;
     int tab_piece[TAILLE_MAX];

    /* On initialise le retour de la fonction */
    ret.coord.x = 0;
    ret.coord.y = 0;
    ret.resultat = -3000;
    ret.nb_rota = 0;
    ret.numero_piece = -1;
    /* - - - - - - - - - - - - - - - - - - - - */

    if(cpt == 0){
        ret.resultat = calcul_1_score_placement(taille_plateau, plateau,joueur);
        free(tab_dispo);
        return(ret);
    }

    if(possible_de_jouer(taille_plateau, plateau, joueur, 5, &tab_dispo, &nb_case_disponible, &liste_piece[joueur]) == 0){ // Recupere la liste des cases disponibles
        ret.resultat = calcul_1_score_placement(taille_plateau, plateau,joueur);
        free(tab_dispo);
        return(ret);
    }

    en_queue(&liste_piece[joueur]);
    val_elem(&liste_piece[joueur],&piece);
    if(nb_tour_joueur <= 12){//Permet dans les 3 premier tours de ne pas prendre la piece 21
        precedent(&liste_piece[joueur]);
    }
    val_elem(&liste_piece[joueur],&piece);
    val_elem(&liste_piece[joueur],&piece_sans_rotation);

    i = 0;
    j = 0;
    compte = 0;
    nb_simulation_rotation = 0;
    nb_simulation_piece = 0;
    nb_simulation_autour = 0;


    for(k = 0; k < nb_case_disponible; k++){ //Pour toutes les cases possibiliter
        coord.x = tab_dispo[k].x;
        coord.y = tab_dispo[k].y;
        init_plateau_fictif (taille_plateau,plateau,plateau_fictif,joueur,&coord);

        while(!hors_liste(&liste_piece[joueur]) && nb_simulation_piece < 1){//on verifie pour chaque pieces

            while(compte < 4 && nb_simulation_rotation < 2){ //effectue tout les rotation de la piece
                compte ++;
                rotation(piece.mat,1);
  /*              if(compte % 4 == 0){
                    miroir_vertical(piece.mat);
                }*/
                while(i < TAILLE_MATRICE_PIECE && nb_simulation_autour < 2){ //dans un rayon de 2 case autour de la coordonner possible, on cherche a voir si la piece peut �tre poser
                    while(j < TAILLE_MATRICE_PIECE && nb_simulation_autour < 2){
                        coord2.x = coord.x+(i-2);
                        coord2.y = coord.y+(j-2);
                        if(!coordonner_invalide(coord.y ,coord2.x,taille_plateau)){
                            if(placer_piece(taille_plateau,plateau_fictif,piece,coord2,joueur,1) == 1){ //Si on a reussi a trouver un endoit ou mettre la piece
                                nb_simulation_autour ++; // On ne simule qu'une rotation de la piece si elle est valide
                                //printf("nb simul rotat %i\n",nb_simulation_rotation);
                                copie_plateau(taille_plateau,plateau,plateau2); //On recopie le plateau
                                placer_piece(taille_plateau,plateau2,piece,coord2,joueur,0); //On place la piece dans notre nouveau plateau
                                copie_liste(nbj_max,liste_piece,liste_piece2);
                                if(piece_dispo(piece.num, &liste_piece2[joueur], &piece2) == 0){
                                    exit(0);
                                }
                                oter_elt(&liste_piece2[joueur]);
                                simuler_tour(nbj_max,joueur_en_jeux,taille_plateau,plateau2,liste_piece2,cpt,joueur,nb_tour_joueur); //On simule le tours des autre joueur
                                ret2 = calcule_ia(nbj_max,joueur_en_jeux,taille_plateau,plateau2,liste_piece2,cpt-1,joueur,nb_tour_joueur); //On simule son prochain tour
                                ret2.resultat = ret2.resultat + calcul_2_score_placement(piece_sans_rotation.taille,&coord2,taille_plateau,nb_tour_joueur);
                                //printf("resultat2 %i, num2 %i, rota2 %i, coord2.x %i, coord2.y %i\n",ret2.resultat,ret2.numero_piece,ret2.nb_rota,ret2.coord.x,ret2.coord.y);
                                //printf("resultat %i, num %i, rota %i, coord.x %i, coord.y %i\n",ret.resultat,ret.numero_piece,ret.nb_rota,ret.coord.x,ret.coord.y);
                                if(ret2.resultat > ret.resultat){ //Si le resultat de la piece renvoyer est superieur a la precedente, on en recupere les donnees
                                    ret.resultat = ret2.resultat;
                                    ret.coord.x = coord2.x;
                                    ret.coord.y = coord2.y;
                                    ret.nb_rota = compte;
                                    ret.numero_piece = piece.num;
                                }
                                ajouter_piece(&liste_piece2[joueur],&piece_sans_rotation); //On replace la piece que l'on a supprimer plus tot pour les autres simulations
                                if(nb_tour_joueur > 12){
                                    if(ret.resultat > 60 - (nb_tour_joueur/nbj_max)){ //Si le resultat obtenue est superieur a 22 on coupe la recherche
                                        free(tab_dispo);
                                        return(ret);
                                    }
                                }else{
                                    if(ret.resultat > 75) { //Si le resultat obtenue est superieur a 22 on coupe la recherche
                                        free(tab_dispo);
                                        return(ret);
                                    }
                                }
                            }
                        }
                        j++;
                    }
                    j = 0;
                    i++;
                }
                if(nb_simulation_autour == 2){
                    nb_simulation_rotation ++;
                }
                nb_simulation_autour = 0;
                i = 0;
            }
            if(nb_simulation_rotation > 0){
                nb_simulation_piece ++; // On ne simule que 3 piece maximum par case
            }
            nb_simulation_rotation = 0;
            compte = 0;
            precedent(&liste_piece[joueur]);
            val_elem(&liste_piece[joueur],&piece);
            val_elem(&liste_piece[joueur],&piece_sans_rotation);
        }
        nb_simulation_piece = 0;
        en_queue(&liste_piece[joueur]);
        if(nb_tour_joueur <= 12){
            precedent(&liste_piece[joueur]);
        }
        val_elem(&liste_piece[joueur],&piece);
        val_elem(&liste_piece[joueur],&piece_sans_rotation);
    }
    free(tab_dispo);
    return(ret);

}

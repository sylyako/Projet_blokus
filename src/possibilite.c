#include "possibilite.h"
#include "init_plateau.h"
#include "ajouter_piece.h"

/**
 * \file possibilite.c
 * \brief Ensemble de fonctions relatives aux possibilitees du positionnement d'une ou de plusieurs piece avec un plateau donne.
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn int verif_posibiliter(int nb_tour, t_coordonnee** tab_dispo, int joueur, int* nb_dispo, t_liste* liste, int taille_plateau, t_case_m (*plateau)[taille_plateau])
 * \brief Verifie si les positions possibles sont REELEMENT des possibles en simulant une piece sur chaque posibilitee
 * \param nb_tour
 * \param tab_dispo Pointeur de pointeur de type t_coordonnee qui comporte toutes les coordonnees possibles a jouer.
 * \param joueur Entier désignant le numero du joueur en jeu
 * \param liste Pointeur de type t_liste contenant les pieces du joueur
 * \param taille_plateau Entier contenant la taille du plateau sur laquelle la partie est jouee.
 * \param plateau Pointeur contenant tout le plateau
 *
 * \fn int possible_de_jouer(int taille_plateau, t_case_m (*plateau)[taille_plateau], int joueur, int nb_tour, t_coordonnee** tab_dispo, int* nb_dispo, t_liste* liste)
 * \brief Verifie si il y a encore des coups possibles et si oui, retourne le tableau des possibilitees
 * \param taille_plateau Entier contenant la taille du plateau sur laquelle la partie est jouee.
 * \param plateau Pointeur contenant tout le plateau
 * \param joueur Entier désignant le numero du joueur en jeu
 * \param tab_dispo Pointeur de pointeur de type t_coordonnee qui comporte toutes les coordonnees possibles a jouer.
 * \param nb_dispo Pointeur vers un type entier désignant le nombre de pieces disponibles.
 * \param liste Pointeur de type t_liste contenant les pieces du joueur
 *
*/

/* Verifie si les positions possibles sont REELEMENT des position possible en simulant un posage des pieces sur chaque posibiliter*/
int verif_posibiliter(int nb_tour, t_coordonnee** tab_dispo, int joueur, int* nb_dispo, t_liste* liste, int taille_plateau, t_case (*plateau)[taille_plateau]){
    t_matrice piece;
    int i = 0, j = 0, k = 0, l, statut = 0, compte = 0;
    t_coordonnee coord, coord2;
    t_case plateau_copie [taille_plateau][taille_plateau];

    en_tete(liste);
    val_elem(liste,&piece);
    if(piece.num == 0){ //si l'on possedent encore le premier pentamino on pourra forcement jouer
        return (1);
    }else{
       while(k < *nb_dispo){ //Pour toutes les cases possibiliter
            coord.x = (*tab_dispo)[k].x;
            coord.y = (*tab_dispo)[k].y;
            init_plateau_fictif(taille_plateau,plateau,plateau_copie,joueur,&coord); // cree un plateau qui n'a comme possibiliter que celle que l'on cherche a tester

            while(!hors_liste(liste) && statut == 0){//on verifie pour chaque pieces
                while(compte < 8 && statut == 0){ //effectue tout les rotation de la piece
                    compte ++;
                    rotation(piece.mat,1);
                    if(compte % 4 == 0){
                        miroir_vertical(piece.mat);
                    }
                    while(i < TAILLE_MATRICE_PIECE && statut == 0){ //dans un rayon de 2 case autour de la coordonner possible, on cherche a voire si la piece peut Ítre poser
                        while(j < TAILLE_MATRICE_PIECE && statut == 0){
                            coord2.x = coord.x+(i-2);
                            coord2.y = coord.y+(j-2);
                            if(!coordonner_invalide(coord.y ,coord2.x,taille_plateau)){
                                if(placer_piece(taille_plateau,plateau_copie,piece,coord2,joueur,1) == 1){ //Si on a reussi a placer une piece sur la position possible
                                    statut = 1; //On passe a la case possible suivante
                                }
                            }
                            j++;
                        }
                        j = 0;
                        i++;
                    }
                    i = 0;
                }
                compte = 1;
                suivant(liste);
                val_elem(liste,&piece);
            }
            if (statut == 0){ //si l'on n'a pas reussi a placer de piece au niveau de la coordonner possible, on retire cette emplacement des possibiliter
                l = k;
                while(l < *nb_dispo){ //Decalage du tableau
                    (*tab_dispo)[l].x = (*tab_dispo)[l+1].x;
                    (*tab_dispo)[l].y = (*tab_dispo)[l+1].y;
                    l++;
                }

                -- *nb_dispo;

                if(joueur == rouge){
                    plateau[coord.y][coord.x].possible_r = 0;
                }else if(joueur == bleu){
                    plateau[coord.y][coord.x].possible_b = 0;
                }else if(joueur == vert){
                    plateau[coord.y][coord.x].possible_b = 0;
                }else{
                    plateau[coord.y][coord.x].possible_j = 0;
                }
                k--;
            }
            statut = 0;
            en_tete(liste);
            val_elem(liste,&piece);
            k++;
        }
    }
    return(1);
}

/* Verifie si il y a encore des coups possibles et retourne le tableau des possibiliter*/
int possible_de_jouer(int taille_plateau, t_case (*plateau)[taille_plateau], int joueur, int nb_tour, t_coordonnee** tab_dispo, int* nb_dispo, t_liste* liste){
    int i,j;
    en_tete(liste);
    /* Si on est au premier tour */
    if(nb_tour == 0){ //economise (taille_plateau)^2-5 verification sur le premier tour et donc on economise sur la partie un maximum de (taille_palteau)^2-(21*4)
        ++ *nb_dispo;
        *tab_dispo = realloc(*tab_dispo, *nb_dispo * sizeof(t_coordonnee));
        if (tab_dispo == NULL){//verifie si l'allocation/realocation a bien ete effectuer
            printf("Une erreur est survenue.\n");
            free(*tab_dispo);
            exit(0);
        }
        if(joueur == rouge){
            if (taille_plateau == 20){
                (*tab_dispo)[*nb_dispo-1].x = 0;
                (*tab_dispo)[*nb_dispo-1].y = 0;
            }else{          //plateau pour 2 joueur
                (*tab_dispo)[*nb_dispo-1].x = 4;
                (*tab_dispo)[*nb_dispo-1].y = 4;
            }
        }else if(joueur == bleu){
            if (taille_plateau == 20){
                (*tab_dispo)[*nb_dispo-1].x = taille_plateau-1;
                (*tab_dispo)[*nb_dispo-1].y = 0;
            }else{          //plateau pour 2 joueur
                (*tab_dispo)[*nb_dispo-1].x = 9;
                (*tab_dispo)[*nb_dispo-1].y = 9;
            }
        }else if(joueur == vert){
            (*tab_dispo)[*nb_dispo-1].x = 0;
            (*tab_dispo)[*nb_dispo-1].y = taille_plateau-1;
        }else{
            (*tab_dispo)[*nb_dispo-1].x = taille_plateau-1;
            (*tab_dispo)[*nb_dispo-1].y = taille_plateau-1;
        }
        return(1);
    }else{

        /* Parcour habituel */

        if(liste_vide(liste)){ //si notre liste est vide on ne peut plus jouer
            return(0);
        }

        if(joueur == rouge){ // faire la verification avant economise (taille_plateau)^2 verification par appel (On ne verifie pas la couleur du joueur a chaque case)
            for(i = 0; i < taille_plateau; i++){ // Recherche toutes les possibiliter de jeux pour le joueur et note les emplacements dans un tableau dynamique
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].possible_r == 1){
                        ++ *nb_dispo;
                        *tab_dispo = realloc(*tab_dispo,*nb_dispo * sizeof(t_coordonnee));
                        if (*tab_dispo == NULL){//verifie si l'allocation/realocation a bien ete effectuer
                            printf("Une erreur est survenue.\n");
                            free(*tab_dispo);
                            exit(0);
                        } //On conserve les coordonner des endroit possible
                        (*tab_dispo)[*nb_dispo-1].x = j;
                        (*tab_dispo)[*nb_dispo-1].y = i;
                    }
                }
            }
        }else if(joueur == bleu){
            for(i = 0; i < taille_plateau; i++){
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].possible_b == 1){
                        ++ *nb_dispo;
                        *tab_dispo = realloc(*tab_dispo, *nb_dispo * sizeof(t_coordonnee));
                        if (tab_dispo == NULL){
                            printf("Une erreur est survenue.\n");
                            free(*tab_dispo);
                            exit(0);
                        }
                        (*tab_dispo)[*nb_dispo-1].x = j;
                        (*tab_dispo)[*nb_dispo-1].y = i;
                    }
                }
            }
        }else if(joueur == vert){
            for(i = 0; i < taille_plateau; i++){
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].possible_v == 1){
                       ++ *nb_dispo;
                        *tab_dispo = realloc(*tab_dispo, *nb_dispo * sizeof(t_coordonnee));
                        if (tab_dispo == NULL){
                            printf("Une erreur est survenue.\n");
                            free(*tab_dispo);
                            exit(0);
                        }
                        (*tab_dispo)[*nb_dispo-1].x = j;
                        (*tab_dispo)[*nb_dispo-1].y = i;
                    }
                }
            }
        }else{
            for(i = 0; i < taille_plateau; i++){
                for(j = 0; j < taille_plateau; j++){
                    if(plateau[i][j].possible_j == 1){
                        ++ *nb_dispo;
                        *tab_dispo = realloc(*tab_dispo, *nb_dispo * sizeof(t_coordonnee));
                        if (tab_dispo == NULL){
                            printf("Une erreur est survenue.\n");
                            free(*tab_dispo);
                            exit(0);
                        }
                        (*tab_dispo)[*nb_dispo-1].x = j;
                        (*tab_dispo)[*nb_dispo-1].y = i;
                    }
                }
            }
        }

        verif_posibiliter(nb_tour,tab_dispo,joueur,nb_dispo,liste,taille_plateau,plateau); //Re-calcule nb_dispo
        if(*nb_dispo > 0){
            return (1);
        }else{
            return(0);
        }
    }
}

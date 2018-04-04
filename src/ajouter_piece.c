#include "ajouter_piece.h"

void placer_posibiliter(int taille_plateau, t_case (*plateau)[taille_plateau], int y, int x, int joueur){
    if(coordonner_invalide(y+1,x,taille_plateau) || plateau[y+1][x].couleur != joueur){
        if(coordonner_invalide(y,x+1,taille_plateau) || plateau[y][x+1].couleur != joueur){
            if(coordonner_invalide(y-1,x,taille_plateau) || plateau[y-1][x].couleur != joueur){
                if(coordonner_invalide(y,x-1,taille_plateau) || plateau[y][x-1].couleur != joueur){
                    if(joueur == rouge){
                        plateau[y][x].possible_r = 1;
                    }else if(joueur == bleu){
                        plateau[y][x].possible_b = 1;
                    }else if(joueur == vert){
                        plateau[y][x].possible_v = 1;
                    }else{
                        plateau[y][x].possible_j = 1;
                    }
                }
            }
        }
    }
}

/* Veerifie si l'on peut placer la piece au coordonner cible puis la place, permet aussi de seulement verifier si l'on peut placer un piece au coordonner cible avec mode = 1 */
int placer_piece(int taille_plateau, t_case (*plateau)[taille_plateau], t_matrice matri, t_coordonnee coord, int joueur, int mode){
    int i,j,indice = -1;
    int cpt = 0;
    t_coordonnee coord2;

    /* Verifie si la ou l'on veut posser la piece est bien une case definie comme possible pour le joueur */
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){//Rappel (i = y et j = x)
            if(matri.mat[i][j] == 1){
                coord2.x = coord.x+(j-2);
                coord2.y = coord.y+(i-2);
                if(coordonner_invalide(coord2.x,coord2.y,taille_plateau)){ //Si un des pentamino de la piece que l'on veut placer est hors plateau
                    if(mode == 3){
                        printf("On est hors plateau %i %i\n",coord2.x,coord2.y);
                        afficher_matrice(matri);
                    }
                    return(0);
                }else if(plateau[coord2.y][coord2.x].couleur != libre){ //Si un des pentamino de la piece que l'on veut placer entre en conflit avec une case d'un joueur
                    if(mode == 3){
                        printf("Conflit de couleur\n");
                    }
                    return(0);
                }else{ //si la case ou l'on veut poser le pentamino est disponible
                    /* On verifie que l'on ne cherche pas a poser a coter d'une de ces propre pieces */
                    if(coordonner_invalide(coord2.y-1,coord2.x,taille_plateau) || plateau[coord2.y-1][coord2.x].couleur != joueur){
                        if(coordonner_invalide(coord2.y+1,coord2.x,taille_plateau) || plateau[coord2.y+1][coord2.x].couleur != joueur){
                            if(coordonner_invalide(coord2.y,coord2.x-1,taille_plateau) || plateau[coord2.y][coord2.x-1].couleur != joueur){
                                if(coordonner_invalide(coord2.y,coord2.x+1,taille_plateau) || plateau[coord2.y][coord2.x+1].couleur != joueur){
                                    if(joueur == rouge && plateau[coord2.y][coord2.x].possible_r == 1){ //Si le pentamino que l'on veut poser est sur une case possible (possible_r/b/v/j)
                                        cpt ++;
                                    }else if (joueur == bleu && plateau[coord2.y][coord2.x].possible_b == 1){
                                        cpt ++;
                                    }else if (joueur == vert && plateau[coord2.y][coord2.x].possible_v == 1){
                                        cpt ++;
                                    }else if (joueur == jaune && plateau[coord2.y][coord2.x].possible_j == 1){
                                        cpt ++;
                                    }
                                }else{
                                    if(mode == 3){
                                        printf("je ne sait pas comment decrire ... 1 \n");
                                    }
                                    return(0);
                                }
                            }else{
                                if(mode == 3){
                                    printf("je ne sait pas comment decrire ... 2 \n");
                                }
                                return(0);
                            }
                        }else{
                            if(mode == 3){
                                 printf("je ne sait pas comment decrire ... 3 \n");
                            }
                            return(0);
                        }
                    }else{
                        if(mode == 3){
                            printf("je ne sait pas comment decrire ... 4 \n");
                        }
                        return(0);
                    }
                }
            }
        }
    }
    if (cpt > 0){ //Si au moin un des pentamino de la piece que l'on cherhce poser est sur une case possible (possible_r/b/v/j)
        if(mode != 1){ //mode == 1 -> Verifie les possibiliter donc pas besoin de placer la piece
            /* Parcoure de la matrice pour y place la piece */
            for(i = 0; i < 5; i++){
                for(j = 0; j < 5; j++){
                    if(matri.mat[i][j] == 1){ //si on trouve une case dans la matrice de la piece

                        coord2.x = coord.x+(j-2);
                        coord2.y = coord.y+(i-2);

                        plateau[coord2.y][coord2.x].couleur = joueur; //On place les pentamino de la pieces
                        plateau[coord2.y][coord2.x].possible_r = 0;
                        plateau[coord2.y][coord2.x].possible_b = 0;
                        plateau[coord2.y][coord2.x].possible_v = 0;
                        plateau[coord2.y][coord2.x].possible_j = 0;

                        /* On retire les possibiliter qui collent la piece */
                        if(joueur == rouge){
                            if(!coordonner_invalide(coord2.y+1,coord2.x,taille_plateau)){
                                plateau[coord2.y+1][coord2.x].possible_r = 0;
                            }
                            if(!coordonner_invalide(coord2.y-1,coord2.x,taille_plateau)){
                                plateau[coord2.y-1][coord2.x].possible_r = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x+1,taille_plateau)){
                                plateau[coord2.y][coord2.x+1].possible_r = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x-1,taille_plateau)){
                                plateau[coord2.y][coord2.x-1].possible_r = 0;
                            }
                        }else if(joueur == bleu){
                            if(!coordonner_invalide(coord2.y+1,coord2.x,taille_plateau)){
                                plateau[coord2.y+1][coord2.x].possible_b = 0;
                            }
                            if(!coordonner_invalide(coord2.y-1,coord2.x,taille_plateau)){
                                plateau[coord2.y-1][coord2.x].possible_b = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x+1,taille_plateau)){
                                plateau[coord2.y][coord2.x+1].possible_b = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x-1,taille_plateau)){
                                plateau[coord2.y][coord2.x-1].possible_b = 0;
                            }
                        }else if(joueur == vert){
                            if(!coordonner_invalide(coord2.y+1,coord2.x,taille_plateau)){
                                plateau[coord2.y+1][coord2.x].possible_v = 0;
                            }
                            if(!coordonner_invalide(coord2.y-1,coord2.x,taille_plateau)){
                                plateau[coord2.y-1][coord2.x].possible_v = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x+1,taille_plateau)){
                                plateau[coord2.y][coord2.x+1].possible_v = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x-1,taille_plateau)){
                                plateau[coord2.y][coord2.x-1].possible_v = 0;
                            }
                        }else{
                            if(!coordonner_invalide(coord2.y+1,coord2.x,taille_plateau)){
                                plateau[coord2.y+1][coord2.x].possible_j = 0;
                            }
                            if(!coordonner_invalide(coord2.y-1,coord2.x,taille_plateau)){
                                plateau[coord2.y-1][coord2.x].possible_j = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x+1,taille_plateau)){
                                plateau[coord2.y][coord2.x+1].possible_j = 0;
                            }
                            if(!coordonner_invalide(coord2.y,coord2.x-1,taille_plateau)){
                                plateau[coord2.y][coord2.x-1].possible_j = 0;
                            }
                        }
                    }
                }
            }

            /* place les posibiliter qu'a engendre la piece */
            for(i = 0; i < 5; i++){
                for(j = 0; j < 5; j++){
                    if(matri.mat[i][j] == 1){

                        coord2.x = coord.x+(j-2);
                        coord2.y = coord.y+(i-2);

                        if(!coordonner_invalide(coord2.y+1,coord2.x+1,taille_plateau) && plateau[coord2.y+1][coord2.x+1].couleur == libre){ //si le coin inferieur droit est libre
                            placer_posibiliter(taille_plateau,plateau,coord2.y+1,coord2.x+1,joueur);
                        }
                        if(!coordonner_invalide(coord2.y+1,coord2.x-1,taille_plateau) && plateau[coord2.y+1][coord2.x-1].couleur == libre){//si le coin inferieur gauche est libre
                            placer_posibiliter(taille_plateau,plateau,coord2.y+1,coord2.x-1,joueur);
                        }
                        if(!coordonner_invalide(coord2.y-1,coord2.x-1,taille_plateau) && plateau[coord2.y-1][coord2.x-1].couleur == libre){//si le coin superieur gauche est libre
                            placer_posibiliter(taille_plateau,plateau,coord2.y-1,coord2.x-1,joueur);
                        }
                        if(!coordonner_invalide(coord2.y-1,coord2.x+1,taille_plateau) && plateau[coord2.y-1][coord2.x+1].couleur == libre){//si le coin superieur droit est libre
                            placer_posibiliter(taille_plateau,plateau,coord2.y-1,coord2.x+1,joueur);
                        }
                    }
                }
            }
        }
        return(1);
    }else{
        if(mode == 3){
            printf("Pas de possibiliter \n");
        }
        return(0);
    }
}

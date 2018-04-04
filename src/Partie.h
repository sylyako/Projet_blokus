#ifndef PARTIE_H
#define PARTIE_H
#include "structures.h"
#include "liste.h"
#include "matrice.h"
#include "init_plateau.h"
#include "afficher.h"

#include "ajouter_piece.h"
#include "possibilite.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "IA.h"

typedef struct {
    
    int joueur_hum ;
    int joueur_ia ;
    
} param_joueur;



void afficher_piece_dispo(int nb_piece, t_liste* liste);
int piece_dispo(int num_piece_choisi, t_liste* liste, t_matrice* piece);
void calcule_score(int nbj_max,int* score,int joueur, t_liste* liste);

/* Fonction de jeux */
int jeux(int nbj, int nbj_max, int nb_tour_joueur, int * score, int * joueur_en_jeux, int taille_plateau, t_case_m (*plateau)[taille_plateau],t_liste* liste_piece, SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police, int opt_charge);

int commencer_partie(int nbj_max, int nb_IA, SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police);


#endif

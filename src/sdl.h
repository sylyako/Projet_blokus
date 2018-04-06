#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "dessine.h"
#include "SDL2/SDL2_rotozoom.h"
#include "Partie.h"
#include "structures.h"
#include "liste.h"
#include "matrice.h"
#include "init_plateau.h"
#include "afficher.h"
#include "ajouter_piece.h"
#include "IA.h"

//  gcc -I/usr/include/SDL2 -I/usr/include/SDL2_ttf -I/usr/include/SDL_image -I/usr/include/SDL_gfx sdl.c dessine.c  -o  app -L/usr/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx

typedef struct {
    SDL_Surface * image;
    SDL_Texture * texture;
    SDL_Rect position;
    int x_init;
    int y_init;
    int dispo;
    
} t_piece;

typedef struct {
    int posx;
    int posy;
    int w;
    int h;
}t_case;

typedef struct {
    int numero_piece;
    int nbr_maj;
    int nbr_rotation;
} t_piece_bougee;


typedef struct {
    
    int joueur_hum ;
    int joueur_ia ;
    
} t_param_joueur;

// ##############################

void quit(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police);



int numero_piece(t_piece tab[21], int x, int y);

int wrap_num(t_piece tab[21], int x, int y);

int hors_jeu(int x, int y);

void replace(SDL_Renderer * surface,t_piece * tabjoueur[4], t_piece  tab[21],  int x, int y, SDL_Window * fenetre, TTF_Font * police,int num_piece, int nb_joueurs, int tour_joueur,t_case back_cases[20][20]);

void positionne_piece(t_piece tab[21], int x, int y,SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police, int nb_joueurs, t_piece * tabjoueur[4], t_piece_bougee * piece_bougee, int tour_joueur, t_case back_cases[20][20]);

void recupere_coord(t_case back_cases[20][20],float x, float y, int*i_res, int *j_res);

void envoi_position(t_piece tab[21], t_case back_cases[20][20], int nb_joueurs, int *i, int *j, t_piece_bougee * piece_bougee);

void init_tabpiece(SDL_Renderer * surface, t_piece tab[21], SDL_Texture * thetexture, char ext[10]);

void init_pieces(t_piece tab[21], SDL_Renderer * surface, int opt, int nb_joueurs);

int verif_piece(t_piece tab[21]);

int press_valider(t_piece tab[21], int x, int y,t_case back_cases[20][20],int nb_joueurs, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_matrice matri, t_coordonnee coord, int joueur, int mode, t_piece_bougee piece_bougee,t_liste* piece);

void attend(void);

int press_tourner(int x, int y);

void transformSurfaceY(SDL_Surface * src, SDL_Surface * dst, int cx, int cy, int isin, int icos, int flipx, int flipy);

void tourner_piece_sdl(SDL_Window * fenetre, SDL_Renderer * surface, t_piece * tabjoueur[4], int tour_joueur,TTF_Font * police, int nb_joueurs, t_piece tabpiece[21], t_piece_bougee * piece_bougee);

void positionne_piece_ia(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs,t_piece * tabjoueur[4],t_piece tab[21], int tour_joueur, t_retour ret, t_case back_cases[20][20]);

void mis_a_jour_piece(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs,t_piece * tabjoueur[4],t_piece tabpiece[21], int tour_joueur);

int mis_a_jour(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs, int tour_joueur);

int press_sauvegarder(int x, int y,t_case back_cases[20][20],int nb_joueurs, t_piece * tabjoueur[nb_joueurs], int nb_IA, int tab_rota[nb_joueurs][21],int nb_tour_joueur, int* score, int* joueur_en_jeux, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_liste* liste_piece);

int press_charger(void);

int press_passerTour(int x, int y, int taille_grille);

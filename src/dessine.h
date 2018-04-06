#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


void dessine_jeu_boutons_back(SDL_Renderer * surface, TTF_Font * police, int mode);
void dessine_jeu_boutons(SDL_Renderer * surface, TTF_Font * police);
void dessine_joueur(SDL_Renderer * surface, TTF_Font * police, int nb_joueurs);
void dessine_tour_joueur(SDL_Renderer * surface, TTF_Font * police, int tour_joueur);
void dessine_banque(SDL_Renderer * surface, TTF_Font * police);

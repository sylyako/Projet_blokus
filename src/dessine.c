#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/**
 * \file dessine.c
 * \brief Ensemble de fonctions qui servent à la creation d'elements de l'interface graphique, et qui la copie sur un renderer
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void dessine_jeu_boutons_back(SDL_Renderer * surface, TTF_Font * police)
 * \brief Fonction qui créer et place les boutons sauvegarder et accueil
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 *
 * \fn void dessine_jeu_boutons(SDL_Renderer * surface, TTF_Font * police)
 * \brief Fonction qui créer et place les boutons de jeu (tourner piece, valider piece...)
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 *
 * \fn void dessine_joueur(SDL_Renderer * surface, TTF_Font * police, int nb_joueurs)
 * \brief Fonction qui créer et place les cadres d'identification des joueurs autour du plateau
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \param nb_joueurs Variable de type int contenant le nombre de joueur dans la partie en cours
 *
 * \fnv oid dessine_tour_joueur(SDL_Renderer * surface, TTF_Font * police, int tour_joueur){
 * \brief Fonction qui créer et place le cadre d'identification du joueur à qui c'est le tour au dessus du plateau
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \param tour_joueur Variable de type int contenant le numero du joueur à qui c'est le tour de jouer
 *
 * \fn void dessine_banque(SDL_Renderer * surface, TTF_Font * police){
 * \brief Fonction qui créer et place le cadre délimitant la banque de piece ainsi que l'encadré de titre
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 *
*/





SDL_Color white={255,255,255, 255};
SDL_Color black ={255,255,255};


void dessine_jeu_boutons_back(SDL_Renderer * surface, TTF_Font * police, int mode){
     int const hf = 680;
    SDL_SetRenderDrawColor(surface,0, 0, 0, 255);
    
    if(mode==1){
        SDL_Rect bouton_sauv= {1,hf - 51,140,50};
        SDL_RenderFillRect(surface,&bouton_sauv);
        
        SDL_Surface* sauv = TTF_RenderText_Solid(police, "Sauvegarder",white);
        SDL_Texture* Message_sauv =SDL_CreateTextureFromSurface(surface,sauv);
        SDL_RenderCopy(surface, Message_sauv, NULL,&bouton_sauv);
    }
    SDL_Surface* accueil = IMG_Load("img/accueil.png");
    SDL_Texture* accueil_t = SDL_CreateTextureFromSurface(surface,accueil);
    SDL_Rect pos_accueil ={0,0,50,50};
    SDL_RenderCopy(surface, accueil_t, NULL,&pos_accueil);
}



void dessine_jeu_boutons(SDL_Renderer * surface, TTF_Font * police){
    int taille_grille=400;
  //  int const hf = 680;
    int const wf = 940;
    
    SDL_SetRenderDrawColor(surface,193, 193, 193, 255);
    
    SDL_Rect bouton_gauche_1= {(((wf-taille_grille)/2)-180)/2,185,180,50};
    SDL_RenderFillRect(surface,&bouton_gauche_1);
    
    SDL_Rect bouton_gauche_2= {(((wf-taille_grille)/2)-180)/2,270,180,50};
    SDL_RenderFillRect(surface,&bouton_gauche_2);
    
    SDL_Rect bouton_gauche_3_enc= {(((wf-taille_grille)/2)-180)/2,355,180,50};
    SDL_RenderDrawRect(surface,&bouton_gauche_3_enc);
    
    SDL_Rect bouton_gauche_4= {(((wf-taille_grille)/2)-180)/2,440,180,50};
    SDL_RenderFillRect(surface,&bouton_gauche_4);
    
    SDL_SetRenderDrawColor(surface,76, 74, 73, 255);
    
    SDL_Rect bouton_gauche_1_enc= {(((wf-taille_grille)/2)-180)/2,185,180,50};
    SDL_RenderDrawRect(surface,&bouton_gauche_1_enc);
    
    SDL_Rect bouton_gauche_2_enc= {(((wf-taille_grille)/2)-180)/2,270,180,50};
    SDL_RenderDrawRect(surface,&bouton_gauche_2_enc);
    
    SDL_Rect bouton_gauche_4_enc= {(((wf-taille_grille)/2)-180)/2,440,180,50};
    SDL_RenderDrawRect(surface,&bouton_gauche_4_enc);
    
    SDL_SetRenderDrawColor(surface,86, 180, 99, 255);
    
    SDL_Rect bouton_gauche_3= {(((wf-taille_grille)/2)-180)/2,355,180,50};
    SDL_RenderFillRect(surface,&bouton_gauche_3);
    
   // SDL_Color white={255,255,255, 255};
    
    SDL_Surface* bouton_gauche_1_t = TTF_RenderText_Solid(police, "Selectionner une piece",white);
    SDL_Texture* Message_1 =SDL_CreateTextureFromSurface(surface, bouton_gauche_1_t);
    SDL_RenderCopy(surface, Message_1, NULL,&bouton_gauche_1);
    
    SDL_Surface* bouton_gauche_2_t = TTF_RenderText_Solid(police, "Tourner la Piece",white);
    SDL_Texture* Message_2 =SDL_CreateTextureFromSurface(surface, bouton_gauche_2_t);
    SDL_RenderCopy(surface, Message_2, NULL,&bouton_gauche_2);
    
    SDL_Surface* bouton_gauche_3_t = TTF_RenderText_Solid(police, "Valider la Position",white);
    SDL_Texture* Message_3 =SDL_CreateTextureFromSurface(surface, bouton_gauche_3_t);
    SDL_RenderCopy(surface, Message_3, NULL,&bouton_gauche_3);
    
    SDL_Surface* bouton_gauche_4_t = TTF_RenderText_Solid(police, "Passer son Tour",white);
    SDL_Texture* Message_4 =SDL_CreateTextureFromSurface(surface, bouton_gauche_4_t);
    SDL_RenderCopy(surface, Message_4, NULL,&bouton_gauche_4);
    
}




void dessine_joueur(SDL_Renderer * surface, TTF_Font * police, int nb_joueurs){
    int taille_grille=400;
    int const hf = 680;
    int const wf = 940;
    int pos_joueur2=0;
    
    if(nb_joueurs==2)
        pos_joueur2=((hf - taille_grille)/2 )-90+500;
    else
        pos_joueur2=((hf - taille_grille)/2 )-90;

    SDL_SetRenderDrawColor(surface,38,102,101, 255);
    
    SDL_Rect joueur_1= {((wf-taille_grille)/2)- 50, ((hf - taille_grille)/2 )-90, 50,50};  // J en haut à gauche
    SDL_RenderFillRect(surface,&joueur_1);
    
    
    SDL_SetRenderDrawColor(surface,225,138,7, 255);
    
    SDL_Rect joueur_2= {((wf-taille_grille)/2)- 50, ((hf - taille_grille)/2 )-90 + 500, 50,50};  // J en bas à gauche
    if(nb_joueurs==4)
        SDL_RenderFillRect(surface,&joueur_2);
    

    SDL_SetRenderDrawColor(surface,154,25,25,255);
    
    SDL_Rect joueur_3= {((wf-taille_grille)/2)- 50 + 380, pos_joueur2 , 50,50};
    SDL_RenderFillRect(surface,&joueur_3);

    SDL_SetRenderDrawColor(surface,37,102,38, 255);
    
    SDL_Rect joueur_4= {((wf-taille_grille)/2)- 50 + 380, ((hf - taille_grille)/2 )-90 +500, 50,50};
    if(nb_joueurs==4)
        SDL_RenderFillRect(surface,&joueur_4);
    
    
    
    SDL_SetRenderDrawColor(surface,218, 149, 76, 255);
    
    
    SDL_Surface* joueur_1_t = TTF_RenderText_Solid(police, "J1",white);
    SDL_Texture* Message_J1 =SDL_CreateTextureFromSurface(surface,joueur_1_t);
    SDL_RenderCopy(surface, Message_J1, NULL,&joueur_1);
    
    SDL_Surface* joueur_2_t = TTF_RenderText_Solid(police, "J4",white);
    SDL_Texture* Message_J2 =SDL_CreateTextureFromSurface(surface,joueur_2_t);
    if(nb_joueurs==4)
        SDL_RenderCopy(surface, Message_J2, NULL,&joueur_2);
    
    
    SDL_Surface* joueur_3_t = TTF_RenderText_Solid(police, "J2",white);
    SDL_Texture* Message_J3 =SDL_CreateTextureFromSurface(surface,joueur_3_t);
    SDL_RenderCopy(surface, Message_J3, NULL,&joueur_3);
        
    SDL_Surface* joueur_4_t = TTF_RenderText_Solid(police, "J3",white);
    SDL_Texture* Message_J4 =SDL_CreateTextureFromSurface(surface,joueur_4_t);
    if(nb_joueurs==4)
        SDL_RenderCopy(surface, Message_J4, NULL,&joueur_4);
    
    
    SDL_SetRenderDrawColor(surface,0,0,0, 255);
    SDL_Rect joueur_courant= {((wf-taille_grille)/2)+75, 20, 100,50};  // J en haut à gauche
    SDL_RenderFillRect(surface,&joueur_courant);
    SDL_Surface* joueur_txt_courant = TTF_RenderText_Solid(police, "Tour de :", black);
    SDL_Texture* Message_JC =SDL_CreateTextureFromSurface(surface,joueur_txt_courant);
    SDL_RenderCopy(surface, Message_JC, NULL,&joueur_courant);
    
    if(nb_joueurs==2){
        SDL_SetRenderDrawColor(surface,154, 193, 193, 255);
        SDL_Rect emplacement1= {373,247,15,15};
        SDL_RenderFillRect(surface,&emplacement1);
        SDL_SetRenderDrawColor(surface,154,25,25,10);
        SDL_Rect emplacement2= {523,397,15,15};
        SDL_RenderFillRect(surface,&emplacement2);
    }
    

}

void dessine_tour_joueur(SDL_Renderer * surface, TTF_Font * police, int tour_joueur){
    int taille_grille=400;
    //int const hf = 680;
    int const wf = 940;
    
    
    if ( tour_joueur == 0) {
        SDL_SetRenderDrawColor(surface,38,102,101, 255);
        SDL_Rect joueur_1_tour= {((wf-taille_grille)/2) + 75 + 70+50, 20, 50,50};  // J en haut à gauche
        SDL_RenderFillRect(surface,&joueur_1_tour);
        SDL_Surface* joueur_1_t_tour = TTF_RenderText_Solid(police, "J1",white);
        SDL_Texture* Message_J1_tour =SDL_CreateTextureFromSurface(surface,joueur_1_t_tour);
        SDL_RenderCopy(surface, Message_J1_tour, NULL,&joueur_1_tour);
    }
    
    
    else if ( tour_joueur ==1) {
        SDL_SetRenderDrawColor(surface,154,25,25,255);
        SDL_Rect joueur_2_tour= {((wf-taille_grille)/2) + 75 + 70+50, 20, 50,50};  // J en bas à gauche
        SDL_RenderFillRect(surface,&joueur_2_tour);
        
        SDL_Surface* joueur_3_t_tour = TTF_RenderText_Solid(police, "J2",white);
        SDL_Texture* Message_J3_tour =SDL_CreateTextureFromSurface(surface,joueur_3_t_tour);
        SDL_RenderCopy(surface, Message_J3_tour, NULL,&joueur_2_tour);
    }
    
    
    else if ( tour_joueur ==2) {
        SDL_SetRenderDrawColor(surface,37,102,38, 255);
        SDL_Rect joueur_3_tour= {((wf-taille_grille)/2)+ 75 + 70+50, 20, 50,50};
        SDL_RenderFillRect(surface,&joueur_3_tour);
        
        SDL_Surface* joueur_4_t_tour = TTF_RenderText_Solid(police, "J3",white);
        SDL_Texture* Message_J4_tour =SDL_CreateTextureFromSurface(surface,joueur_4_t_tour);
        SDL_RenderCopy(surface, Message_J4_tour, NULL,&joueur_3_tour);
    }
    
    
    else {
        SDL_SetRenderDrawColor(surface,225,138,7, 255);
        SDL_Rect joueur_4_tour= {((wf-taille_grille)/2)+ 75 + 70+50, 20, 50,50};
        SDL_RenderFillRect(surface,&joueur_4_tour);
        
        SDL_Surface* joueur_2_t_tour = TTF_RenderText_Solid(police, "J4",white);
        SDL_Texture* Message_J2_tour =SDL_CreateTextureFromSurface(surface,joueur_2_t_tour);
        SDL_RenderCopy(surface, Message_J2_tour, NULL,&joueur_4_tour);
    }
    
    
}


void dessine_banque(SDL_Renderer * surface, TTF_Font * police){
    int taille_grille=400;
   // int const hf = 680;
    int const wf = 940;
    SDL_SetRenderDrawColor(surface,193, 193, 193, 255);
    
    SDL_Rect bouton_droite_1= {wf - ((((wf-taille_grille)/2)-180)/2) - 200,2,180,50};
    SDL_RenderFillRect(surface,&bouton_droite_1);
    
    SDL_Rect bouton_droite_2= {wf - ((((wf-taille_grille)/2)-180)/2) - 210,50 +2,250,612};
    SDL_RenderFillRect(surface,&bouton_droite_2);
    
    SDL_SetRenderDrawColor(surface,123,0,0, 255);
    
    SDL_Rect joueur_piece= {wf-55 , 2, 50,50};
    SDL_RenderFillRect(surface,&joueur_piece);
    
    SDL_Surface* piece = TTF_RenderText_Solid(police, "Banque de Pieces",white);
    SDL_Texture* Message_piece =SDL_CreateTextureFromSurface(surface,piece);
    SDL_RenderCopy(surface, Message_piece, NULL,&bouton_droite_1);
}




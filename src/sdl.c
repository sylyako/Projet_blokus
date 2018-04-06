#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "dessine.h"
#include "possibilite.h"
#include "SDL2/SDL2_rotozoom.h"
#include "Partie.h"
#include "sdl.h"
#include "IA.h"
#include "structures.h"
#include "liste.h"
#include "matrice.h"
#include "init_plateau.h"
#include "afficher.h"

#include "ajouter_piece.h"



/**
 * \file sdl.c
 * \brief Ensemble de fonctions servants à l'interface graphique.
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void quit(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police)
 * \brief Fonction qui detruit les éléments de SDL crées.
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 *
 * \fn int numero_piece(t_piece tab[21], int x, int y)
 * \brief Fonction qui permet de récuperer le numero de pièce qui recouvre la position x y.
 * \param tab[21] Variable de type t_piece contenant toutes les pieces d'un joueur
 * \param x Variable de type int représentant une position en abscisse
 * \param y Variable de type int représentant une position en ordonnée
 * \return le numero de la pièce s'il y en a une. Sinon -1 (echec)
 *
 * \fn int wrap_num(t_piece tab[21], int x, int y)
 * \brief Fonction wrapper vers numero_piece.
 * \param tab[21] Variable de type t_piece contenant toutes les pieces d'un joueur
 * \param x Variable de type int représentant une position en abscisse
 * \param y Variable de type int représentant une position en ordonnée
 * \return le numero de la pièce s'il y en a une. Sinon -1 (echec)
 *
 * \fn int hors_jeu(int x, int y)
 * \brief Fonction qui determine si la position x,y est hors du plateau de jeu.
 * \param x Variable de type int représentant une position en abscisse
 * \param y Variable de type int représentant une position en ordonnée
 * \return 1 si la position est dans le plateau, 0 sinon.
 *
 * \fn void replace(SDL_Renderer * surface,t_piece * tabjoueur[4], t_piece  tab[21],  int x, int y, SDL_Window * fenetre, TTF_Font * police,int num_piece, int nb_joueurs, int tour_joueur, t_case back_cases[20][20])
 * \brief Fonction qui replace une piece sur la grille proprement, de manière à ce que le coin haut gauche de l'image soit collé au coin haut gauche de la case où il se trouve.
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param tabjoueur[4] Tableau de pointeur de type t_piece pointant vers chaque tableau de piece des 4 joueurs.
 * \param tab[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param x Variable de type int représentant une position en abscisse
 * \param y Variable de type int représentant une position en ordonnée
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param police SDL - Pointeur de type TTF_Font
 * \param num_piece Variable de type int correspondant au numero de la piece à replacer
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param tour_joueur Variable de type int contenant le numero du joueur en train de jouer
 * \param back_cases Matrice 20x20 de type t_case contenant toutes les informations (void doc de t_case) de toutes les cases.
 *
 * \fn void positionne_piece(t_piece tab[21], int x, int y,SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police, int nb_joueurs, t_piece * tabjoueur[4],t_piece_bougee * piece_bougee, int tour_joueur, t_case back_cases[20][20])
 * \brief Fonction qui permet au joueur de bouger/positionner une piece.
 * \param tab[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param x Variable de type int représentant une position en abscisse
 * \param y Variable de type int représentant une position en ordonnée
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param police SDL - Pointeur de type TTF_Font
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param tabjoueur[4] Tableau de pointeur de type t_piece pointant vers chaque tableau de piece des 4 joueurs.
 * \param piece_bougee Variable de type t_piece_bougee contenant toutes les informations de la derniere piece bougee ou de celle qui est en train d'etre bougée.
 * \param tour_joueur Variable de type int contenant le numero du joueur en train de jouer
 * \param back_cases Matrice 20x20 de type t_case contenant toutes les informations (void doc de t_case) de toutes les cases.
 *
 * \fn void recupere_coord(t_case back_cases[20][20],float x, float y, int*i_res, int *j_res)
 * \brief Fonction qui permet de récuperer les coordonnees de la case qui recouvre la position x y et enregistre ces coordonnées dans i_res et j_res.
 * \param back_cases Matrice 20x20 de type t_case contenant toutes les informations (void doc de t_case) de toutes les cases.
 * \param x Variable de type float représentant une position en abscisse
 * \param y Variable de type float représentant une position en ordonnée
 * \param i_res Pointeur de type int qui recupere la coordonnée de ligne de la case trouvée
 * \param j_res Pointeur de type int qui recupere la coordonnée de colonne de la case trouvée
 *
 * \fn void envoi_position(t_piece tab[21], t_case back_cases[20][20], int nb_joueurs, int *i, int *j, t_piece_bougee * piece_bougee)
 * \brief Fonction qui recupère les coordonnées de la case, dans i et j, qui représente le milieu de la piece.
 * \param tab[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param back_cases Matrice 20x20 de type t_case contenant toutes les informations (void doc de t_case) de toutes les cases.
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param i Pointeur de type int qui recupere la coordonnée de ligne de la case trouvée
 * \param j Pointeur de type int qui recupere la coordonnée de colonne de la case trouvée
 * \param piece_bougee Pointeur de type t_piece_bougee contenant toutes les informations de la derniere piece bougee ou de celle qui est en train d'etre bougée.
 *
 * \fn void init_tabpiece(SDL_Renderer * surface, t_piece tab[21], SDL_Texture * thetexture, char ext[10])
 * \brief Fonction qui importe l'image correspondante à la piece et créer sa texture, et ceci 21 fois
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param tab[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param thetexture SDL - Pointeur de type SDL_Texture
 * \param ext[10] Tableau de caractere contenant l'extension correspondante au joueur.
 *
 * \fn void init_pieces(t_piece tab[21], SDL_Renderer * surface, int opt, int nb_joueurs)
 * \brief Fonction qui initialise la position et les dimensions de toutes les pieces dans tab
 * \param tab[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 *
 * \fn int press_valider(t_piece tab[21], int x, int y,t_case back_cases[20][20],int nb_joueurs, int taille_plateau, t_plateau plateau[taille_plateau][taille_plateau], t_matrice matri, t_coordonnee coord, int joueur,int mode, t_piece_bougee piece_bougee )
 * \brief Fonction qui verifie que l'utilisateur a cliqué sur le bouton valider, et pose definitivement la piece à sa place si toutes les regles sont respectées
 * \param tab[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param x Variable de type float représentant une position en abscisse
 * \param y Variable de type float représentant une position en ordonnée
 * \param back_cases Matrice 20x20 de type t_case contenant toutes les informations (void doc de t_case) de toutes les cases.
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param taille_plateau Variable de type int contenant la taille du plateau de jeu.
 * \param plateau Matrice de type t_plateau contenant le plateau de jeu
 * \param matri Variable de type t_matri contenant la matrice de la piece que l'utilisateur souhaite valider
 * \param coord Variable detype t_coordonnee contenant les coordonnees de la piece que l'utilisateur souhaite valider
 * \param joueur Variable de type int contenant le numero du joueur
 * \param piece_bougee Pointeur de type t_piece_bougee contenant toutes les informations de la derniere piece bougee ou de celle qui est en train d'etre bougée.
 *
 * \fn int press_tourner(int x, int y)
 * \brief Fonction qui determine si la position x,y correspond à un clic sur le bouton tourner une piece
 * \param x Variable de type float représentant une position en abscisse
 * \param y Variable de type float représentant une position en ordonnée
 * \return 1 si l'utilisateur a cliqué sur le bouton, 0 sinon
 *
 * \fn void attend(void)
 * \brief Fonction qui attend que l'utilisateur relache le clic.
 *
 * \fn void tourner_piece_sdl(SDL_Window * fenetre, SDL_Renderer * surface, t_piece * tabjoueur[4], int tour_joueur,TTF_Font * police, int nb_joueurs, t_piece tabpiece[21], t_piece_bougee piece_bougee){
 * \brief Fonction qui effectue une rotation de 90 degré sur une piece.
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param tabjoueur[4] Tableau de pointeur de type t_piece pointant vers chaque tableau de piece des 4 joueurs.
 * \param tour_joueur Variable de type int contenant le numero du joueur en train de joueur
 * \param police SDL - Pointeur de type TTF_Font
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param tabpiece[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param piece_bougee Pointeur de type t_piece_bougee contenant toutes les informations de la derniere piece bougee ou de celle qui est en train d'etre bougée.
 *
 * \fn void mis_a_jour_piece(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs,t_piece * tabjoueur[4],t_piece tabpiece[21], int tour_joueur){
 * \brief Fonction qui met à jour la banque de piece au joueur correspondant (suivant généralement) et met à jour les pieces placées de tous les joueurs
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param tabjoueur[4] Tableau de pointeur de type t_piece pointant vers chaque tableau de piece des 4 joueurs.
 * \param tabpiece[21] Tableau de type t_piece contenant les pieces d'un joueur.
 * \param tour_joueur Variable de type int contenant le numero du joueur en train de joueur
 *
 * \fn int mis_a_jour(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs, int tour_joueur){
 * \brief Fonction qui met à jour l'ensemble de la fenetre, autre que les pieces.
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \param nb_joueurs Variable de type int contenant le nombre de joueurs participant à la partie en cours
 * \param tour_joueur Variable de type int contenant le numero du joueur en train de joueur
 * \return 1 pour un succes, 0 sinon
*/



//  gcc -I/usr/include/SDL2 -I/usr/include/SDL2_ttf -I/usr/include/SDL_image -I/usr/include/SDL_gfx sdl.c dessine.c  -o  app -L/usr/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx



//########## Signatures ############

int page2_regle( SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police ) ;
int page1_regle (SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police );
int menu_principal(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police , TTF_Font * police_titre);
int mis_a_jour(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs, int tour_joueur);
void mis_a_jour_piece(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs,t_piece * tabjoueur[4],t_piece tabpiece[21], int tour_joueur);


int const hf = 680;
int const wf = 940;


// ##############################

void quit(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police){
    
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_DestroyRenderer(surface);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}




int numero_piece(t_piece tab[21], int x, int y){
    int i=0;
    int trouve=0;
    int numero_gagnant=-1;
    
    while (i<21 && trouve != 1){
        if(tab[i].position.x < x && (tab[i].position.x+tab[i].position.w) > x){
            if(tab[i].position.y < y && (tab[i].position.y+tab[i].position.h) > y){
                trouve=1;
                numero_gagnant=i;
            }
        }
        i++;
    }

    if(trouve)
        return numero_gagnant;
    else
        return -1;
}



int wrap_num(t_piece tab[21], int x, int y){
    return numero_piece(tab,x,y);
}




int hors_jeu(int x, int y){
    if( x>669 || x<240)
        return 0;
    else if( y<130|| y>540)
        return 0;
    else
        return 1;
}


void replace(SDL_Renderer * surface,t_piece * tabjoueur[4], t_piece  tab[21],  int x, int y, SDL_Window * fenetre, TTF_Font * police,int num_piece, int nb_joueurs, int tour_joueur, t_case back_cases[20][20]){
    int i=0;
    int j=0;
    int error=2;
    int trouve=0;
    //int compteur;
    //int k;
    x=x+error;
    y=y-error;

    while(i<20 && trouve==0){
        j=0;
        while(j<20 && trouve==0){ // On cherche la case qui couvre la position haute gauche de la piece.
            
            if( x>back_cases[i][j].posx && x<back_cases[i][j].posx+back_cases[i][j].w && y>back_cases[i][j].posy && y<back_cases[i][j].posy+back_cases[i][j].h){
                tab[num_piece].position.x=back_cases[i][j].posx;
                tab[num_piece].position.y=back_cases[i][j].posy;
                trouve=1;
                mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tab,tour_joueur);
            }
            j++;
        }
        i++;
    }
}


void positionne_piece(t_piece tab[21], int x, int y,SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police, int nb_joueurs, t_piece * tabjoueur[4],t_piece_bougee * piece_bougee, int tour_joueur, t_case back_cases[20][20]){
    int select_piece=0;
    int go=1;
   // int compteur=0;
  //  int k=0;
    SDL_Event event;
    float majoration_taille=0;
    
    if(nb_joueurs==2)
        majoration_taille=1.5;
    else
        majoration_taille=1;
    
    
    select_piece=numero_piece(tab,x,y);     // On recupere le numero de la piece cliquee
    
    if(select_piece != -1 && tab[select_piece].dispo==1){
        
        if( (select_piece != piece_bougee->numero_piece) && (piece_bougee->numero_piece != -1) && (tab[piece_bougee->numero_piece].dispo==1) ){     // Si le joueur avait déjà bougé une autre piece avant, on
            tab[piece_bougee->numero_piece].position.x=tab[piece_bougee->numero_piece].x_init;                                                      // remet l'ancienne a sa place.
            tab[piece_bougee->numero_piece].position.y=tab[piece_bougee->numero_piece].y_init;
            tab[piece_bougee->numero_piece].position.w=tab[piece_bougee->numero_piece].position.w/majoration_taille;
            tab[piece_bougee->numero_piece].position.h=tab[piece_bougee->numero_piece].position.h/majoration_taille;
            piece_bougee->numero_piece=-1;
            piece_bougee->nbr_maj=0;
            piece_bougee->nbr_rotation=0;
        }
        
        while(event.type != SDL_MOUSEBUTTONDOWN && go){
            if(event.type == SDL_QUIT){
                go=0;
                break;
            }
            SDL_WaitEvent(&event);
            SDL_GetMouseState(&x,&y);
            SDL_Rect newrect={x,y,tab[select_piece].position.w,tab[select_piece].position.h};
            tab[select_piece].position=newrect;
            piece_bougee->numero_piece=select_piece;
            piece_bougee->nbr_maj=piece_bougee->nbr_maj+1;

            if(piece_bougee->nbr_maj<=1){
                tab[piece_bougee->numero_piece].position.w=tab[piece_bougee->numero_piece].position.w*majoration_taille;
                tab[piece_bougee->numero_piece].position.h=tab[piece_bougee->numero_piece].position.h*majoration_taille;
            }
            mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tab, tour_joueur);
        }
        
        while(event.type != SDL_MOUSEBUTTONUP){
            SDL_WaitEvent(&event);
        }
        
        replace(surface,tabjoueur,tab,x,y,fenetre,police,select_piece, nb_joueurs, tour_joueur, back_cases);
        
        
        if(hors_jeu(x,y)==0){
            tab[select_piece].position.x=tab[select_piece].x_init;
            tab[select_piece].position.y=tab[select_piece].y_init;
            tab[piece_bougee->numero_piece].position.w=tab[piece_bougee->numero_piece].position.w/majoration_taille;
            tab[piece_bougee->numero_piece].position.h=tab[piece_bougee->numero_piece].position.h/majoration_taille;
            mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tab, tour_joueur);
            piece_bougee->numero_piece=-1;
            piece_bougee->nbr_maj=0;
            piece_bougee->nbr_rotation=0;
        }

    }
    
   
}

void recupere_coord(t_case back_cases[20][20],float x, float y, int*i_res, int *j_res){
    int i,j;
 //   int case_trouve=-1;
    for(i=0 ; i<20 ; i++){
        for(j=0 ; j<20 ; j++){
            if (x > back_cases[i][j].posx && x<back_cases[i][j].posx+back_cases[i][j].w && y>back_cases[i][j].posy && y<back_cases[i][j].posy+back_cases[i][j].h){
                *i_res=i;
                *j_res=j;
            }
        }
    }
}

void envoi_position(t_piece tab[21], t_case back_cases[20][20], int nb_joueurs, int *i, int *j, t_piece_bougee * piece_bougee){
    int largeur=0;
    int hauteur=0;
    float posx=0;
    float posy=0;
    int majoration = 0;
    int demi_pix=0;

    
    if(nb_joueurs==2){
        majoration = 6;
        demi_pix = 15;
    }
    else{
        majoration=4;
        demi_pix=10;
    }
    
    largeur=tab[piece_bougee->numero_piece].position.w;
    hauteur=tab[piece_bougee->numero_piece].position.h;
    posx=tab[piece_bougee->numero_piece].position.x;
    posy=tab[piece_bougee->numero_piece].position.y;

    
    if (piece_bougee->nbr_rotation == 0 ) {
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2) - demi_pix ,posy+ (hauteur/2) - demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+ (largeur/2) - demi_pix ,posy+ hauteur/2 ,i,j);
            }
        }
       
        else {
                   if (( hauteur / majoration ) % 10 == 0 ) {
                       recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2) - demi_pix,i,j);
                   }
                   else {
                       recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2),i,j);
                   }
       }
        
    }
    
        
    else if (piece_bougee->nbr_rotation == 1 ) {
        
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2) + demi_pix ,posy+ (hauteur/2) - demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+ (largeur/2) + demi_pix ,posy+ hauteur/2 ,i,j);
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2) - demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2),i,j);
            }
        }
        
        }
    
    else if (piece_bougee->nbr_rotation == 2 ) {
        
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2) + demi_pix ,posy+ (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+ (largeur/2) + demi_pix ,posy+ hauteur/2 ,i,j);
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2),i,j);
            }
        }
        
    }
    
    else if ( piece_bougee->nbr_rotation == 3 ) {
        
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2) - demi_pix ,posy+ (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+ (largeur/2) - demi_pix ,posy+ hauteur/2 ,i,j);
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx+(largeur/2),posy+ (hauteur/2),i,j);
            }
        }
        
        
    }
        
}
        

void envoi_position_ia(t_piece tab[21], t_case back_cases[20][20], int nb_joueurs, int *i, int *j, t_retour ret){
    int largeur=0;
    int hauteur=0;
    float posx=0;
    float posy=0;
    int majoration = 0;
    int demi_pix=0;
   // int tamponx=0;
  //  int tampony=0;
    
    if(nb_joueurs==2){
        majoration = 6;
        demi_pix = 15;
    }
    else{
        majoration=4;
        demi_pix=10;
    }
    
    largeur=tab[ret.numero_piece].position.w;
    hauteur=tab[ret.numero_piece].position.h;
    posx=back_cases[ret.coord.y+1][ret.coord.x+1].posx;
    posy=back_cases[ret.coord.y+1][ret.coord.x+1].posy;
    printf("Ses coordonnees : en X:%i \n en y:%i.\n Piece numero : %i.",ret.coord.y+1, ret.coord.x+1,ret.numero_piece);
    
    if (ret.nb_rota == 0 ) {
        printf("-----ROTA 0\n");
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2) + demi_pix ,posy- (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx- (largeur/2) + demi_pix ,posy- hauteur/2 ,i,j);
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2) + demi_pix,i,j);
            }
            else {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2),i,j);
            }
        }
        
    }
    
    
   else  if (ret.nb_rota == 1 ) {
        printf("-----ROTA 1\n");
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2) - demi_pix ,posy- (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx- (largeur/2) - demi_pix ,posy- hauteur/2 ,i,j);
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2) + demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2),i,j);
            }
        }
        
    }
    
    else if (ret.nb_rota == 2 ) {
        printf("-----ROTA 2\n");
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2) - demi_pix ,posy- (hauteur/2) - demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx- (largeur/2) - demi_pix ,posy- hauteur/2 ,i,j);
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2) - demi_pix ,i,j);
            }
            else {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2),i,j);
            }
        }
        
    }
    
    else if ( ret.nb_rota == 3 ) {
        printf("-----ROTA 3\n");
        if ( (largeur / majoration ) %10 ==0) {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2) + demi_pix ,posy- (hauteur/2) - demi_pix ,i,j);
                printf("\nONE\n");
            }
            else {
                recupere_coord(back_cases,posx- (largeur/2) + demi_pix ,posy- hauteur/2 ,i,j);
                printf("\nTWO\n");
            }
        }
        
        else {
            if (( hauteur / majoration ) % 10 == 0 ) {
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2) - demi_pix ,i,j);
                printf("\nTHREE\n");
            }
            else {
                printf("Valeur envoyée a recupere_coord de x : %f. \n calcul de y : %f.\n",posx-(largeur/2), posy- (hauteur/2));
                recupere_coord(back_cases,posx-(largeur/2),posy- (hauteur/2),i,j);
                printf("\nFOUR\n");
            }
        }
    }
}
        




void init_tabpiece(SDL_Renderer * surface, t_piece tab[21], SDL_Texture * thetexture, char ext[10]){
    int compteur=0;
    char nom[20];
    for (compteur=0 ; compteur<21 ; compteur++){
        char dossier[40]="img/";
        sprintf(nom,"%i",compteur+1);
        strcat(nom,ext);
        strcat(dossier,nom);
        tab[compteur].image=IMG_Load(dossier);
        thetexture=SDL_CreateTextureFromSurface(surface,tab[compteur].image);
        tab[compteur].texture=thetexture;
        printf("******* %s *******\n", dossier );
    }
}


void init_pieces(t_piece tab[21], SDL_Renderer * surface, int opt, int nb_joueurs){
    int x=wf-250;
    int y=55;
    int compteur=0;
    int espacement=10;
    int place_res=0;
    int nbr_ligne=1;

    
    // Initialisation de la postion initiale
    for(compteur=0 ; compteur < 21 ; compteur++){
        
        if(compteur==0){
            tab[compteur].position.x=x+10;
            tab[compteur].position.y=y+550;
            tab[compteur].x_init=x+10;
            tab[compteur].y_init=y+550;
            place_res=80;
            
        }
        
        else if (compteur==9){
            nbr_ligne+=nbr_ligne;
            tab[compteur].position.x=x+20;
            tab[compteur].position.y=y-10;
            tab[compteur].x_init=x+20;
            tab[compteur].y_init=y-10;
            place_res=80;
            y=90+y;
        }
        
        else if (compteur==12){
            nbr_ligne+=nbr_ligne;
            tab[compteur].position.x=x+20;
            tab[compteur].position.y=y+5;
            place_res=80;
            tab[compteur].x_init=x+20;
            tab[compteur].y_init=y+5;
            y=90+y;
        }
        
        
        else if (compteur%3==0 && compteur<10){
            nbr_ligne+=nbr_ligne;
            tab[compteur].position.x=x;
            tab[compteur].position.y=y;
            tab[compteur].x_init=x;
            tab[compteur].y_init=y;
            y=90+y;
            place_res=80;
        }
        

        
        else if (compteur%3==0 &&compteur>10){
            nbr_ligne+=nbr_ligne;
            tab[compteur].position.x=x;
            tab[compteur].position.y=y;
            tab[compteur].x_init=x;
            tab[compteur].y_init=y;
            place_res=80;
            y=90+y;
        }

        else {
            tab[compteur].position.x=x+espacement+place_res;
            tab[compteur].position.y=y;
            tab[compteur].x_init=x+espacement+place_res;
            tab[compteur].y_init=y;
            place_res+=80;
        }
     
    }

    // Initialisation des largeurs/hauteurs
    
    tab[0].position.w=20;
    tab[0].position.h=20;
    
    tab[1].position.w=20;
    tab[1].position.h=40;
    
    tab[2].position.w=20;
    tab[2].position.h=60;
    
    tab[3].position.w=40;
    tab[3].position.h=40;
    
    tab[4].position.w=20;
    tab[4].position.h=80;
    
    tab[5].position.w=40;
    tab[5].position.h=60;
    
    tab[6].position.w=40;
    tab[6].position.h=60;
    
    tab[7].position.w=40;
    tab[7].position.h=40;
    
    tab[8].position.w=60;
    tab[8].position.h=40;
    
    tab[9].position.w=20;
    tab[9].position.h=100;
    
    tab[10].position.w=40;
    tab[10].position.h=80;
    
    tab[11].position.w=40;
    tab[11].position.h=80;
    
    tab[12].position.w=40;
    tab[12].position.h=60;
    
    tab[13].position.w=40;
    tab[13].position.h=60;
    
    tab[14].position.w=40;
    tab[14].position.h=80;
    
    tab[15].position.w=60;
    tab[15].position.h=60;
    
    tab[16].position.w=60;
    tab[16].position.h=60;
    
    tab[17].position.w=60;
    tab[17].position.h=60;
    
    tab[18].position.w=60;
    tab[18].position.h=60;
    
    tab[19].position.w=60;
    tab[19].position.h=60;
    
    tab[20].position.w=60;
    tab[20].position.h=60;

    
    for(compteur=0 ; compteur <21 ; compteur++){
        tab[compteur].dispo=1;
        if (opt==1)
            SDL_RenderCopy(surface, tab[compteur].texture, NULL, &tab[compteur].position);
    }
    
}

void recupere_piece(int piece, t_liste* liste, t_matrice* copie){
    
    en_tete(liste);
    do{
        val_elem(liste,copie);
        suivant(liste);
    }while(copie->num != piece);
    precedent(liste);
    
}



int press_valider(t_piece tab[21], int x, int y,t_case back_cases[20][20],int nb_joueurs, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_matrice matri, t_coordonnee coord, int joueur,int mode, t_piece_bougee piece_bougee,t_liste* piece ){
  //  int verif=0;
    int taille_grille=400;
    int i=0;
    int j=0;
    
    if(x>(((wf-taille_grille)/2)-180)/2 && x< (((wf-taille_grille)/2)-180)/2+180 && y>355 && y< 405){
        recupere_piece(piece_bougee.numero_piece,&piece[joueur], &matri);
        rotation(matri.mat,piece_bougee.nbr_rotation);
        envoi_position(tab,back_cases,nb_joueurs,&i,&j,&piece_bougee);
        coord.x=j;
        coord.y=i;
        
        if(placer_piece(taille_plateau, plateau, matri, coord, joueur,0)){
            return 1;
        }
        else{
           return -1;
        }
    }
    
    else{
        return 0;
    }
}



void attend(void){
    SDL_Event event;
    
    do
    {
        SDL_WaitEvent(&event);
    }while(event.type != SDL_MOUSEBUTTONUP);
}


int press_tourner(int x, int y){

    int taille_grille=400;
    if(x>(((wf-taille_grille)/2)-180)/2 && x< (((wf-taille_grille)/2)-180)/2+180 && y>270 && y< 320){
        return 1;
    }
    return 0;
}



void tourner_piece_sdl(SDL_Window * fenetre, SDL_Renderer * surface, t_piece * tabjoueur[4], int tour_joueur,TTF_Font * police, int nb_joueurs, t_piece tabpiece[21], t_piece_bougee * piece_bougee){

    //double angle = 90;
    //double zoom = 2.0;
   // int lissage = 0;
    float tampon=0;

    
    SDL_Surface * imageArot=rotateSurface90Degrees(tabpiece[piece_bougee->numero_piece].image,1);
    tabpiece[piece_bougee->numero_piece].image=imageArot;
    
    tampon=tabpiece[piece_bougee->numero_piece].position.w;
    tabpiece[piece_bougee->numero_piece].position.w=tabpiece[piece_bougee->numero_piece].position.h;
    tabpiece[piece_bougee->numero_piece].position.h=tampon;
    tabpiece[piece_bougee->numero_piece].texture = NULL;
    tabpiece[piece_bougee->numero_piece].texture =SDL_CreateTextureFromSurface(surface,tabpiece[piece_bougee->numero_piece].image);
    attend();
    
    SDL_RenderCopy(surface, tabpiece[piece_bougee->numero_piece].texture, NULL,&tabpiece[piece_bougee->numero_piece].position);
    
    mis_a_jour_piece(fenetre, surface, police, nb_joueurs,tabjoueur, tabpiece, tour_joueur);

    if(piece_bougee->nbr_rotation == 3){
        piece_bougee->nbr_rotation=0;
    }
    else
        piece_bougee->nbr_rotation+=1;

}


void positionne_piece_ia(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs,t_piece * tabjoueur[4],t_piece tab[21], int tour_joueur, t_retour ret, t_case back_cases[20][20]){
    int select_piece=ret.numero_piece;
    int x=0;
    int y=0;
    int i=0;
    int tampon=0;
    float majoration_taille=0;
    
    if(nb_joueurs==2)
        majoration_taille=1.5;
    else
        majoration_taille=1;
    
    if(ret.nb_rota>0){
        do
        {
            //double angle = 90;
            //double zoom = 2.0;
            //int lissage = 0;
            float tampon=0;
            
            if(i != 0){
                majoration_taille=1;
            }
            
            SDL_Surface * imageArot=rotateSurface90Degrees(tab[ret.numero_piece].image,1);
            tab[ret.numero_piece].image=imageArot;
            
            tampon=tab[ret.numero_piece].position.w*majoration_taille;
            tab[ret.numero_piece].position.w=tab[ret.numero_piece].position.h*majoration_taille;
            tab[ret.numero_piece].position.h=tampon;
            
            tab[ret.numero_piece].texture = NULL;
            tab[ret.numero_piece].texture =SDL_CreateTextureFromSurface(surface,tab[ret.numero_piece].image);
            
            
            i++;
        }while(i<ret.nb_rota);
    }
    
    envoi_position_ia(tab, back_cases, nb_joueurs, &x, &y, ret);
    
 /*   if(ret.numero_piece==15 && ret.nb_rota==2){
        x=x+1;
    }
    
    else if((ret.numero_piece==14 || ret.numero_piece==12) && ret.nb_rota>0){
        x=x-1;
    }
    else if(ret.numero_piece==13 && ret.nb_rota>0){
        x=x+1;
    }*/
    tampon=x;
    x=back_cases[x][y].posx;
    y=back_cases[tampon][y].posy;

    SDL_Rect newrect={x,y,tab[select_piece].position.w,tab[select_piece].position.h};
    tab[ret.numero_piece].position=newrect;
    
    SDL_RenderCopy(surface, tab[ret.numero_piece].texture, NULL,&tab[ret.numero_piece].position);
    
    mis_a_jour_piece(fenetre, surface, police, nb_joueurs,tabjoueur, tab, tour_joueur);
    
    SDL_RenderPresent(surface);
    
    
}




void mis_a_jour_piece(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs,t_piece * tabjoueur[4],t_piece tabpiece[21], int tour_joueur){
    int compteur=0;
    int k=0;
    
    SDL_RenderClear(surface);
    mis_a_jour(fenetre,surface, police ,nb_joueurs,tour_joueur);
    for(compteur=0 ; compteur <21 ; compteur++){
        SDL_RenderCopy(surface, tabpiece[compteur].texture, NULL, &tabpiece[compteur].position);
    }
    for(compteur=0 ; compteur <4 ; compteur++){
        for(k=0 ; k<21 ; k++){
            if(tabjoueur[compteur][k].dispo==0)
                SDL_RenderCopy(surface, tabjoueur[compteur][k].texture, NULL, &tabjoueur[compteur][k].position);
        }
    }
    SDL_RenderPresent(surface);
}


int mis_a_jour(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int nb_joueurs, int tour_joueur){
    
   // SDL_Color white={255,255,255, 255};
    int taille_pix =0;
    int taille_grille=0;
    int nb_piece_par_ligne=0;
    int nb_cases =0;
    int j =0;
    float c=0;
    float l=0;
    int i=0;
    int n=0;
    float ecart=0;
    
    if ( nb_joueurs == 2) {
        taille_pix =30;
        taille_grille=400;
        nb_piece_par_ligne =14;
        nb_cases = 196;
    }
    
    
    if (nb_joueurs ==4 ) {
        taille_pix =20;
        taille_grille=400;
        nb_piece_par_ligne =20;
        nb_cases =400;
    }
    
    int x_orig = (wf - taille_grille) /2;
    int y_orig =(hf - taille_grille) /2;
    if(nb_joueurs==2){
        x_orig = (wf - taille_grille) /2-25;
        y_orig =(hf - taille_grille) /2-20;
    }
 
    
    // ############### Couleur de fond ###############
    
    SDL_SetRenderDrawColor(surface, 255,255,255,255);   // On met la couleur avant de décrire la surface
    SDL_RenderClear(surface);
    
    
    
    
    // ############### Quadrillage     ###############
    
    SDL_SetRenderDrawColor(surface, 0,0,0, 255);  // Grille en noir
    SDL_Rect cases[taille_grille];
    
    
    for ( i = 0; i < nb_piece_par_ligne; i++) {
        for ( j =0 ; j < nb_piece_par_ligne ; j++){
            
            cases[n].x = x_orig + c ;
            cases[n].y = y_orig + l;
            cases[n].w = taille_pix ;
            cases[n].h = taille_pix;
            c=c+taille_pix + ecart;
            n++;
        }
        l=l+ taille_pix + ecart;
        c=0;
        
    }
    
    if(SDL_RenderDrawRects(surface,cases,nb_cases) <0)//Remplissage des boutons
    {
        printf("Erreur lors des remplissages de rectangles: %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    
    // ############### Bouton de la fenetre   ###############
    
    dessine_jeu_boutons(surface,police);
    
    
    
    // ################ Cases Nom Joueur & Points #################################
    
   // SDL_Color black ={255,255,255};
    dessine_joueur(surface,police,nb_joueurs);
    dessine_tour_joueur(surface,police,tour_joueur);
    
    
    // ##################### Banque de Pièces ######################
    
    dessine_banque(surface,police);
    

    
    // ###################### Sauvegarder et quitter ###################@
    
    
    dessine_jeu_boutons_back(surface,police,1);
    
    
    return 1;
    
}



int press_sauvegarder(int x, int y,t_case back_cases[20][20],int nb_joueurs, t_piece * tabjoueur[nb_joueurs], int nb_IA, int tab_rota[nb_joueurs][21],int nb_tour_joueur, int* score, int* joueur_en_jeux, int taille_plateau, t_case_m (*plateau)[taille_plateau], t_liste* liste_piece){
    int joueur=0;
    int num_piece=0;
    int i=0;
    int posi=0;
    int posj=0;
  //  int cas_erreur=0;
    int nbr_piecejoueur=0;
    int  j, cpt;
    t_matrice piece;
    FILE *fichier;
    FILE * fic;
    attend();
    
    
    if(x>1 && x< 141 && y>hf-51 && y< hf-1){
        //Sauvegarde de la SDL
        fic=fopen("ressources/sauvegarde_sdl.txt","w");
        for(joueur=0 ; joueur<nb_joueurs ; joueur++){
            
            if(joueur==0)
                fprintf(fic,"%i_%i/", nb_joueurs,nb_IA);
            
            for(i=0 ; i<21 ; i++){
                if(tabjoueur[joueur][i].dispo==0){
                    nbr_piecejoueur++;
                }
            }
            if(nbr_piecejoueur==0){
                fprintf(fic,"0=-1,-1:-1.-1-");
            }
            else {
                fprintf(fic,"%i=", nbr_piecejoueur);
                for(num_piece=0 ; num_piece<21 ; num_piece++){
                    if(tabjoueur[joueur][num_piece].dispo==0){
                        printf("POSITION de joueur %i pour piece %i : %i %i\n", joueur,num_piece,tabjoueur[joueur][num_piece].position.x,tabjoueur[joueur][num_piece].position.y);
                        recupere_coord(back_cases, tabjoueur[joueur][num_piece].position.x+5,tabjoueur[joueur][num_piece].position.y+5, &posi, &posj);
                        fprintf(fic,"%i,%i_%i:%i.%i-",joueur,num_piece, tab_rota[joueur][num_piece],posi,posj);
                    }
                }
                nbr_piecejoueur=0;
            }
        }
        fclose(fic);
        
        // Sauvegarde du moteur
        
        fichier = fopen("ressources/SAV1", "w+");
        
        fprintf(fichier,"%i",nb_IA);
        
        fprintf(fichier,"%i",nb_joueurs);
        
        fprintf(fichier,"%i;",nb_tour_joueur);
        
        
        for(i = 0; i < nb_joueurs; i++){
            fprintf(fichier,"%i;",score[i]);
        }
        
        for(i = 0; i < nb_joueurs; i++){
            fprintf(fichier,"%i",joueur_en_jeux[i]);
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
        
        for(i = 0; i < nb_joueurs; i++ ){
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
        return 1;
    }
    else {
        return 0;
    }
}


int press_passerTour(int x, int y, int taille_grille){
    if(x > (((wf-taille_grille)/2)-180)/2 && x < (((wf-taille_grille)/2)-180)/2 + 180 && y> 440 && y< 440+50)
        return 1;
    else
        return 0;
}




    


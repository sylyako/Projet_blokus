#include "structures.h"
#include "liste.h"
#include "matrice.h"
#include "init_plateau.h"
#include "afficher.h"
#include "ajouter_piece.h"
#include "possibilite.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "dessine.h"
#include "SDL2/SDL2_rotozoom.h"
#include "sdl.h"
#include <string.h>
#include "Partie.h"
#include "IA.h"

/**
 * \file Partie.c
 * \brief Ensemble de fonctions qui font tourner une partie de jeu ainsi que les menus. Fichier principal.
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void recherche_piece_dispo(t_liste* liste, int* nb_piece, int tab_piece[])
 * \brief Fonction qui stocke dans tab_piece les numeros de pieces disponibles dans liste
 * \param liste Pointeur de type t_liste
 *
 * \fn int piece_dispo(int piece, int* nb_piece, int tab_piece[], t_liste* liste, t_matrice* copie)
 * \brief Verifie si la piece choisie (int piece) est bien une piece disponible. Si c'est le cas on copie tout les information de la piece dans copie.
 * \param piece Numero de la piece concernée
 * \param tabpiece Tableau contenant les numeros des pieces disponibles
 * \param liste Pointeur de type t_liste contenant toutes les pieces d'un joueur
 * \param copie Pointeur de type t_matrice recevant la piece disponible
 *
 * \fn void calcule_score(int nbj_max,int score[nbj_max],int joueur, t_liste* liste)
 * \brief Procédure qui calcul le score final d'un joueur
 * \param nbj_max Variable de type int contenant le nombre de joueur
 * \param score[nbj_max] Tableau contenant les scores de chaque joueur
 * \param joueur Variable contenant le numero du joueur dont on souhaite connaitre le score
 * \param liste Pointeur de type t_liste contenant les pieces
 *
 * \fn int jeux(int nbj, int nbj_max, int nb_tour_joueur, int score[nbj_max], int joueur_en_jeux[nbj_max], int taille_plateau, t_case_m plateau [taille_plateau][taille_plateau],t_liste* piece, SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police)
 * \brief Procédure qui initialise les elements necessaires au jeu et qui fait tourner le jeu jusqu'à l'arret de celui-ci
 * \param nbj Variable de type int contenant le nombre de joueurs humains
 * \param nbj_max Variable de type int contenant le nombre de joueurs total
 * \param nb_tour_joueur Variable contenant ????
 * \param score[nbj_max] Tableau contenant les scores de tous les joueurs
 * \param joueur_en_jeux[nbj_max] Tableau contenant ????
 * \param taille_plateau Variable de type int contenant la taille du plateau de jeu.
 * \param plateau [taille_plateau][taille_plateau] Matrice contenant le plateau de jeu
 * \param piece Pointeur de type t_liste contenant les pieces
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param police SDL - Pointeur de type TTF_Font
 *
 * \fn int commencer_partie(int nbj_max, SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police)
 * \brief Fonction qui lance une partie selon le nombre de joueurs choisi
 * \param nbj_max Variable de type int contenant le nombre de joueurs total
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param police SDL - Pointeur de type TTF_Font
 * \return ????
 *
 * \fn int page_regle(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int numero_page )
 * \brief Fonction "récursive" qui affiche une page des regles du jeu
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \param numero_page Variable de type int contenant le numero de la page que l'utilisateur souhaite consulter
 * \return 1 pour succès, -1 pour echec
 *
 * \fn void menu_nb_joueurs(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police)
 * \brief Fonction affichant le menu permettant de choisir le nombre de joueur.
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 *
 * \fn int menu_local (SDL_Window * fenetre ,SDL_Renderer * surface, TTF_Font * police)
 * \brief Fonction executant les evenements de clic de l'utilisateur sur le choix du nombre de joueurs
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \return 0 pour succès /!\ PAS SUPER LOGIQUE (avant c'était 1)
 *
 * \fn int menu_principal(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police )
 * \brief Fonction affichant le menu principal et executant les evenements de clic de l'utilisateur
 * \param fenetre SDL - Pointeur de type SDL_Window
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 * \return 1 pour succès /!\ PAS SUPER LOGIQUE (avant c'était 0,1)
 *
 * \fn int main
 * \brief Construction des éléments de base de la SDL (+ gestion des erreurs occasionnées s'il y en a) + lancement du menu principal
 */


int tour_joueur; //Contenant le numero du joueur en jeu

t_piece_bougee piece_bougee={-1,0,0}; // Contenant les informations sur la dernière pièce bougée

t_case back_cases[20][20]; // contenant les informations sur toutes les cases SDL

int nb_joueurs_tot=0; // Informations sur la partie.
int nbr_IA=-1;



int menu_principal(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police);




/* Verifie si la piece choisi est bien une piece dispo si c'est le cas on copie tout les information de la piece */
int piece_dispo(int num_piece_choisi, t_liste* liste, t_matrice* piece){

    en_tete(liste);
    val_elem(liste,piece);
    while(piece->num != num_piece_choisi && !hors_liste(liste)){
        suivant(liste);
        val_elem(liste,piece);
    }
    if(hors_liste(liste)){
        return 0;
    }
    
    return 1;
}


void calcule_score(int nbj_max,int score[nbj_max],int joueur, t_liste* liste){
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
int jeux(int nbj, int nbj_max, int nb_tour_joueur, int * score, int * joueur_en_jeux, int taille_plateau, t_case_m (*plateau)[taille_plateau],t_liste* liste_piece, SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police, int opt_charge){
    int const hf = 680;
    int const wf = 940;
    //Declarations pour moteur
    int nb_joueur_en_jeux = 0, nb_dispo = 0, statut;
    //int  nb_piece = 0;
    int i,j = nbj_max;
    //int cpt = nbj_max;
    //int tab_piece[TAILLE_MAX];
    t_matrice piece;
    t_couleur joueur = 0; // 0 = bleu, 1 = rouge, 2 = vert, 3 = jaune
    t_coordonnee* tab_dispo, coord; //tableau dynamique qui contiendra tout les possibilitees que l'on peut jouer
    int tab_rota[nbj_max][21];
    
    //Declarations pour sdl
    int taille_pix =0;
    int taille_grille=0;
    int nb_piece_par_ligne=0;
    int nb_cases =0;
    float c=0;
    float l=0;
    int n=0;
    int nb_joueurs=nbj_max;
    float ecart=0;
   // int compteur;

	if(nbj_max == 4){   //mode 4 joueur
        taille_plateau = 20;
        taille_pix =20;
        taille_grille=400;
        nb_piece_par_ligne =20;
        nb_cases =400;
	}else{              // mode 2 joueur(*tab_dispo)[k];
        taille_plateau = 14;
        taille_pix =30;
        taille_grille=400;
        nb_piece_par_ligne =14;
        nb_cases = 196;
	}

    
    //Definition de la taille de la grille (SDL)
    int x_orig = (wf - taille_grille) /2;
    int y_orig =(hf - taille_grille) /2;
    if(nb_joueurs==2){
        x_orig = (wf - taille_grille) /2-25;
        y_orig =(hf - taille_grille) /2-20;
    }
    
    //Dessin intial (SDL)
    
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
            
            back_cases[i][j].posx=x_orig + c;
            back_cases[i][j].posy=y_orig + l;
            back_cases[i][j].w=taille_pix;
            back_cases[i][j].h=taille_pix;
            
            c=c+taille_pix + ecart;
            n++;
        }
        l=l+ taille_pix + ecart;
        c=0;
    }

    
    if(SDL_RenderDrawRects(surface,cases,nb_cases) <0)//Remplissage des boutons
    {
        printf("Erreur lors desOOOOOOO remplissages de rectangles: %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    
    // ############### Bouton de la fenetre   ###############
    //SDL_Color white={255,255,255,255};
    dessine_jeu_boutons(surface,police);
    
    
    
    // ################ Cases Nom Joueur & Points #################################
    //SDL_Color black ={255,255,255};
    dessine_joueur(surface,police,nb_joueurs);
    dessine_tour_joueur(surface,police,0);
    
    
    // ##################### Banque de Pièces ######################
    
    dessine_banque(surface,police);
    
    
    int x = wf - 150;
    int y = 230;
    
    t_piece tab_bleu[21];
    t_piece tab_rouge[21];
    t_piece tab_vert[21];
    t_piece tab_orange[21];
    
    char ext[10]=".png";
    char extr[10]="r.png";
    char extv[10]="v.png";
    char exto[10]="o.png";
    SDL_Texture * thetexture=NULL;
    
    init_tabpiece(surface,tab_bleu,thetexture,ext);
    init_tabpiece(surface,tab_rouge,thetexture,extr);
    init_tabpiece(surface,tab_orange,thetexture,exto);
    init_tabpiece(surface,tab_vert,thetexture,extv);
    
    
    
    
    // ###################### Sauvegarder, quitter, retour a l'accueil ###################@
    
    dessine_jeu_boutons_back(surface,police,1);
    

    init_pieces(tab_bleu, surface,1,nb_joueurs);
    init_pieces(tab_rouge, surface,0,nb_joueurs);
    init_pieces(tab_orange, surface,0,nb_joueurs);
    init_pieces(tab_vert, surface,0,nb_joueurs);
    
    
    // ############### Chargement d'une partie en SDL ###############
    
    float majoration_taille;
    t_piece * tabjoueur[4]={tab_bleu, tab_rouge, tab_vert, tab_orange};
    if(opt_charge!=0){
        char carac;
        int joueur_jeu=0;
        int num_piece=0;
        int posi=0;
        int posj=0;
   //     int compt=0;
        int nb_piecejoueur=0;
        int nb_rotation;
        int tampon;
        
        FILE * fic;
        fic=fopen("sauvegarde_sdl.txt","r");
        fscanf(fic,"%c", &carac);
        while(carac != '/'){
            fscanf(fic,"%c", &carac);
        }
        
        if(nbj_max==2){
            majoration_taille=1.5;
        }
        else
            majoration_taille=1;
        
        while(!feof(fic)){
            fscanf(fic,"%i%*c",&nb_piecejoueur);
            i=0;
            tampon=0;
            while(i<nb_piecejoueur){
         
                fscanf(fic,"%i%*c%i%*c%i%*c%i%*c%i%*c",&joueur_jeu,&num_piece, &nb_rotation, &posi, &posj);
                tabjoueur[joueur_jeu][num_piece].dispo=0;
                tabjoueur[joueur_jeu][num_piece].position.w=tabjoueur[joueur_jeu][num_piece].position.w*majoration_taille;
                tabjoueur[joueur_jeu][num_piece].position.h=tabjoueur[joueur_jeu][num_piece].position.h*majoration_taille;
                
                if(nb_rotation>0){
                
                    SDL_Surface * imageArot=rotateSurface90Degrees(tabjoueur[joueur_jeu][num_piece].image,nb_rotation);
                    tabjoueur[joueur_jeu][num_piece].image=imageArot;
                    
                    tampon=tabjoueur[joueur_jeu][num_piece].position.w;
                    tabjoueur[joueur_jeu][num_piece].position.w=tabjoueur[joueur_jeu][num_piece].position.h;
                    tabjoueur[joueur_jeu][num_piece].position.h=tampon;
                    
                    tabjoueur[joueur_jeu][num_piece].texture = NULL;
                    tabjoueur[joueur_jeu][num_piece].texture =SDL_CreateTextureFromSurface(surface,tabjoueur[joueur_jeu][num_piece].image);
                }
                tabjoueur[joueur_jeu][num_piece].position.x=back_cases[posi][posj].posx;
                tabjoueur[joueur_jeu][num_piece].position.y=back_cases[posi][posj].posy;

                
                SDL_RenderCopy(surface, tabjoueur[joueur_jeu][num_piece].texture, NULL, &tabjoueur[joueur_jeu][num_piece].position);
               
                nb_rotation=0;
                i++;
            }
            nb_piecejoueur=0;
        }
        fclose(fic);
    }
        
 
    SDL_RenderPresent(surface);
    
	for(i = 0; i < nbj_max; i++){
        if (joueur_en_jeux[i] == 1){
            nb_joueur_en_jeux ++;
        }
	}

    
    //Declaration du moteur d'evenements et des variables pour la sdl
    SDL_Event event;
   // int Bouton=0 ;
    int stop=0;
    int onclick = 0;
   // int numero_piece=0;
    //int err_verif=0;
    tour_joueur=0;
    //int k=0;
    int autorisation_next=0;
    t_retour ret;
    int condamne[4]={0,0,0,0};
    int tous_condamnes=0;
    
    
    // ############### Boucle du jeu ###############

    
    while(nb_joueur_en_jeux >= 1 && (stop!=1||stop!=-1)){
       
        statut = 0;
        tab_dispo = NULL;   // pour chaque joueur on remet a 0 le tableau des possibilitees
        nb_dispo = 0;
        autorisation_next++;
        tous_condamnes=0;
        
        // ###### Determine si il y a encore un joueur qui peut jouer #######
        
        while(condamne[joueur]==1 && tous_condamnes<nbj_max){
            if(nbj_max == 4){
                if(joueur == 3){
                    tour_joueur=0;
                    joueur=0;
                }else{
                    tour_joueur++;
                    joueur++;
                }
                free(tab_dispo);
                nb_tour_joueur++;
            }else{
                if(joueur == 1){
                    tour_joueur=0;
                    joueur=0;
                }else{
                    tour_joueur++;
                    joueur++;
                }
                free(tab_dispo);
                nb_tour_joueur++;
            }
            tous_condamnes++;
        }
        if(tous_condamnes==nbj_max){
            stop=1;
            break;
        }
        // ###### Si le joueur est une IA ########
        
        if(joueur >= nbj_max-nbj){

            ret= calcule_ia(nbj_max,joueur_en_jeux, taille_plateau,plateau, liste_piece, 2, joueur, nb_tour_joueur);
            piece_dispo(ret.numero_piece, &liste_piece[joueur], &piece);

            if(ret.nb_rota==4)
                ret.nb_rota=0;
            for(l = 1; l <= ret.nb_rota; l++){
                rotation(piece.mat,1);
            }
            
            tab_rota[joueur][ret.numero_piece]=ret.nb_rota;
            
            // ###### Si l'IA a encore des possibilitees #######
            if(ret.numero_piece!=-1){
                if(placer_piece(taille_plateau,plateau,piece,ret.coord,joueur,0) == 0){
                    fprintf(stderr, "Error IA!\n");
                }
                oter_elt(&liste_piece[joueur]);
                positionne_piece_ia(fenetre,surface,police, nbj_max, tabjoueur, tabjoueur[tour_joueur], tour_joueur, ret, back_cases);
                mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[tour_joueur],tour_joueur);
                
                autorisation_next=0;
                piece_bougee.numero_piece=-1;
                piece_bougee.nbr_maj=0;
                piece_bougee.nbr_rotation=0;
                tabjoueur[tour_joueur][ret.numero_piece].dispo=0;

                score[joueur] += 15;
            }
            
            else{
                condamne[joueur]=1;
            }
            
            
            if(nbj_max == 4){
                if(joueur == 3){
                    tour_joueur=0;
                    joueur=0;
                }else{
                    tour_joueur++;
                    joueur++;
                }
                nb_tour_joueur++;
            }else{
                if(joueur == 1){
                    tour_joueur=0;
                    joueur=0;
                }else{
                    tour_joueur++;
                    joueur++;
                }
                nb_tour_joueur++;
            }
            
            mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[tour_joueur],tour_joueur);
        }
        
        // ###### Si le joueur est un humain ########
        else{
        
             SDL_PollEvent(&event);
            
            if (event.type == SDL_QUIT) {
                stop=-1;
                break;
            }
            
            
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT) {
                    onclick = 1;
                }
            }
            
            
            if (event.type == SDL_MOUSEBUTTONUP) {
                onclick = 0;
            }
            

            if(joueur_en_jeux[0]==0 && joueur_en_jeux[1]==0 && joueur_en_jeux[2]==0 && joueur_en_jeux[3]==0 ){
                stop=1;
                break;
            }
               
        
        if(joueur_en_jeux[joueur] == 1){
            if(possible_de_jouer(taille_plateau, plateau, joueur, nb_tour_joueur/4, &tab_dispo, &nb_dispo,&liste_piece[joueur])){
                if (onclick == 1 ){
                    if (SDL_GetMouseState(&x, &y)){
                                coord.x = 0;
                                coord.y = 0;
                                // ###### Si le joueur clique sur nue piece pour la positionner ########
                                if(wrap_num(tabjoueur[tour_joueur],x,y)!=-1){
                                     positionne_piece(tabjoueur[tour_joueur],x,y,surface, fenetre, police, nb_joueurs,tabjoueur, &piece_bougee, tour_joueur, back_cases);
                                 }
                        
                                 // ###### Tentative de validation de la piece ########
                                 else if(press_valider(tabjoueur[tour_joueur],x,y,back_cases,nb_joueurs,taille_plateau, plateau, piece, coord, joueur,0, piece_bougee, liste_piece)==1 && piece_bougee.numero_piece != -1){
                                     attend();
                                     autorisation_next=0;
                                     oter_elt(&liste_piece[joueur]);
                                     
                                     tab_rota[joueur][piece_bougee.numero_piece]=piece_bougee.nbr_rotation;
                                     
                                     tabjoueur[tour_joueur][piece_bougee.numero_piece].dispo=0;
                                     piece_bougee.numero_piece=-1;
                                     piece_bougee.nbr_maj=0;
                                     piece_bougee.nbr_rotation=0;

                                     score[joueur] += 15;

                                     if(nbj_max == 4){
                                         if(tour_joueur == 3){
                                             tour_joueur=0;
                                         }else{
                                             tour_joueur++;
                                         }
                                      
                                         nb_tour_joueur++;
                                     }else{
                                         if(tour_joueur == 1){
                                             tour_joueur=0;
                                         }else{
                                             tour_joueur++;
                                         }
                                     
                                         nb_tour_joueur++;
                                     }
                                     
                                     mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[tour_joueur],tour_joueur);
                                 }
                                // ###### Si la validation a echouee, on lui affiche un message d'erreur. ########
                                 else if(press_valider(tabjoueur[tour_joueur],x,y,back_cases,nb_joueurs,taille_plateau, plateau, piece, coord, joueur,0, piece_bougee, liste_piece)==-1 && piece_bougee.numero_piece != -1){
                                     mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[tour_joueur],tour_joueur);
                                     SDL_SetRenderDrawColor(surface,255, 190, 100, 255);
                                     SDL_Color error_color={220,20,60};
                                     SDL_Rect rec_error= {wf-wf/2-180,hf-hf/2-50,180,50};
                                     SDL_RenderFillRect(surface,&rec_error);
                                     SDL_Surface* error = TTF_RenderText_Solid(police, "Faut t'acheter des lunettes ! ",error_color);
                                     SDL_Texture* Message_error =SDL_CreateTextureFromSurface(surface, error);
                                     SDL_RenderCopy(surface, Message_error, NULL,&rec_error);
                                     SDL_RenderPresent(surface);
                                     
                                     SDL_Event erreur;
                                     SDL_PollEvent(&erreur);
                                     while(erreur.type != SDL_MOUSEBUTTONUP){
                                         SDL_PollEvent(&erreur);
                                     }
                                     
                                     mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[tour_joueur],tour_joueur);
                                     SDL_SetRenderDrawColor(surface,193, 193, 193, 0);
                                     SDL_Color error_color2={33,33,19};
                                     SDL_Rect rec_error2= {50,50,0,0};
                                     SDL_RenderFillRect(surface,&rec_error2);
                                     SDL_Surface* error2 = TTF_RenderText_Solid(police, "Faut t'acheter des lunettes ! ",error_color2);
                                     SDL_Texture* Message_error2 =SDL_CreateTextureFromSurface(surface, error2);
                                     SDL_RenderCopy(surface, Message_error2, NULL,&rec_error2);
                                     SDL_RenderPresent(surface);
                                     
                                     
                                 }
                        
                                 // ###### Si le joueur désire tourner une piece ########
                                 else if(press_tourner(x,y)==1 && piece_bougee.numero_piece != -1){
                                     tourner_piece_sdl(fenetre,surface,tabjoueur,tour_joueur,police,nb_joueurs,tabjoueur[tour_joueur],&piece_bougee);
                                 }
                        
                                 // ###### Si le joueur veut sauvegarder sa partie ########
                                 else if(press_sauvegarder(x,y,back_cases, nb_joueurs, tabjoueur, nbj, tab_rota, nb_tour_joueur, score, joueur_en_jeux, taille_plateau, plateau, liste_piece)==1);
                        
                                else if(event.motion.x > 0 && event.motion.x < 50  && event.motion.y > 0 && event.motion.y < 50 ){
                                    stop=1;
                                    menu_principal(fenetre,surface,police);
                                }
                        
                                // ###### La joueur décide de passer son tour. Il ne pourra plus jouer jusqu'à la fin de la partie. ########
                                else if(press_passerTour(x,y, taille_grille)==1){
                                    
                                    if(piece_bougee.numero_piece != -1){        //Si jamais il avait deplace une piece, elle est remise a sa place
                                        tabjoueur[joueur][piece_bougee.numero_piece].position.x=tabjoueur[joueur][piece_bougee.numero_piece].x_init;
                                        tabjoueur[joueur][piece_bougee.numero_piece].position.y=tabjoueur[joueur][piece_bougee.numero_piece].y_init;
                                        tabjoueur[joueur][piece_bougee.numero_piece].position.w=tabjoueur[joueur][piece_bougee.numero_piece].position.w/majoration_taille;
                                        tabjoueur[joueur][piece_bougee.numero_piece].position.h=tabjoueur[joueur][piece_bougee.numero_piece].position.h/majoration_taille;
                                        piece_bougee.numero_piece=-1;
                                        piece_bougee.nbr_maj=0;
                                        piece_bougee.nbr_rotation=0;
                                    }
                                    condamne[joueur]=1;
                                    if(nbj_max == 4){
                                        if(joueur == 3){
                                            joueur = 0;
                                            tour_joueur=0;
                                        }else{
                                            joueur++;
                                            tour_joueur++;
                                        }
                                  
                                        nb_tour_joueur++;
                                    }else{
                                        if(joueur == 1){
                                            joueur = 0;
                                            tour_joueur=0;
                                        }else{
                                            joueur ++;
                                            tour_joueur++;
                                        }
                                   
                                        nb_tour_joueur++;
                                    }
                                    mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[joueur], tour_joueur);
                                }
                        }
                }

            }else{
               statut = 1;
            }
            if(statut == 1){
                joueur_en_jeux[joueur] = 0;
                nb_joueur_en_jeux --;
                calcule_score(nbj_max, score, joueur, &liste_piece[joueur]);
                statut = 0;
            }
        }
        // ###### Chanegement de joueur ########
        if(nbj_max == 4 && autorisation_next==0){
            if(joueur == 3){
                joueur = 0;                      // a quel moment on dit de changer de joueur dans la sdl ?
            }else{
                joueur++;
            }
            free(tab_dispo);
            nb_tour_joueur++;
        }else if(autorisation_next==0){
            if(joueur == 1){
                joueur = 0;
            }else{
                joueur ++;
            }
            free(tab_dispo);
            nb_tour_joueur++;
        }

        }
    }
    int maxscore=0;
    int gagnant=0;

    for(j = 0; j < nbj_max; j++){
        if(i==0){
            maxscore=score[i];
            gagnant=i;
        }
        if(score[i] > maxscore){
            maxscore=score[i];
            gagnant=i;
        }
    }
    
    if(stop != -1){ // Si l'utilisateur est à la fin de la partie et n'a pas clique sur la fermeure de la fenetre
        // ###### Message d'aurevoir ########
        mis_a_jour_piece(fenetre, surface, police, nb_joueurs, tabjoueur,tabjoueur[tour_joueur],tour_joueur);
        SDL_SetRenderDrawColor(surface,234, 221, 206, 100);
        SDL_Color error_color2={133,94,100};
        SDL_Rect rec_error2= {100,150,690,200};
        SDL_RenderFillRect(surface,&rec_error2);
        SDL_Surface* error2 =NULL;
        
        switch(gagnant)
        {
            case 1 : error2 = TTF_RenderText_Solid(police, "Fin de la partie !  Joueur 1 a gagne.",error_color2); break;
            case 2 : error2 = TTF_RenderText_Solid(police, "Fin de la partie !  Joueur 2 a gagne.",error_color2); break;
            case 3 : error2 = TTF_RenderText_Solid(police, "Fin de la partie !  Joueur 3 a gagne.",error_color2); break;
            case 4 : error2 = TTF_RenderText_Solid(police, "Fin de la partie !  Joueur 4 a gagne.",error_color2); break;
           // default : break;
        }

        SDL_Texture* Message_error2 =SDL_CreateTextureFromSurface(surface, error2);
        SDL_RenderCopy(surface, Message_error2, NULL,&rec_error2);
        
        SDL_Rect rec_clic= {250,450,400,140};
        SDL_RenderFillRect(surface,&rec_clic);
        SDL_Surface* clic = TTF_RenderText_Solid(police, "Cliquez sur l'ecran.",error_color2);
        SDL_Texture* Message_clic =SDL_CreateTextureFromSurface(surface, clic);
        SDL_RenderCopy(surface, Message_clic, NULL,&rec_clic);
        
        SDL_RenderPresent(surface);
        attend();
    }
    
    free(tab_dispo);
    quit(fenetre, surface, police);
    return (1);
}










int commencer_partie(int nbj_max, int nb_IA, SDL_Renderer * surface, SDL_Window * fenetre, TTF_Font * police){

    
    switch(nbj_max){
        case 2:{
            int score[nbj_max], joueur_en_jeux[nbj_max],taille_plateau = 14;
            t_liste liste_piece[nbj_max];
            t_case_m plateau[taille_plateau][taille_plateau];

            init_plateau(taille_plateau,plateau,nbj_max,liste_piece,joueur_en_jeux,score);

            if(jeux(nb_IA,nbj_max,0,score,joueur_en_jeux,taille_plateau,plateau,liste_piece,surface,fenetre,police,0) == 4){
                return(4);
            }else{
                return(1);
            }
            break;
        }

        case 4:{
            int score[nbj_max], joueur_en_jeux[nbj_max],taille_plateau = 20;
            t_liste liste_piece[nbj_max];
            t_case_m plateau[taille_plateau][taille_plateau];

            init_plateau(taille_plateau,plateau,nbj_max,liste_piece,joueur_en_jeux,score);

            if(jeux(nb_IA,nbj_max,0,score,joueur_en_jeux,taille_plateau,plateau,liste_piece,surface,fenetre,police,0)){
                return(4);
            }else{
                return(1);
            }
            break;
        }
        
        default : return(0); // Rajout //
    }
}



int page_regle(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police, int numero_page ) {
    
    int const hf = 680;
    int const wf = 940;
    
    SDL_Surface* regle=NULL;
    SDL_SetRenderDrawColor(surface, 255,255,255,255);   // On met la couleur avant de d'ecrire la surface
    SDL_RenderClear(surface);
    
    SDL_Color rouge={ 188,81,72, 255};
    
    int h =0;
    int w=0;
    
    SDL_Surface* regle_titre= TTF_RenderText_Solid(police, " *****  Regle du Blokus *****",rouge);
    SDL_Texture* Message_titre_regle=SDL_CreateTextureFromSurface(surface, regle_titre);
    SDL_QueryTexture(Message_titre_regle, NULL, NULL, &w, &h);
    SDL_Rect taille_titre ={(wf-200)/2-170,0,w,h};
    SDL_RenderCopy(surface, Message_titre_regle, NULL,&taille_titre);
    
    
    
    if(numero_page==1){
        regle = IMG_Load("../regle_11.png");
    }
    else if (numero_page==2){
        regle = IMG_Load("../regle_2.png");
    }
    else {
        regle = IMG_Load("../regle_3.png");
    }
    
    SDL_Texture* monImage = SDL_CreateTextureFromSurface(surface,regle);
    SDL_Rect pos_fond ={30,50,wf-60,hf-45};
    SDL_RenderCopy(surface, monImage, NULL,&pos_fond);
    
    
    if(numero_page==1 || numero_page==2){
        SDL_Surface* fleche_bas = IMG_Load("../fleche_bas.png");
        if(!fleche_bas)
        {
            printf("Erreur de chargement de l'image : %s",SDL_GetError());
            return -1;
        }
        SDL_Texture* fleche_bas_t = SDL_CreateTextureFromSurface(surface,fleche_bas);
        SDL_Rect pos_fleche_bas ={wf-50,hf-50,50,50};
        SDL_RenderCopy(surface, fleche_bas_t, NULL,&pos_fleche_bas);
        
        
    }
    
    if (numero_page==2 || numero_page==3){
        
        SDL_Surface* fleche_haut = IMG_Load("../fleche_haut.jpg");
        SDL_Texture* fleche_haut_t = SDL_CreateTextureFromSurface(surface,fleche_haut);
        SDL_Rect pos_fleche_haut ={wf-50,hf-100,50,50};
        SDL_RenderCopy(surface, fleche_haut_t, NULL,&pos_fleche_haut);
        
    }
    
    
    dessine_jeu_boutons_back(surface, police, 0);
    
    SDL_RenderPresent(surface);
    
    SDL_Event event;
    
   // int Bouton=0 ;
    int stop=0;
    
    while(!stop){
        SDL_WaitEvent(&event);
        
        switch(event.type){
                
            case SDL_MOUSEBUTTONUP :
                
                if ((numero_page != 3) && event.motion.x > wf-50 && event.motion.x < wf  && event.motion.y > hf- 50 && event.motion.y < hf ){
                    page_regle(fenetre,surface,police,numero_page+1);
                    stop =1;
                }
                
                if (event.motion.x > 0 && event.motion.x < 50  && event.motion.y > 0 && event.motion.y < 50 ){
                    menu_principal(fenetre,surface,police);
                    stop=1;
                }
                
                if ( (numero_page ==2 || numero_page==3) && event.motion.x > wf-50 && event.motion.x < wf  && event.motion.y > hf- 100 && event.motion.y < hf -50 ){
                    page_regle(fenetre,surface,police, numero_page-1);
                    stop=1;
                    
                }
            
                
                
                break;
                
                
            case SDL_QUIT:
                
                stop=1;
                quit(fenetre, surface, police);
        }
        
    }
    return 1 ;
}


void menu_nb_joueurs(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police){
    int w =0;
    int h =0;
    int stop=0;
    int const hf = 680;
    int const wf = 940;
    SDL_Event event;

    
    SDL_SetRenderDrawColor(surface, 188,81,72, 255);
    SDL_RenderClear(surface);

    
    SDL_SetRenderDrawColor(surface, 254,248,230, 255);
    SDL_Rect bouton1 = {(wf-200)/2-200,(hf-70)/2,200,70};
    SDL_RenderFillRect(surface,&bouton1);
    
    SDL_Rect bouton2 = {(wf-200)/2+200,(hf-70)/2,200,70};
    SDL_RenderFillRect(surface,&bouton2);
    
    SDL_Color rouge={ 188,81,72, 255};
    SDL_Surface* text_bouton1= TTF_RenderText_Solid(police, "2 joueurs",rouge);
    SDL_Texture* Message_bouton1=SDL_CreateTextureFromSurface(surface, text_bouton1);
    SDL_QueryTexture(Message_bouton1, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_2J ={(wf-200)/2-200 +10,(hf-70)/2 + 10,w,h};
    SDL_RenderCopy(surface, Message_bouton1, NULL,&taille_bout_2J);
    
    SDL_Surface* text_bouton2= TTF_RenderText_Solid(police, "4 joueurs",rouge);
    SDL_Texture* Message_bouton2=SDL_CreateTextureFromSurface(surface, text_bouton2);
    SDL_QueryTexture(Message_bouton2, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_4J ={(wf-200)/2+200 +10,(hf-70)/2 +10,w,h};
    SDL_RenderCopy(surface, Message_bouton2, NULL,&taille_bout_4J);
    
    dessine_jeu_boutons_back(surface, police, 0);
    
    SDL_RenderPresent(surface);
    
    while(!stop){
        SDL_WaitEvent(&event);
        
        switch(event.type){
                
            case SDL_MOUSEBUTTONUP :
                
                if (event.motion.x > ((wf-200)/2)-200 && event.motion.x < (wf-200)/2  && event.motion.y > (hf-70)/2  && event.motion.y < (hf-70)/2 + 70 ){

                    commencer_partie(nb_joueurs_tot,nbr_IA,surface,fenetre,police); // rajouter paramètre nbr_IA
                    stop=1;
                }
                
                
                if (event.motion.x > (wf-200)/2+200 && event.motion.x < (wf-200)/2+200  + 200  && event.motion.y > (hf-70)/2  && event.motion.y < (hf-70)/2 + 70 ){
                    
                    commencer_partie(nb_joueurs_tot, nbr_IA,surface,fenetre,police);
                    stop=1;
                }
                
                if(event.motion.x > 0 && event.motion.x < 50  && event.motion.y > 0 && event.motion.y < 50 ){
                    menu_principal(fenetre,surface,police);
                    stop=1;
                }
                
                break;
                
            case SDL_QUIT:
                
                stop=1;
                quit(fenetre, surface, police);
        }
    
    }
}


void menu_reseau(SDL_Renderer * surface, TTF_Font * police){
    // ###### Indisponible sur interface graphique ########
}




int select_nb_IA (SDL_Window * fenetre ,SDL_Renderer * surface, TTF_Font * police, int nb_joueurs_tot){
    
    
    int const hf = 680;
    int const wf = 940;
    
    int w=0;
    int h=0;
    SDL_Event event;
    SDL_WaitEvent(&event);
    
    int ecart=0;
    
    SDL_SetRenderDrawColor(surface, 188,81,72, 255);
    SDL_RenderClear(surface);

    // #### Espace entre les boutons, selon le nombre de boutons. #####
    
    if(nb_joueurs_tot==2){
        ecart = (wf - (200*3.8));
    }else {
        ecart = (wf - (200*4)) / 5 ;
    }
    
    SDL_SetRenderDrawColor(surface, 254,248,230, 255);
    
    SDL_Rect titre = {( wf /2) - 350, 100, 700,70 } ;
    SDL_RenderFillRect(surface,&titre);
    
    SDL_Rect bouton0 = { ecart ,(hf-70)/2,200,70};
    SDL_RenderFillRect(surface,&bouton0);
    
    SDL_Rect bouton1 = { 2*ecart + 200 ,(hf-70)/2,200,70};
    SDL_RenderFillRect(surface,&bouton1);
    
    if(nb_joueurs_tot>2){
        SDL_Rect bouton2 = { 3*ecart + 400 ,(hf-70)/2,200,70};
        SDL_RenderFillRect(surface,&bouton2);
        
        SDL_Rect bouton3 = { 4*ecart + 600 ,(hf-70)/2,200,70};
        SDL_RenderFillRect(surface,&bouton3);
    }
    
    SDL_Color rouge={ 188,81,72, 255};
    
    SDL_Surface* text_titre= TTF_RenderText_Solid(police, "Selectionnez un nombre d' I.A.",rouge);
    SDL_Texture* Message_titre=SDL_CreateTextureFromSurface(surface, text_titre);
    SDL_QueryTexture(Message_titre, NULL, NULL, &w, &h);
    SDL_Rect taille_titre ={ ( wf /2) - 350 + 60, 100 + 10,w,h};
    SDL_RenderCopy(surface, Message_titre, NULL,&taille_titre);
    
    SDL_Surface* text_bouton0= TTF_RenderText_Solid(police, "  0 ",rouge);
    SDL_Texture* Message_bouton0=SDL_CreateTextureFromSurface(surface, text_bouton0);
    SDL_QueryTexture(Message_bouton0, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_0 ={ecart +50,(hf-70)/2 +10,w,h};
    SDL_RenderCopy(surface, Message_bouton0, NULL,&taille_bout_0);
    
    SDL_Surface* text_bouton1= TTF_RenderText_Solid(police, "  1 ",rouge);
    SDL_Texture* Message_bouton1=SDL_CreateTextureFromSurface(surface, text_bouton1);
    SDL_QueryTexture(Message_bouton1, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_1 ={ 2*ecart + 260 ,(hf-70)/2 +10,w,h};
    SDL_RenderCopy(surface, Message_bouton1, NULL,&taille_bout_1);
    
    if(nb_joueurs_tot>2){
        SDL_Surface* text_bouton2= TTF_RenderText_Solid(police, "2",rouge);
        SDL_Texture* Message_bouton2=SDL_CreateTextureFromSurface(surface, text_bouton2);
        SDL_QueryTexture(Message_bouton2, NULL, NULL, &w, &h);
        SDL_Rect taille_bout_2 ={3*ecart + 480 ,(hf-70)/2 +10,w,h};
        SDL_RenderCopy(surface, Message_bouton2, NULL,&taille_bout_2);
        
        SDL_Surface* text_bouton3= TTF_RenderText_Solid(police, "3",rouge);
        SDL_Texture* Message_bouton3=SDL_CreateTextureFromSurface(surface, text_bouton3);
        SDL_QueryTexture(Message_bouton3, NULL, NULL, &w, &h);
        SDL_Rect taille_bout_3 ={4*ecart + 680 ,(hf-70)/2 +10,w,h};
        SDL_RenderCopy(surface, Message_bouton3, NULL,&taille_bout_3);
    }
    
    dessine_jeu_boutons_back(surface, police, 0);
    
    SDL_RenderPresent(surface);
    
    int nbr_IA= -1;
    
    int stop =0;
    while(!stop){
        SDL_WaitEvent(&event);

        switch(event.type){

            case SDL_MOUSEBUTTONUP :

                if (event.motion.x > ecart +50 && event.motion.x < ecart +50 + 200 ) {

                    nbr_IA =0;
                    stop =1;

                }
                
                if (event.motion.x > 2*ecart + 260  && event.motion.x < 2*ecart + 260  + 200 ) {
                    
                    nbr_IA =1;
                    stop =1;
                }
                
                
                if (event.motion.x > 3*ecart + 480  && event.motion.x < 3*ecart + 480  + 200 && nb_joueurs_tot>2) {
                    
                    nbr_IA =2;
                    stop =1;
                }
                
                if (event.motion.x > 4*ecart + 680  && event.motion.x < 4*ecart + 680  + 200 && nb_joueurs_tot>2) {
                    
                    nbr_IA =3;
                    stop=1;
                }
                
                if(event.motion.x > 0 && event.motion.x < 50  && event.motion.y > 0 && event.motion.y < 50 ){
                    menu_principal(fenetre,surface,police);
                    stop=1;
                }
                
                break;
                
            case SDL_QUIT :
              
                stop =1;
                quit(fenetre,surface,police);
    
        }
    }
    
    return nbr_IA;
    
}


int menu_local (SDL_Window * fenetre ,SDL_Renderer * surface, TTF_Font * police){
    
    int const hf = 680;
    int const wf = 940;
    menu_nb_joueurs(fenetre,surface, police);
    
   // t_param_joueur * joueur_partie;
    
    SDL_Event event;
    
   // int Bouton=0 ;
    int stop=0;
    while(!stop){
        SDL_WaitEvent(&event);
        
        switch(event.type){
                
            case SDL_MOUSEBUTTONUP :
                
                if (event.motion.x > ((wf-200)/2)-200 && event.motion.x < (wf-200)/2  && event.motion.y > (hf-70)/2  && event.motion.y < (hf-70)/2 + 70 ){
                    
                    nb_joueurs_tot = 2;
                    nbr_IA = select_nb_IA (fenetre,surface,police,nb_joueurs_tot);
                    commencer_partie(nb_joueurs_tot,nbr_IA,surface,fenetre,police);
                    stop=1;
                }
                
                
                if (event.motion.x > (wf-200)/2+200 && event.motion.x < (wf-200)/2+200  + 200  && event.motion.y > (hf-70)/2  && event.motion.y < (hf-70)/2 + 70 ){
                    nb_joueurs_tot = 4;
                    nbr_IA = select_nb_IA (fenetre,surface,police,nb_joueurs_tot);
                    commencer_partie(nb_joueurs_tot, nbr_IA,surface,fenetre,police);
                    stop=1;
                }
                
                if(event.motion.x > 0 && event.motion.x < 50  && event.motion.y > 0 && event.motion.y < 50 ){
                    menu_principal(fenetre,surface,police);
                    stop=1;
                }
                
                break;
                
            case SDL_QUIT:
                
                stop=1;
                quit(fenetre, surface, police);
        }
        
    }
    
    return 0;
    
}







int menu_principal(SDL_Window * fenetre, SDL_Renderer * surface, TTF_Font * police ){

    int const hf = 680;
    int const wf = 940;
    SDL_SetRenderDrawColor(surface, 188,81,72, 255);
    SDL_RenderClear(surface);
    nb_joueurs_tot=0;
    nbr_IA=0;


    TTF_Font* police_titre = TTF_OpenFont("../ressources/TravelingTypewriter.ttf",80);
    if(!police_titre) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    
    // Menu centre
    
    SDL_SetRenderDrawColor(surface, 254,248,230, 255);
    SDL_Rect fond_menu = {(940-400)/2,(680-(500-70))/2,400,500};
    SDL_RenderFillRect(surface,&fond_menu);
    
    // Boutons Menu
    SDL_Rect bouton[5];
    SDL_SetRenderDrawColor(surface, 123,0,0, 255);
    
    bouton[0].x = (940-285)/2;
    bouton[0].y = 150;
    bouton[0].w = 285;
    bouton[0].h = 55;
    
    for(int i = 1; i != 5; i++) {
        
        bouton[i].x = bouton[i-1].x ;
        bouton[i].y = bouton[i-1].y + 100 ;
        
        bouton[i].w = bouton[0].w ;
        bouton[i].h = bouton[0].h;
    }
    
    if(SDL_RenderDrawRects(surface,bouton,5) <0)//Remplissage des boutons
    {
        printf("Erreur lors des remplissages de rectangles: %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    
    SDL_Color beige={254,248,230, 255};
    
    SDL_Surface* text_titre= TTF_RenderText_Solid(police_titre, "Blokus",beige);
    SDL_Texture* Messagetitre=SDL_CreateTextureFromSurface(surface, text_titre);
    
    int w = 0;
    int h = 0;
    
    SDL_QueryTexture(Messagetitre, NULL, NULL, &w, &h);
    SDL_Rect taille_titre ={(wf/2)-135,0,w,h};
    
    SDL_RenderCopy(surface, Messagetitre, NULL,&taille_titre);
    
    
    
    
    SDL_Color rouge={ 188,81,72, 255};
    
    SDL_Surface* text1= TTF_RenderText_Solid(police, "Jeu Local",rouge);
    SDL_Texture* Message1=SDL_CreateTextureFromSurface(surface, text1);
    SDL_QueryTexture(Message1, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_1 ={(940-285)/2 +55,153,w,h};
    SDL_RenderCopy(surface, Message1, NULL,&taille_bout_1);
    
    
    
    SDL_Surface* text2= TTF_RenderText_Solid(police, "Jeu en Reseau",rouge);
    SDL_Texture* Message2=SDL_CreateTextureFromSurface(surface, text2);
    SDL_QueryTexture(Message2, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_2 ={(940-285)/2 +8,253,w,h};
    SDL_RenderCopy(surface, Message2, NULL,&taille_bout_2);
    
    SDL_Surface* text3= TTF_RenderText_Solid(police, "Reprendre la partie",rouge);
    SDL_Texture* Message3=SDL_CreateTextureFromSurface(surface, text3);
    SDL_QueryTexture(Message3, NULL, NULL, &w, &h);
    //SDL_Rect taille_bout_3 ={(940-285)/2 +20,345,w,h};
    SDL_RenderCopy(surface, Message3, NULL,&bouton[2]);
    
    SDL_Surface* text4= TTF_RenderText_Solid(police, "Regles du Jeu",rouge);
    SDL_Texture* Message4=SDL_CreateTextureFromSurface(surface, text4);
    SDL_QueryTexture(Message4, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_4 ={(940-285)/2 +10,453,w,h};
    SDL_RenderCopy(surface, Message4, NULL,&taille_bout_4);
    
    SDL_Surface* text5= TTF_RenderText_Solid(police, "Quitter",rouge);
    SDL_Texture* Message5=SDL_CreateTextureFromSurface(surface, text5);
    SDL_QueryTexture(Message5, NULL, NULL, &w, &h);
    SDL_Rect taille_bout_5 ={(940-285)/2 +70,553,w,h};
    SDL_RenderCopy(surface, Message5, NULL,&taille_bout_5);
    
    
    
    
    // Affichage du rendu
    
    SDL_RenderPresent(surface);
    
    SDL_Event event;
    //    int bouton_clique=0;
    int Bouton=0 ;
    int stop=0;
    int size=0;
    while(!stop){
        SDL_WaitEvent(&event);
        
        switch(event.type){
                
            case SDL_MOUSEBUTTONUP :
                
                if (event.motion.x > (940-285)/2 && event.motion.x < (940-285)/2 + 285  && event.motion.y > 150  && event.motion.y < 150 + 55 ){
                    menu_local(fenetre,surface,police);
                    stop =1;
                }
                
                
                if (event.motion.x > (940-285)/2 && event.motion.x < (940-285)/2 + 285  && event.motion.y > 250  && event.motion.y < 250 + 55 ){
                    //option de reseau non disponible.
                }
                
                
                if (event.motion.x > (940-285)/2 && event.motion.x < (940-285)/2 + 285  && event.motion.y > 350  && event.motion.y < 350 + 55 ){
                    // #### Chargement de la sauvegarde du moteur #####
                    FILE * fic;
                    fic=fopen("sauvegarde_sdl.txt","r");
                    fscanf(fic,"%i%*c%i%*c", &nb_joueurs_tot, &nbr_IA);
                    fclose(fic);
                    
                    if(nb_joueurs_tot==2)
                        size=14;
                    else
                        size=20;
                    
                    int caractereActuel;
                    int nbj, nbj_max,nb_tour_joueur = 0, taille_plateau, nb_piece, num_piece;
                    int i = 1,j,k;
                    t_matrice piece;
                    FILE *fichier;
                    
                    fichier = fopen("SAV1", "r");
                    caractereActuel = fgetc(fichier);
                    nbj = caractereActuel - 48;        //nb joueur humain
                    caractereActuel = fgetc(fichier);
                    nbj_max = caractereActuel - 48;    //nb total de joueur
                    caractereActuel = fgetc(fichier);
                    while(caractereActuel != 59){ // 59 = ;
                        nb_tour_joueur = (nb_tour_joueur*i) + (caractereActuel - 48);    //nb de tour de joueur effectuer(definie indirectement sur quel joueur on s'est arreter)
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
                            score[j] = (score[j]*i) + (caractereActuel - 48);    // score de chaque joueur
                            i*=10;
                            caractereActuel = fgetc(fichier);
                        }
                        i = 1;
                    }
                    
                    for(i = 0; i < nbj_max; i++){
                        caractereActuel = fgetc(fichier);
                        player[i] = caractereActuel -48;        //Quel joueur peut encore jouer (quel joueur est encore en jeu)
                    }
                    
                    caractereActuel = fgetc(fichier);
                    if(caractereActuel == 1){
                        taille_plateau = 14;        // La taille du plateau
                    }else{
                        taille_plateau = 20;
                    }
                    
                    t_case_m plateau[taille_plateau][taille_plateau];
                    caractereActuel = fgetc(fichier);
                    
                    for(i = 0; i < taille_plateau; i++){        // Initialisation du plateau
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
                    
                    for(j = 0; j < nbj_max; j++){    //Pour chaque joueur
                        i = 1;
                        nb_piece = 0;
                        while(caractereActuel != 59){    //recupere le nombre de piece qu'il reste au joueur i
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
                            while(caractereActuel != 59){    //recupere le numero de la piece enregistree dans la sauvegarde
                                num_piece = (num_piece*i) + caractereActuel - 48;
                                i *= 10;
                                caractereActuel = fgetc(fichier);
                            }
                            
                            caractereActuel = fgetc(fichier);
                            
                            while(num_piece != piece.num && !hors_liste(&liste_piece[j])){ // Tant que le numero de la piece enregistree dans la sauvegarde n'est pas le meme que celui de la liste
                                oter_elt(&liste_piece[j]);    //On retire cette element et passe au suivant
                                val_elem(&liste_piece[j],&piece);
                            }
                            suivant(&liste_piece[j]);
                        }
                        printf("\n");
                        
                    }
                    
                    fclose(fichier);
                    jeux(nbr_IA,nb_joueurs_tot,0,score,player,taille_plateau,plateau,liste_piece,surface,fenetre,police,1);
                }
                
                
                if (event.motion.x > (940-285)/2 && event.motion.x < (940-285)/2 + 285  && event.motion.y > 450  && event.motion.y < 450 + 55 ){
                    page_regle(fenetre,surface,police,1);
                    stop =1;
                }
                
                
                if (event.motion.x > (940-285)/2 && event.motion.x < (940-285)/2 + 285  && event.motion.y > 550  && event.motion.y < 550 + 55 ){
                    Bouton=5;
                }
                
                
                if (event.motion.x > wf-70 && event.motion.x < wf  && event.motion.y > hf-70  && event.motion.y < hf ){
                    
                    menu_principal(fenetre,surface,police);
                }
                
                break;
                
                
            case SDL_QUIT:
                stop=1;
        }
        
        
    }
    return 1;
}



int main() {
    
    SDL_Window * fenetre;
    SDL_Renderer * surface;  // Déclaration des pointeurs de bases pour construire une fenetre et la remplir.
    
    if(SDL_VideoInit(NULL) < 0) // Initialisation de la SDL // Generation de pleins de codes erreurs pour vite reperer l'erreur si besoin
    {
        printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    // Création de la fenêtre :
    fenetre = SDL_CreateWindow("Blokus" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 940 , 680,SDL_WINDOW_SHOWN );
    if(fenetre == NULL) // Gestion des erreurs
    {
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    // Création du Renderer :
    surface = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    if(surface == NULL)//gestion des erreurs
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    // Texte dans la fenetre
    
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    
    
    
    TTF_Font* police = TTF_OpenFont("../ressources/TravelingTypewriter.ttf",37);
    if(!police) {
        printf("TTF_OpenFont: ZIZIIZIZ %s\n", TTF_GetError());
    }

    
    menu_principal(fenetre,surface, police);
    SDL_Quit();
    return 0;
    
}






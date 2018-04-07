#include "structures.h"
#include "init_plateau.h"
#include "afficher.h"


void font(t_plateau* plateau){
	plateau->plateau[plateau->taille_plateau-1][plateau->taille_plateau-1].couleur = vert;
}


void commencer_partie_local(){
    int nbj = 0; //nb joueur ia
    int nbj_max = 4; // nombre total de joueur
    int i;
    int taille_plateau = 20;

    t_plateau plateau_jeu; //la structure de t_plateau est dans structure.h
	
    plateau_jeu.taille_plateau = taille_plateau;
    init_plateau(&plateau_jeu,nbj_max); //On malloc plateau_jeu ici
	
	
	plateau_jeu.plateau[0][0].couleur = rouge; //1er test en entrant une valeur direct
	affiche_plateau(&plateau_jeu,0,0,nbj_max);
	
	font(&plateau_jeu); //2nd test en passent par une fonction
    affiche_plateau(&plateau_jeu,0,0,nbj_max);
	
	libere_plateau(&plateau_jeu); //On free la memoire après utilisation
}

int main(){

    commencer_partie_local();

    return(0);
}

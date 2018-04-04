#include "liste.h"

/**
 * \file liste.c
 * \brief Ensemble de fonctions servants ˆ l'utilisation des listes.
 * \author Friant Marilou Tourpe Florian Semamra Kevin Amillard Joris
 * \version 1
 *
 *
 * \fn void copie_liste(int nbj_max, t_liste source[nbj_max], t_liste copie[nbj_max])
 * \brief Fonction qui copie une liste source sur la liste copie
 * \param nbj_max Nombre de joueur dans la partie
 * \param surface SDL - Pointeur de type SDL_Renderer
 * \param police SDL - Pointeur de type TTF_Font
 */



void copie_liste(int nbj_max, t_liste source[nbj_max], t_liste copie[nbj_max]){

    int i,l,queue,ec;

    t_matrice piece;



    for(i = 0; i < nbj_max; i++){



        copie[i].queue = -1;

        copie[i].ec = -1;



        en_tete(&source[i]);

        while(!hors_liste(&source[i])){

            val_elem(&source[i],&piece);

            ajouter_piece(&copie[i],&piece);

            suivant(&source[i]);

        }

        en_tete(&source[i]);

        en_tete(&copie[i]);

    }

}


//Initialisation des listes
void init_liste(t_liste* liste){
    int i;
    t_matrice mat;

	liste->queue = -1;
	liste->ec = -1;


	for(i = 0; i < TAILLE_MAX; i++){
        init_matrice(&(liste->elem[i]));
        //afficher_matrice(liste.elem[i]);
	}
}

int liste_vide(t_liste* liste)
/* Rend vrai si la liste est vide, faux sinon */
{
    if (liste->queue == -1){
        return (1);
    }else{
        return (0);
    }
}

int hors_liste(t_liste* liste)
/* Rend vrai si l'elt courant est hors de la liste, faux sinon */
{
    if (liste->ec < 0 || liste->ec > liste->queue){
        return (1);
    }else{
        return (0);
    }
}

void en_tete(t_liste* liste)
/* Positionne en tete de la liste */
{
	if(!liste_vide(liste)){
		liste->ec = 0;
	}
}

void en_queue(t_liste* liste)
/* Positionne en queue de la liste */
{
	if(!liste_vide(liste)){
		liste->ec = liste->queue;
	}
}

void precedent(t_liste* liste)
/* Positionne sur l'elt precedent*/
{

    if(!hors_liste(liste)){
        liste->ec--;
    }

}

void suivant(t_liste* liste)
/* Positionne sur l'elt suivant*/
{
	if(!hors_liste(liste)){
		liste->ec++;
	}
}


/* Renvoie toutes les information sur une piece */
void val_elem (t_liste* liste, t_matrice* copie) {
    int i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++){
            copie->mat[i][j] = liste->elem[liste->ec].mat[i][j];
        }
    }
    copie->taille = liste->elem[liste->ec].taille;
    copie->num = liste->elem[liste->ec].num;
}

/* Supprime l'elt courant et positionne sur le suivant*/
void oter_elt(t_liste* liste){
	int i;

	if(!hors_liste(liste)){
		for(i = liste->ec ; i < liste->queue ; i++){
			liste->elem[i] = liste->elem[i+1];
		}

		liste->queue--;
		if(hors_liste(liste)){ //si on suppr le 1er elem on est hors_liste, on revien donc en liste si la liste n'est pas vide
		    en_queue(liste);
		}
	}
}



/* Ajoute ou remplace un element de la liste */

void placer_elem(t_liste* liste,t_matrice* piece){

    int i,j;

    t_coordonnee coord;



    insertion_num_piece(&(liste->elem[liste->ec]),piece->num);

    insertion_taille_piece(&(liste->elem[liste->ec]),piece->taille);

    for(i = 0; i < 5; i++){

        for(j = 0; j < 5; j++){

            liste->elem[liste->ec].mat[i][j] = 0;

            if(piece->mat[i][j] == 1){

                coord.x = i;

                coord.y = j;

                insertion_matrice_piece(&(liste->elem[liste->ec]),coord);

            }

        }

    }

}



/* Ajoute un element a la bonne place dans la liste */

void ajouter_piece(t_liste* liste,t_matrice* piece){

    t_matrice piece1,piece2;



    if(liste_vide(liste)){

        liste->queue = 0;

        liste->ec = 0;



        placer_elem(liste,piece);

    }else{



        en_tete(liste);

        val_elem(liste,&piece1);



        while(piece->num > piece1.num && !hors_liste(liste)){

            suivant(liste);

            val_elem(liste,&piece1);

        }



        if(hors_liste(liste)){

            placer_elem(liste,piece);

            liste->queue ++;

        }else{

            placer_elem(liste,piece);

            suivant(liste);

            while(!hors_liste(liste)){

                val_elem(liste,&piece2);

                placer_elem(liste,&piece1);

                copie_matrice(&piece2,&piece1);

                suivant(liste);

            }

            liste->queue ++;

            placer_elem(liste,&piece1);

        }

    }

}

/* Remplie les listes avec les données du fichier*/
void remplir_listes(t_liste* liste) {
	FILE *fichier;
	int i, j, caractereActuel,cpt;
    t_coordonnee coord;

	fichier = fopen("piece.txt", "r");

	while((caractereActuel = fgetc(fichier)) != EOF){
		if (caractereActuel == 123){ //123 = {
		    liste->ec++;
		    liste->queue++;
		    insertion_num_piece(&(liste->elem[liste->ec]),liste->ec);
		    cpt = 0;
		}else if(caractereActuel <= 57 && caractereActuel >= 48){ //si c'est un chiffre
		    cpt ++;

		    coord.x = caractereActuel - 48;
		    caractereActuel = fgetc(fichier);
		    coord.y = caractereActuel - 48;

		    insertion_matrice_piece(&(liste->elem[liste->ec]),coord);

		}else if(caractereActuel == 125){ // 125 = }
		    insertion_taille_piece(&(liste->elem[liste->ec]),cpt);

		}
	}
	en_tete(liste);
	fclose(fichier);
}

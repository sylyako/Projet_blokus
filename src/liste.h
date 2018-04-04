#ifndef LISTE_H
#define LISTE_H

#include "matrice.h"
 /** 
 * \brief structure t_liste : Structure definissant une liste de piece.
 */
typedef struct{
    int queue;
    int ec;
    t_matrice elem[TAILLE_MAX];	/**< Contient une piece */
}t_liste;

void copie_liste(int nbj_max, t_liste source[nbj_max], t_liste copie[nbj_max]);
void init_liste(t_liste* liste);
int liste_vide(t_liste* liste);
int hors_liste(t_liste* liste);
void en_tete(t_liste* liste);
void en_queue(t_liste* liste);
void precedent(t_liste* liste);
void suivant(t_liste* liste);
void val_elem (t_liste* liste, t_matrice* copie);
void oter_elt(t_liste* liste);
void placer_elem(t_liste* liste,t_matrice* piece);
void ajouter_piece(t_liste* liste,t_matrice* piece);
void remplir_listes(t_liste* liste);

#endif

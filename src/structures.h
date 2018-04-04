#ifndef STRUCTURES
#define STRUCTURES

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define TAILLE_MAX 21
#define TAILLE_MATRICE_PIECE 5


typedef enum {
    libre = 4,
    rouge = 0,
    bleu = 1,
    vert = 2,
    jaune = 3
}t_couleur;

 /** 
 * \brief structure t_case_m : Structure contenant les informations d'une case du plateau.
 */
typedef struct {
    t_couleur couleur;	/**< voir enum t_couleur */

    int possible_r; /**< Booleen determinant la disponibilite pour un joueur (1 OUI, 0 NON) */
    int possible_b;
    int possible_v;
    int possible_j;
} t_case_m;

 /** 
 * \brief structure t_coordonnee : Structure contenant deux coordonnees de plateau de jeu : x et y.
 */
typedef struct { 
    int x;
    int y;
}t_coordonnee;

#endif

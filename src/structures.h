/**
*@file structures.h
*@brief Contient les structures communes du programme
*@version 1.0
*@date mars 2018
*/

#ifndef STRUCTURES
#define STRUCTURES

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define TAILLE_MAX 21
#define TAILLE_MATRICE_PIECE 5

/**
 * \enum	t_couleur
 * \brief	Définition de couleurs en fonction d'un entier
 * \details	L'énumération contient les quatre couleurs utilisées pour le Blokus ainsi qu'une
 * 		valeur utilisée si aucune couleur n'est présente 
 */
typedef enum {
    libre = 4,	/*!< Sans couleur               */
    rouge = 0,
    bleu = 1,
    vert = 2,
    jaune = 3
}t_couleur;

/**
 * \struct	t_case
 * \brief	Définition d'une case pour un plateau de Blokus
 * \details	Elle contient une couleur pour déterminer si la case est occupée ainsi que des booléens
 *		pour savoir si la case est utilisable pour un joueur
 */
typedef struct {
    t_couleur couleur;	/*!< énumération qui indique si la case est occupée et par quelle couleur               */

    int possible_r; 	/*!< booléen qui est vrai si la case est une possibilité pour le joueur rouge               */
    int possible_b;	/*!< booléen qui est vrai si la case est une possibilité pour le joueur bleu             */
    int possible_v;	/*!< booléen qui est vrai si la case est une possibilité pour le joueur vert               */
    int possible_j;	/*!< booléen qui est vrai si la case est une possibilité pour le joueur jaune               */
} t_case;

/**
 * \struct	t_coordonnee
 * \brief	Contient des coordonnées pour une matrice à deux dimensions
 * 
 */
typedef struct { //a voir si on conserve
    int x;	/*!< Numéro de colonne              */
    int y;	/*!< Numéro de ligne              */
}t_coordonnee;

#endif

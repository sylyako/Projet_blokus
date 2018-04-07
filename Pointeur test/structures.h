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


typedef struct {
    t_couleur couleur;

    int possible_r; // booleen : 1 = possible, 0 = pas possible
    int possible_b;
    int possible_v;
    int possible_j;
} t_case;


typedef struct { //a voir si on conserve
    int x;
    int y;
}t_coordonnee;


typedef struct {
    t_case** plateau;

    int taille_plateau;
} t_plateau;

#endif

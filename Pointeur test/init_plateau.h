#ifndef INITPLATEAU
#define INITPLATEAU

#include "structures.h"

void init_plateau(t_plateau* plateau, int nbj_max);
int coordonner_invalide(int x, int y, int taille_plateau);
void libere_plateau(t_plateau* plateau);
#endif

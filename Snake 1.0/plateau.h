#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include "case_plateau.h"

typedef struct plateau {
    unsigned hauteur;
    unsigned largeur;
    unsigned nombre_snake;
    unsigned niveau;
    case_plateau ** position_case;
    case_plateau cible_fruit;
    int score;



}plateau;
void get_argument(int argc, char **argv, plateau *p);
void affiche_plateau(plateau p,void* snake); //problème avec include
case_plateau** mappage_plateau(plateau p);
void remplir_plateau(plateau *p);
void placer_fruit(plateau *p);
#endif // PLATEAU_H_INCLUDED

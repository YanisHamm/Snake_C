#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include "case_plateau.h"
typedef struct plateau {
    unsigned hauteur;
    unsigned largeur;
    unsigned nombre_snake;
    unsigned niveau;
    case_plateau ** position_case;

}plateau;
void get_argument(int argc, char **argv, plateau *p);
void affiche_plateau(plateau p);
case_plateau** mappage_plateau(plateau p);
void remplir_plateau(plateau *p);
#endif // PLATEAU_H_INCLUDED
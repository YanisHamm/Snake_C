#ifndef CASE_PLATEAU_H_INCLUDED
#define CASE_PLATEAU_H_INCLUDED
#include <stdbool.h>

typedef struct case_plateau
{
    bool obstacle;
    bool fruit;
    bool snake;
    bool vide;
    char lettre_fruit;
    int x;
    int y;
    int id_snake;

} case_plateau;



#endif // CASE_PLATEAU_H_INCLUDED

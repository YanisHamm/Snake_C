#ifndef CASE_PLATEAU_H_INCLUDED
#define CASE_PLATEAU_H_INCLUDED
#include <stdbool.h>
typedef enum
{
    Fraise=5,
    Cerise=3,
    Banane=2,
    Pomme=1
} fruit;
typedef struct case_plateau
{
    bool obstacle;
  //  enum fruit;
    bool snake;
    bool vide;
} case_plateau;



#endif // CASE_PLATEAU_H_INCLUDED

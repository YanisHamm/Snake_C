#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <string.h>

int main(int argc, char **argv)
{
plateau p;
get_argument(argc,argv,&p);
printf("hauteur = %d ,largeur =%d , nombre_snake = %d , niveaux = %d \n",
          p.hauteur,p.largeur,p.nombre_snake,p.niveau);
affiche_plateau(p);
return 0;
}

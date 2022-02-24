#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <string.h>
#include <threads.h>
#include <unistd.h>
#include "snake.h"


int main(int argc, char **argv)
{
    plateau p;
    snake s;
    thrd_t threadsSnake;

    get_argument(argc,argv,&p);
    printf("hauteur = %d ,largeur =%d , nombre_snake = %d , niveaux = %d \n",
           p.hauteur,p.largeur,p.nombre_snake,p.niveau);




    snake_init(&s,&p);

/*    p.position_case[5][0].fruit=true;
    p.position_case[5][0].obstacle=false;
    p.position_case[5][0].snake=false;
    p.position_case[5][0].vide=false;
    p.position_case[5][0].lettre_fruit='T';*/

            placer_fruit(&p);
    for(;;)
    {
        snake_move(&s,&p);


     sleep(1);

    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <string.h>
#include <threads.h>
#include <unistd.h>
#include "snake.h"
typedef struct carte{
    plateau p;
    snake s;

}carte;

int threadSnakeFonction(void * data)
{
    carte* crt=data;

    snake_move(&crt->s,&crt->p);
    return 1;
}

int main(int argc, char **argv)
{
    plateau p;
    snake *s;
    carte crt;
    thrd_t* threadsSnake;
    get_argument(argc,argv,&p);
    affiche_plateau(p);
    printf("hauteur = %d ,largeur =%d , nombre_snake = %d , niveaux = %d \n",
           p.hauteur,p.largeur,p.nombre_snake,p.niveau);



    threadsSnake = malloc(p.nombre_snake * sizeof(threadsSnake));
    s = malloc(p.nombre_snake * sizeof(snake));

    for (int i =0;i<p.nombre_snake;i++)
    {
        snake_init(&s[i],&p);
    }

    crt.p=p;
    for(int i =0 ; i<p.nombre_snake; i++)
    {
        crt.s=s[i];
        if (thrd_create( &threadsSnake[i], &threadSnakeFonction, (void *)&crt ) != thrd_success )
        {
            fprintf( stderr, "Impossible de créer thread\n" );
            return EXIT_FAILURE;
        }
    }

    placer_fruit(&p);
    return 0;
}

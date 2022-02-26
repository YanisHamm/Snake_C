#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <string.h>
#include <threads.h>
#include <unistd.h>
#include "snake.h"
plateau p;
snake *s;
mtx_t mutexAffichage;
bool finJeu=false;
int threadSnakeFonction2(void * data)
{
    int resultMove;
    snake * sd=data;
    while(sd->score != p.score && sd->vivant && !finJeu)
    {
        sleep(1);
        if(sd->score == p.score)
        {
            finJeu=true;
            return 1; // fin de jeux win
        }
        resultMove=snake_move(sd,&p);
        if (resultMove==0)
        {
            return 0; // Snake dead
        }
        mtx_lock( &mutexAffichage );

        affiche_plateau(p);
        if(p.nombre_snake==2)printf("Score snake 1 =%d\tScore snake 2 =%d\tScore à atteindre %d\n",s[0].score,s[1].score,p.score);
        else if(p.nombre_snake==3)printf("Score snake 1 =%d\tScore snake 2 =%d\tScore snake 3 =%d\tScore à atteindre %d\n",s[0].score,s[1].score,s[2].score,p.score);
        else if(p.nombre_snake==4)printf("Score snake 1 =%d\tScore snake 2 =%d\tScore snake 3 =%d\tScore snake 4 =%d\tScore à atteindre %d\n",s[0].score,s[1].score,s[2].score,s[3].score,p.score);
        else return 2;
        mtx_unlock( &mutexAffichage );
    }

    return 3;
}
int main(int argc, char **argv)
{
    int score;

    srand( time( NULL ) );

    thrd_t* threadsSnake;
    get_argument(argc,argv,&p);
    placer_fruit(&p);


    score = rand()% 49;
    score =score+50;
    p.score=score;

//p.position_case[11][21]
    printf("\t\t\t\tSNAKE \n\t\t\t\t-----\n");
    printf("hauteur = %d ,largeur =%d , nombre_snake = %d , niveaux = %d \nLe score à atteindre est %d \nATTENDRE 5 SECONDES POUR AGRANDIR LE TERMINAL ET AVOIR UN BON AFFICHAGE\n",
           p.hauteur,p.largeur,p.nombre_snake,p.niveau,p.score);
    // sleep(5);
    printf("\t\t\t\tGO!!! \n\t\t\t\t-----\n");

    threadsSnake = malloc(p.nombre_snake * sizeof(threadsSnake));
    s = malloc(p.nombre_snake * sizeof(snake));

    for (int i =0; i<p.nombre_snake; i++)
    {

        snake_init(&s[i],&p);
        s[i].thread_id=i;
    }
    mtx_init( &mutexAffichage, mtx_plain);

    for(int i =0; i<p.nombre_snake; i++)
    {
        if (thrd_create( &threadsSnake[i], &threadSnakeFonction2, (void *)&s[i] ) != thrd_success )
        {
            fprintf( stderr, "Impossible de créer thread\n" );
            return EXIT_FAILURE;
        }
    }
    for( int i=0; i<p.nombre_snake; i++ )
    {
        int threadResultCode;
        if ( thrd_join( threadsSnake[i], &threadResultCode ) == thrd_error )
        {
            fprintf( stderr, "Impossible d'attendre le thread %d\n", i );
            return EXIT_FAILURE;
        }
        if ( threadResultCode == 1 )
        {
            printf("Snake %d à gagné.",s[i].thread_id);

        }
        if ( threadResultCode == 0 )
        {
            printf("Snake %d mort.",s[i].thread_id);

        }

    }
    return 0;
}
